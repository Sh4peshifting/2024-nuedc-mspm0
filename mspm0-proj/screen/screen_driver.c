#include "screen_driver.h"

void SPI_Controller_transmitCommand(uint8_t *cmd, uint8_t cmdLength)
{
    while (DL_SPI_isBusy(SPI_0_INST))
        ;

    DL_SPI_setControllerCommandDataModeConfig(SPI_0_INST, cmdLength);

    int i = 0;
    for (i = 0; i < cmdLength; i++) {
        while (DL_SPI_isBusy(SPI_0_INST))
            ;
        DL_SPI_transmitData8(SPI_0_INST, cmd[i]);
    }
}

void SPI_Controller_transmitData(uint8_t *data, uint8_t dataLength)
{
    int i = 0;
    for (i = 0; i < dataLength; i++) {
        while (DL_SPI_isBusy(SPI_0_INST))
            ;
        DL_SPI_transmitData8(SPI_0_INST, data[i]);
    }
}

void delay_ms(uint16_t ms)
{
	while (ms--) {
        delay_cycles(CPUCLK_FREQ / 1000);
    }
}


void spi_send(uint8_t data, uint8_t data_type) 
{
    // CS = 0			
    switch (data_type) {
        case 0:
        SPI_Controller_transmitCommand(&data, 1);
        break;
        case 1:
        SPI_Controller_transmitData(&data, 1);
        break;
        default:
        break;
    }
    // CS = 1
}

void init_ads(uint8_t page)
{
	spi_send(page, 0); // set page address
	spi_send(0x10, 0); // Set Higer Column Address
	spi_send(0x00, 0); // Set Lower Column Address
}

void display(uint8_t a, uint8_t b)
{
	uint8_t pag = 0xb0;
	uint8_t i, j;
	spi_send(0x40, 0);					// Set Display Start Line
	for (i = 0; i < 8; i++) // 8 pages
	{
		init_ads(pag);
		for (j = 0; j < 64; j++)
		{
			spi_send(a, 1);
			spi_send(b, 1);
		}
		pag++;
	}
	delay_ms(80);
}

void disp_HZ16(uint8_t uc_RowNo, uint8_t uc_ColNo, uint8_t uc_HZCode)
{
	uint8_t uc_PageCnt, uc_ColCnt;
	uint8_t uc_PageAddr;

	uc_PageAddr = 0xB0 | (uc_RowNo * 2);

	for (uc_PageCnt = 0; uc_PageCnt < 2; uc_PageCnt++)
	{
		spi_send(uc_PageAddr, 0); // Set Page Address

		spi_send(0x10 | ((uc_ColNo >> 4) & 0x0F), 0); // Set Upper Bit Column Address
		spi_send(0x00 | (uc_ColNo & 0x0F), 0);				 // Set Low Bit Column Address

		for (uc_ColCnt = 0; uc_ColCnt < 16; uc_ColCnt++)
			spi_send(HZK[uc_HZCode * 32 + uc_PageCnt * 16 + uc_ColCnt], 1);

		uc_PageAddr++;
	}
}

void disp_HZ16str(uint8_t uc_RowNo, uint8_t uc_ColNo, uint8_t *HZinf, uint8_t uc_HZCnt)
{
	uint8_t uc_CharCnt;

	for (uc_CharCnt = 0; uc_CharCnt < uc_HZCnt; uc_CharCnt++)
	{
		disp_HZ16(uc_RowNo, uc_ColNo, HZinf[uc_CharCnt]);
		uc_ColNo = uc_ColNo + 16;
	}
}

void initial(void)
{
	// CS = 0;
	delay_ms(2); // 2ms
	// RST = 0;
	delay_ms(40); // 40ms
	// RST = 1;
	delay_ms(10); // 10ms

	spi_send(0xe2, 0); // Reset
	delay_ms(1);			// 1ms
	spi_send(0xA2, 0); // set 1/9 bias
	spi_send(0xA0, 0); // seg0~seg131
	spi_send(0xc8, 0); // com63~com0

	spi_send(0x24, 0); // set (1+Rb/Ra) 100:5.0 ; 111: 6.4
	delay_ms(2);			// 2ms
	spi_send(0x81, 0); // Electronic Volume Mode Set
	spi_send(0x2B, 0); // Electronic Volume Register Set
	delay_ms(1);			// 1ms

	spi_send(0x29, 0); // power control set
	delay_ms(1);			// 1ms
	spi_send(0x2B, 0); // power control set
	delay_ms(1);			// 1ms
	spi_send(0x2F, 0); // power control set
	delay_ms(1);			// 1ms

	spi_send(0xaf, 0); // Dispaly On
	delay_ms(1);			// 1ms
}
