#ifndef __ADC_DATA_CONV_H__
#define __ADC_DATA_CONV_H__

#include "ti_msp_dl_config.h"
#include <string.h>
#include "fft.h"

#define RESULT_SIZE (2048)
#define VOLT_COEF (1)
#define CURR_COEF (1)
#define COIL_N (1)

#define HIGHMARGIN 0.75 
#define LOWMARGIN  0.25 
#define MINGAIN  DL_OPA_GAIN_N1_P2 // Maximum GAIN level of OPA wanted
#define MAXGAIN  DL_OPA_GAIN_N31_P32 // Minimum GAIN level of OPA wanted.

void adc_dma_init();

void adc_data_opt();

#endif