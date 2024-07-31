#include "adc_data_conv.h"

extern uint16_t adc_sample_inx;

volatile uint16_t gADC0_Samples[RESULT_SIZE];
volatile uint16_t gADC1_Samples[RESULT_SIZE];

volatile uint8_t adc_done;

float volt[RESULT_SIZE];
float curr[RESULT_SIZE];


// float volt_in[RESULT_SIZE];
// float curr_in[RESULT_SIZE];

float curr_real;
// float curr_real_calc_inx;

float curr_img;
// float curr_img_calc_inx;

uint16_t volt_edge_rec;
uint16_t volt_edge_inx[50];
volatile uint8_t volt_edge_flag = 0;

float volt_rms;
float curr_rms;

float curr_ori_rms;
float volt_ori_rms;

volatile uint8_t opa_gain_not_met;

uint16_t peak_to_peak_calc(uint16_t* array, uint16_t size)
{
    uint16_t array_sorted[size];
    memcpy(array_sorted, array, size * 2);
    quickSort(array_sorted, 0, size - 1);

    uint16_t max_val = 0;
    uint16_t min_val = 0;
    for (uint8_t i = 0; i < 5; i++) {
        max_val += array_sorted[size - 1 - i];
        min_val += array_sorted[i];
    }
    max_val = max_val / 5;
    min_val = min_val / 5;
    return max_val - max_val;    
}

void adc_dma_init()
{
     DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,
        (uint32_t) DL_ADC12_getMemResultAddress(
            ADC12_0_INST, DL_ADC12_MEM_IDX_0));
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) &gADC0_Samples[0]);
    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);

    DL_DMA_setSrcAddr(DMA, DMA_CH1_CHAN_ID,
        (uint32_t) DL_ADC12_getMemResultAddress(
            ADC12_1_INST, DL_ADC12_MEM_IDX_0));
    DL_DMA_setDestAddr(DMA, DMA_CH1_CHAN_ID, (uint32_t) &gADC1_Samples[0]);
    DL_DMA_enableChannel(DMA, DMA_CH1_CHAN_ID);

    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
    NVIC_EnableIRQ(ADC12_1_INST_INT_IRQN);
}

float circuit_param_calc(float* param_input,uint16_t start_inx, uint16_t end_inx)
{
    float circuit_param = 0;
    for (uint16_t i = start_inx; i < end_inx; i++) {
        circuit_param += param_input[i];
    }
    circuit_param = circuit_param / (end_inx - start_inx + 1);
    return circuit_param;
}

// void find_positive_half_cycles(float* signal, uint16_t size) {
//     uint16_t pos_start = 0;
//     uint16_t pos_end = 0;
//     uint16_t nege_start = 0;
//     uint16_t nege_end = 0;
//     uint16_t half_pos_cycle = 0;

//     uint16_t in_positive_half_cycle = 0;

//     for (uint16_t i = 1; i < size; i++) {
//         if (signal[i] > 0 && signal[i - 1] <= 0) {
//             pos_start = i;
//             in_positive_half_cycle = 1;
//         } else if (signal[i] <= 0 && signal[i - 1] > 0 && in_positive_half_cycle) {
//             pos_end = i - 1; 
//             curr_real += circuit_param_calc(curr ,pos_start, pos_end);
//             curr_real_calc_inx++;
//             in_positive_half_cycle = 0;
//             half_pos_cycle = (pos_end - pos_start) / 2;
//             nege_start = pos_start + half_pos_cycle;
//             nege_end = pos_end + half_pos_cycle;
//             if (nege_end < RESULT_SIZE){
//                 curr_img += circuit_param_calc(curr, nege_start, nege_end);
//                 curr_img_calc_inx++;
//             }
//         }
//     }
// }

void curr_real_img_calc()
{
    uint16_t max_real_inx = 0;
    uint16_t max_img_inx = 0;
    uint16_t half_pos_cycle = 0;

    if (!volt_edge_flag) {
        max_real_inx = volt_edge_rec / 2;
        max_img_inx = volt_edge_rec / 2 - 1;
    }
    else {
        max_real_inx = (volt_edge_rec - 1) / 2;
        max_img_inx = (volt_edge_rec - 1) / 2;
    }
    for (uint16_t i = 0; i < max_real_inx; i++) {
        curr_real += circuit_param_calc(curr, volt_edge_inx[2 * i], volt_edge_inx[2 * i + 1]);
    }
    for (uint16_t i = 0; i < max_img_inx; i++) {
        half_pos_cycle = (volt_edge_inx[2 * i + 1] - volt_edge_inx[2 * i]) / 2;
        curr_img += circuit_param_calc(curr, volt_edge_inx[2 * i] + half_pos_cycle, 
            volt_edge_inx[2 * i + 1]) + half_pos_cycle;
    }
    curr_real = curr_real / max_real_inx;
    curr_img = curr_img / max_img_inx;
}

// (volt*3.3/4096 -1.65)*COFFE
// (curr*3.3/4096 -1.65) *COFFE/N 

static void adc_data_sort()
{
    for (uint16_t i = 0; i < RESULT_SIZE ; i++) {
        volt[i] = (3.3 * gADC0_Samples[i] / 4096 - 1.65);
        curr[i] = (3.3 * gADC1_Samples[i] / 4096 - 1.65);
    }
    // find_positive_half_cycles(volt, RESULT_SIZE);
    // curr_real = curr_real / curr_real_calc_inx;
    // curr_img = curr_img / curr_img_calc_inx;
}

static void adc_data_calc_input()
{
    uint16_t gain=1<<(DL_OPA_getGain(OPA_1_INST)>>13);
    for (uint16_t i = 0; i < RESULT_SIZE ; i++) {
        volt[i] = volt[i]*VOLT_COEF;
        curr[i] = curr[i]*CURR_COEF/COIL_N/gain;
    }

    volt_rms = volt_ori_rms  * VOLT_COEF;
    curr_rms = curr_ori_rms  * CURR_COEF / COIL_N/gain;
}



static void volt_rms_calc()
{
    float volt_ori_temp = 0;
    for (uint16_t i = volt_edge_inx[0]; i < volt_edge_inx[volt_edge_rec - 1]; i++){
        if(volt[i] < 0){
            volt_ori_temp -= volt[i];
        }
        else {
            volt_ori_temp += volt[i];
        }
    }

    volt_ori_rms = volt_ori_temp / (volt_edge_inx[volt_edge_rec - 1] - volt_edge_inx[0] + 1);

}

static void curr_ori_rms_calc()
{
    float curr_ori_temp = 0;

    for (uint16_t i = volt_edge_inx[0]; i < volt_edge_inx[volt_edge_rec - 1]; i++){
        if(curr[i] < 0){
            curr_ori_temp -= curr[i];
        }
        else {
            curr_ori_temp +=curr[i];
        }
    }

    curr_ori_rms = curr_ori_temp / (volt_edge_inx[volt_edge_rec - 1] - volt_edge_inx[0] + 1);
    
    // volt_edge_flag = 0;
    // volt_edge_rec = 0;
    // adc_sample_inx = 0;
    // memset(volt_edge_inx, 0, 100);
    // adc_done = 0;
}

static void vc_rms_calc()
{
    volt_rms = volt_ori_rms  * VOLT_COEF;
    curr_rms = curr_ori_rms  * CURR_COEF / COIL_N;
}
uint32_t Gain;

static void opa_gain_adjust()
{
    Gain = DL_OPA_getGain(OPA_1_INST);
    uint32_t tempGain = 0;
    if (curr_ori_rms > HIGHMARGIN) {
        tempGain = DL_OPA_getGain(OPA_1_INST);
        opa_gain_not_met = 1;
        if(tempGain > MINGAIN){
            DL_OPA_decreaseGain(OPA_1_INST);
        }
        else {
            opa_gain_not_met = 0;
        }
        
    }
    else if (curr_ori_rms < LOWMARGIN) {
        tempGain = DL_OPA_getGain(OPA_1_INST);
        opa_gain_not_met = 1;
        if(tempGain < MAXGAIN){
           DL_OPA_increaseGain(OPA_1_INST);
        }
        else {
            opa_gain_not_met = 0;
        }
        
    }
    else {
        opa_gain_not_met = 0;
    }
}

void adc_data_opt()
{
    do {
        volt_edge_flag = 0;
        volt_edge_rec = 0;
        adc_sample_inx = 0;
        memset(volt_edge_inx, 0, 100);
        adc_done = 0;

        NVIC_EnableIRQ(COMP_0_INST_INT_IRQN);
        DL_TimerG_startCounter(TIMER_0_INST);
        while (!adc_done) {
            __WFE();
        }

        adc_data_sort();
        curr_ori_rms_calc();
        opa_gain_adjust();
        delay_cycles(CPUCLK_FREQ/2);
    } while (opa_gain_not_met);
    volt_rms_calc(); 
    // vc_rms_calc();
    // adc_data_calc_input();
    // fft_proc(curr);
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
            adc_done |= 0x01;
            DL_TimerG_stopCounter(TIMER_0_INST);
            NVIC_DisableIRQ(COMP_0_INST_INT_IRQN);
            adc_sample_inx = 0;
            break;
        default:
            break;
    }
}
void ADC12_1_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_1_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
            adc_done |= 0x02;
            break;
        default:
            break;
    }
}
void GROUP1_IRQHandler(void)
{
    switch (DL_COMP_getPendingInterrupt(COMP_0_INST)) {
        case DL_COMP_IIDX_OUTPUT_EDGE:
            if (volt_edge_flag == 0 && adc_sample_inx != 0) 
            {
                volt_edge_inx[volt_edge_rec] = adc_sample_inx - 1;
                if(volt_edge_rec < 50)
                    volt_edge_rec++;
                volt_edge_flag = 1;
            }
            break;
        case DL_COMP_IIDX_OUTPUT_EDGE_INV:
            if (volt_edge_flag == 1 && adc_sample_inx != 0) 
            {
                volt_edge_inx[volt_edge_rec] = adc_sample_inx - 1;
                if(volt_edge_rec < 50)
                    volt_edge_rec++;
                volt_edge_flag = 0;
            }
            break;
        default:
            break;
    }
}