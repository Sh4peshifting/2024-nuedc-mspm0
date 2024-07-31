#include "fft.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include <stdio.h>

// float current_spectrum[2048];
float harmonic[16];
//frequency increasement 4.88Hz
float curr_thd;

float find_max(float *array,uint16_t start,uint16_t end)
{
    float max_value=0;
    uint16_t max_index=0;
    for(uint16_t i=start;i<end;i++){
        if(array[i]>max_value ){
            max_value=array[i];
            max_index=i;
        }
    }
    return max_value;
}

uint16_t find_max_index(float *array,uint16_t start,uint16_t end)
{
    float max_value=0;
    uint16_t max_index=0;
    for(uint16_t i=start;i<end;i++){
        if(array[i]>max_value ){
            max_value=array[i];
            max_index=i;
        }
    }
    return max_index;
}

void curr_thd_calc()
{
    float curr_pow_sum = 0;
    float curr_sqrt = 0;
    arm_power_f32(harmonic+2, 14, &curr_pow_sum);
    arm_sqrt_f32(curr_pow_sum, &curr_sqrt);

    curr_thd = curr_sqrt / harmonic[1];

}


void fft_proc(float *input_signal)
{
    float input_cmplx[2048]={0};
    for (uint16_t i = 0; i < 1024; i++)
    {
        input_cmplx[2*i] = input_signal[i];
    }

    arm_cfft_f32(&arm_cfft_sR_f32_len1024 , input_cmplx , 0 , 1);
    arm_cmplx_mag_f32(input_cmplx,volt,1024);

    uint16_t base_wave_index=find_max_index(volt,3,20);
    harmonic[1]=find_max(volt,3,20)/1024;
    for(uint16_t i=2;i<16;i++){
       harmonic[i]= find_max(volt, base_wave_index*i-3, base_wave_index*i+3) / 512;
    }
    curr_thd_calc();

}

