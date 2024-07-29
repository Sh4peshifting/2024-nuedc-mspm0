#ifndef __DSP_H__
#define __DSP_H__

#include "ti_msp_dl_config.h"

#define RESULT_SIZE (2048)
#define VOLT_COEF (1)
#define CURR_COEF (1)
#define COIL_N (1)

void adc_dma_init();

#endif