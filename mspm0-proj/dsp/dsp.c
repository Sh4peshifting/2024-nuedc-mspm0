#include "dsp.h"

// use `DL_TimerG_startCounter(TIMER_0_INST);` to start adc

volatile uint16_t gADC0_Samples[RESULT_SIZE];
volatile uint16_t gADC1_Samples[RESULT_SIZE];

volatile uint8_t adc_done;

float volt_ch1[RESULT_SIZE];
float volt_ch2[RESULT_SIZE];

float volt_real;
float volt_real_calc_inx;

float volt_img;
float volt_img_calc_inx;

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

void fft_proc()
{
    
}

float volt_param_calc(float* volt,uint16_t start_inx, uint16_t end_inx)
{
    float volt_param = 0;
    for (uint16_t i = start_inx; i < end_inx; i++) {
        volt_param += volt[i];
    }
    volt_param = volt_param / (end_inx - start_inx + 1);
    return volt_param;
}

void find_positive_half_cycles(float* signal, uint16_t size) {
    uint16_t pos_start = 0;
    uint16_t pos_end = 0;
    uint16_t nege_start = 0;
    uint16_t nege_end = 0;
    uint16_t half_pos_cycle = 0;

    uint16_t in_positive_half_cycle = 0;

    for (uint16_t i = 1; i < size; i++) {
        if (signal[i] > 0 && signal[i - 1] <= 0) {
            pos_start = i;
            in_positive_half_cycle = 1;
        } else if (signal[i] <= 0 && signal[i - 1] > 0 && in_positive_half_cycle) {
            pos_end = i - 1; 
            volt_real += volt_param_calc(volt_ch2 ,pos_start, pos_end);
            volt_real_calc_inx++;
            in_positive_half_cycle = 0;
            half_pos_cycle = (pos_end - pos_start) / 2;
            nege_start = pos_start + half_pos_cycle;
            nege_end = pos_end + half_pos_cycle;
            if (nege_end < RESULT_SIZE){
                volt_img += volt_param_calc(volt_ch2, nege_start, nege_end);
                volt_img_calc_inx++;
            }
        }
    }
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
            adc_done |= 0x01;
            DL_TimerG_stopCounter(TIMER_0_INST);
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
