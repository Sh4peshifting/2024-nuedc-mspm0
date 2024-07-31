#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include "ti_msp_dl_config.h"

uint16_t partition(uint16_t array[], uint16_t start_inx, uint16_t end_inx);
void quickSort(uint16_t array[], uint16_t start_inx, uint16_t end_inx);

#endif