#include "screen_driver.h"
#include "font.h"

void delay_ms(uint16_t ms)
{
    while (ms--) {
        delay_cycles(CPUCLK_FREQ / 1000);
    }
}

void SPI_SendByte(uint8_t c)
{

	if (c & 0x80)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);

	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);

	if (c & 0x40)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);

	if (c & 0x20)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);

	if (c & 0x10)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);

	if (c & 0x08)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);

	if (c & 0x04)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);

	if (c & 0x02)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);

	if (c & 0x01)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);
}

void write(uint8_t _data, uint8_t di) // di=0, write command
{																	// di=1,write data
	// CD = di;
	if (di)
		DL_GPIO_setPins(SPI_CD_PORT, SPI_CD_PIN);
	else
		DL_GPIO_clearPins(SPI_CD_PORT, SPI_CD_PIN);
	// CS = 0;
	DL_GPIO_clearPins(SPI_CS_PORT, SPI_CS_PIN);
	SPI_SendByte(_data);
	// CD = ~di;
	if (di)
		DL_GPIO_clearPins(SPI_CD_PORT, SPI_CD_PIN);
	else
		DL_GPIO_setPins(SPI_CD_PORT, SPI_CD_PIN);
	// CS = 1;
	DL_GPIO_setPins(SPI_CS_PORT, SPI_CS_PIN);
}

void init_ads(uint8_t page)
{
	write(page, 0); // set page address
	write(0x10, 0); // Set Higer Column Address
	write(0x00, 0); // Set Lower Column Address
}

void display(uint8_t a, uint8_t b)
{
	uint8_t pag = 0xb0;
	uint8_t i, j;
	write(0x40, 0);					// Set Display Start Line
	for (i = 0; i < 8; i++) // 8 pages
	{
		init_ads(pag);
		for (j = 0; j < 64; j++)
		{
			write(a, 1);
			write(b, 1);
		}
		pag++;
	}
	delay_ms(80);
}

void disp_char_ascii(uint8_t uc_RowNo, uint8_t uc_ColNo, uint8_t uc_Code)
{
	uint8_t uc_PageCnt, uc_ColCnt;
	uint8_t uc_PageAddr;

	uc_PageAddr = 0xB0 | (uc_RowNo * 2);

    if (uc_Code == 0) {
        uc_Code = ' ';
    }

    uc_Code-=32;

	for (uc_PageCnt = 0; uc_PageCnt < 2; uc_PageCnt++)
	{
		write(uc_PageAddr, 0); // Set Page Address

		write(0x10 | ((uc_ColNo >> 4) & 0x0F), 0); // Set Upper Bit Column Address
		write(0x00 | (uc_ColNo & 0x0F), 0);				 // Set Low Bit Column Address

		for (uc_ColCnt = 0; uc_ColCnt < 8; uc_ColCnt++)
			write(ascii_tbl[uc_Code*16 + uc_PageCnt * 8 + uc_ColCnt], 1);

		uc_PageAddr++;
	}
}



void set_axis(uint8_t x,uint8_t y)
{
    write(0xB0|y,0);           //y的值为0~8 
    write(0x10|(x>>4),0); 
    write(0x00|(x&0x0F),0); 
}

void disp_str_ascii(uint8_t uc_RowNo, uint8_t uc_ColNo, uint8_t *ptr, uint8_t uc_Cnt)
{
	uint8_t uc_CharCnt;

	for (uc_CharCnt = 0; uc_CharCnt < uc_Cnt; uc_CharCnt++)
	{
		disp_char_ascii(uc_RowNo, uc_ColNo, ptr[uc_CharCnt]);
		uc_ColNo = uc_ColNo + 8;
	}
}



void screen_init(void)
{
	// CS = 0;
	DL_GPIO_clearPins(SPI_CS_PORT, SPI_CS_PIN);
	delay_ms(2); // 2ms
	// RST = 0;
	DL_GPIO_clearPins(SPI_RST_PORT, SPI_RST_PIN);
	delay_ms(40); // 40ms
	// RST = 1;
	DL_GPIO_setPins(SPI_RST_PORT, SPI_RST_PIN);
	delay_ms(10); // 10ms

	write(0xe2, 0); // Reset
	delay_ms(1);		// 1ms
	write(0xA2, 0); // set 1/9 bias
	write(0xA0, 0); // seg0~seg131
	write(0xc8, 0); // com63~com0

	write(0x24, 0); // set (1+Rb/Ra) 100:5.0 ; 111: 6.4
	delay_ms(2);		// 2ms
	write(0x81, 0); // Electronic Volume Mode Set
	write(0x2B, 0); // Electronic Volume Register Set
	delay_ms(1);		// 1ms

	write(0x29, 0); // power control set
	delay_ms(1);		// 1ms
	write(0x2B, 0); // power control set
	delay_ms(1);		// 1ms
	write(0x2F, 0); // power control set
	delay_ms(1);		// 1ms

	write(0xaf, 0); // Dispaly On
	delay_ms(1);		// 1ms

    display(0x00, 0x00);//clear screen
    //display(0xff, 0xff); //all black
    // display(0xaa, 0x55); //interval black
}


