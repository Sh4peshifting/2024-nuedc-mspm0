#include "timer.h"

uint16_t adc_sample_inx = 0;

void TIMER_0_INST_IRQHandler(void)
{
   switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
       case DL_TIMER_IIDX_ZERO:
            adc_sample_inx++;
           break;
       default:
           break;
   }
}