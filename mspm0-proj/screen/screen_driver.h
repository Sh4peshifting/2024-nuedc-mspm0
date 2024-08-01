#ifndef __SCREEN_DRIVER_H__
#define __SCREEN_DRIVER_H__

#include "ti_msp_dl_config.h"


#define WR_CD_PIN(level) if(level == 0) \
                            DL_GPIO_clearPins(SPI_CD_PORT, SPI_CD_PIN); \
                          else  \
                            DL_GPIO_setPins(SPI_CD_PORT, SPI_CD_PIN)
#define WR_CS_PIN(level) if(level == 0) \
                            DL_GPIO_clearPins(SPI_CS_PORT, SPI_CS_PIN); \
                          else  \
                            DL_GPIO_setPins(SPI_CS_PORT, SPI_CS_PIN)
#define WR_RST_PIN(level) if(level == 0) \
                            DL_GPIO_clearPins(SPI_RST_PORT, SPI_RST_PIN); \
                          else  \
                            DL_GPIO_setPins(SPI_RST_PORT, SPI_RST_PIN)


void screen_init(void);
void disp_HZ16(uint8_t uc_RowNo, uint8_t uc_ColNo, uint8_t uc_HZCode);
void disp_HZ16str(uint8_t uc_RowNo, uint8_t uc_ColNo, uint8_t *HZinf, uint8_t uc_HZCnt);
void disp();

#endif