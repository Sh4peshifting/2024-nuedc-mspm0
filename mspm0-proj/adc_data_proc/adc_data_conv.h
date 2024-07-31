#ifndef __ADC_DATA_CONV_H__
#define __ADC_DATA_CONV_H__

#include "ti_msp_dl_config.h"
#include <string.h>
#include "fft.h"
#include "quick_sort.h"

#define RESULT_SIZE (1024)
#define VOLT_COEF (586.802)
#define CURR_COEF (1)
#define COIL_N (1)

#define HIGHMARGIN 0.75 
#define LOWMARGIN  0.25 
#define MINGAIN  DL_OPA_GAIN_N1_P2 // Minimum GAIN level of OPA wanted
#define MAXGAIN  DL_OPA_GAIN_N31_P32 // Maximum GAIN level of OPA wanted.

void adc_dma_init();

void adc_data_opt();
uint16_t peak_to_peak_calc(uint16_t* array, uint16_t size);

#endif