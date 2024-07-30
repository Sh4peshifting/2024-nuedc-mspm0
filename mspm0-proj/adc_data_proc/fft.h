#ifndef __FFT_H__
#define __FFT_H__

#include "ti_msp_dl_config.h"
#include "arm_const_structs.h"
#include "arm_math.h"

extern float current_spectrum[1024];
void fft_proc(float *input_signal);


#endif 