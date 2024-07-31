#ifndef __FFT_H__
#define __FFT_H__

#include "ti_msp_dl_config.h"
#include "arm_const_structs.h"
#include "arm_math.h"

extern float volt[1024];
extern float curr_thd;
void fft_proc(float *input_signal);


#endif 