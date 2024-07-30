#include "fft.h"
#include "arm_const_structs.h"
#include "arm_math.h"
// #include <cstdint>
#include <stdio.h>

float current_spectrum[1024];
float harmonic[15];
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

            max_index=i;
        }
    }
    return max_index;
}


void fft_proc(float *input_signal)
{
    arm_cfft_f32(&arm_cfft_sR_f32_len2048 , input_signal , 0 , 1);
    arm_cmplx_mag_f32(input_signal,current_spectrum,2048);

    uint16_t base_wave_index=find_max_index(current_spectrum,3,20);

    for(uint16_t i=1;i<=15;i++){
       harmonic[i]= find_max(current_spectrum, base_wave_index*i-3, base_wave_index*i+3) / 1024;
    }


}

void curr_thd_calc()
{
    float curr_pow_sum = 0;
    float curr_sqrt = 0;
    arm_power_f32(harmonic + 1, 14, &curr_pow_sum);
    arm_sqrt_f32(curr_pow_sum, &curr_sqrt);

    curr_thd = curr_sqrt / harmonic[0];

}