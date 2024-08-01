#include "screen_driver.h"
#include "font.h"

typedef unsigned char uchar;
typedef unsigned int uint;

unsigned char HZK[] =
		{
            0xE0,0x10,0xC8,0x28,0xE8,0xF0,0x00,0x00,0x03,0x04,0x0B,0x0A,0x0B,0x05,0x00,0x00,
				0x10, 0x60, 0x02, 0x8C, 0x00, 0x0E, 0x22, 0x12, 0x0A, 0xC2, 0x0A, 0x12, 0x22, 0x0E, 0x00, 0x00,
				0x04, 0x04, 0x7E, 0x01, 0x20, 0x21, 0x11, 0x09, 0x05, 0xFF, 0x05, 0x09, 0x11, 0x21, 0x20, 0x00, /*"??",0*/

				0x20, 0x20, 0x20, 0xFF, 0x20, 0x20, 0x00, 0xFF, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xFF, 0x00, 0x00,
				0x10, 0x30, 0x10, 0x0F, 0x08, 0x88, 0x60, 0x1F, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xFF, 0x00, 0x00, /*"??",1*/

				0x00, 0x00, 0xFE, 0x92, 0x92, 0x92, 0x92, 0xFE, 0x92, 0x92, 0x92, 0x92, 0xFE, 0x00, 0x00, 0x00,
				0x40, 0x38, 0x01, 0x00, 0x3C, 0x40, 0x40, 0x42, 0x4C, 0x40, 0x40, 0x70, 0x05, 0x08, 0x30, 0x00, /*"?",2*/

                0x00,0x00,0x00,0xFB,0x80,0x94,0x80,0x94,0x80,0x94,0x80,0xB7,0x80,0x60,0x00,0x00,
                0x00,0x00,0x00,0xFB,0x80,0x94,0x80,0x94,0x80,0x94,0x80,0xB7,0x80,0x60,0x00,0x00,
                
				0x40, 0x40, 0x42, 0xCC, 0x00, 0x04, 0x04, 0x04, 0xFC, 0x24, 0x24, 0x24, 0x24, 0xE4, 0x04, 0x00,
				0x00, 0x40, 0x20, 0x1F, 0x20, 0x50, 0x48, 0x46, 0x41, 0x40, 0x48, 0x50, 0x48, 0x47, 0x40, 0x00, /*"??",3*/

				0x10, 0x88, 0xC4, 0x33, 0x80, 0x9E, 0x90, 0x9F, 0x90, 0x9E, 0x20, 0xD8, 0x17, 0xF0, 0x10, 0x00,
				0x01, 0x00, 0xFF, 0x80, 0x40, 0x3E, 0x02, 0x02, 0x3E, 0x10, 0x88, 0x67, 0x18, 0x67, 0x80, 0x00, /*"?",4*/

				0x00, 0x00, 0xF8, 0x88, 0x88, 0x88, 0x88, 0xFF, 0x88, 0x88, 0x88, 0x88, 0xF8, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x1F, 0x08, 0x08, 0x08, 0x08, 0x7F, 0x88, 0x88, 0x88, 0x88, 0x9F, 0x80, 0xF0, 0x00, /*"??",5*/

				0x80, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0xE2, 0xA2, 0x92, 0x8A, 0x86, 0x82, 0x80, 0x80, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*"??",6*/

				0x04, 0x04, 0x04, 0x84, 0xE4, 0x3C, 0x27, 0x24, 0x24, 0x24, 0x24, 0xE4, 0x04, 0x04, 0x04, 0x00,
				0x04, 0x02, 0x01, 0x00, 0xFF, 0x09, 0x09, 0x09, 0x09, 0x49, 0x89, 0x7F, 0x00, 0x00, 0x00, 0x00, /*"??",7*/

				0x00, 0xFE, 0x22, 0x5A, 0x86, 0x00, 0xFE, 0x92, 0x92, 0x92, 0x92, 0x92, 0xFE, 0x00, 0x00, 0x00,
				0x00, 0xFF, 0x04, 0x08, 0x07, 0x00, 0xFF, 0x40, 0x20, 0x03, 0x0C, 0x14, 0x22, 0x41, 0x40, 0x00, /*"??",8*/

				0x00, 0x80, 0x40, 0x20, 0x18, 0x06, 0x80, 0x00, 0x07, 0x18, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
				0x01, 0x00, 0x20, 0x70, 0x28, 0x26, 0x21, 0x20, 0x20, 0x24, 0x38, 0x60, 0x00, 0x01, 0x01, 0x00, /*"??",9*/

				0x00, 0x10, 0x12, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x12, 0x12, 0x02, 0xFE, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x3F, 0x10, 0x10, 0x10, 0x10, 0x3F, 0x00, 0x40, 0x80, 0x7F, 0x00, 0x00, 0x00, /*"?",10*/
};

uchar SMWDZ[] =
		{
				0x02, 0x03, 0x04, 0x05, 0x06};

void delay_ms(uint16_t ms)
{
    while (ms--) {
        delay_cycles(CPUCLK_FREQ / 1000);
    }
}

void SPI_SendByte(uchar c)
{

	if (c & 0x80)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SDA = Temp_Buff7;
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SDA = Temp_Buff6;
	if (c & 0x40)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SDA = Temp_Buff5;
	if (c & 0x20)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SDA = Temp_Buff4;
	if (c & 0x10)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SDA = Temp_Buff3;
	if (c & 0x08)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SDA = Temp_Buff2;
	if (c & 0x04)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SDA = Temp_Buff1;
	if (c & 0x02)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SDA = Temp_Buff0;
	if (c & 0x01)
		DL_GPIO_setPins(SPI_SDA_PORT, SPI_SDA_PIN);
	else
		DL_GPIO_clearPins(SPI_SDA_PORT, SPI_SDA_PIN);
	// SCL = 0;
	DL_GPIO_clearPins(SPI_SCL_PORT, SPI_SCL_PIN);
	// SCL = 1;
	DL_GPIO_setPins(SPI_SCL_PORT, SPI_SCL_PIN);
}

void write(uchar _data, uchar di) // di=0, write command
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

void init_ads(uchar page)
{
	write(page, 0); // set page address
	write(0x10, 0); // Set Higer Column Address
	write(0x00, 0); // Set Lower Column Address
}

void display(uchar a, uchar b)
{
	uchar pag = 0xb0;
	uint i, j;
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

void disp_HZ162(uchar uc_RowNo, uchar uc_ColNo, uchar uc_HZCode)
{
	uchar uc_PageCnt, uc_ColCnt;
	uchar uc_PageAddr;

	uc_PageAddr = 0xB0 | (uc_RowNo * 2);

	for (uc_PageCnt = 0; uc_PageCnt < 2; uc_PageCnt++)
	{
		write(uc_PageAddr, 0); // Set Page Address

		write(0x10 | ((uc_ColNo >> 4) & 0x0F), 0); // Set Upper Bit Column Address
		write(0x00 | (uc_ColNo & 0x0F), 0);				 // Set Low Bit Column Address

		for (uc_ColCnt = 0; uc_ColCnt < 16; uc_ColCnt++)
			write(HZK[uc_HZCode * 32 + uc_PageCnt * 16 + uc_ColCnt], 1);

		uc_PageAddr++;
	}
}

void disp_HZ16(uchar uc_RowNo, uchar uc_ColNo, uchar uc_HZCode)
{
	uchar uc_PageCnt, uc_ColCnt;
	uchar uc_PageAddr;

	uc_PageAddr = 0xB0 | (uc_RowNo * 2);
    uc_HZCode-=32;

	for (uc_PageCnt = 0; uc_PageCnt < 2; uc_PageCnt++)
	{
		write(uc_PageAddr, 0); // Set Page Address

		write(0x10 | ((uc_ColNo >> 4) & 0x0F), 0); // Set Upper Bit Column Address
		write(0x00 | (uc_ColNo & 0x0F), 0);				 // Set Low Bit Column Address

		for (uc_ColCnt = 0; uc_ColCnt < 8; uc_ColCnt++)
			write(ascii_tbl[uc_HZCode*16 + uc_PageCnt * 8 + uc_ColCnt], 1);

		uc_PageAddr++;
	}
}



void set_axis(uint8_t x,uint8_t y)
{
    write(0xB0|y,0);           //y的值为0~8 
    write(0x10|(x>>4),0); 
    write(0x00|(x&0x0F),0); 
}
void disp_HZ16str(uchar uc_RowNo, uchar uc_ColNo, uchar *HZinf, uchar uc_HZCnt)
{
	uchar uc_CharCnt;

	for (uc_CharCnt = 0; uc_CharCnt < uc_HZCnt; uc_CharCnt++)
	{
		disp_HZ16(uc_RowNo, uc_ColNo, HZinf[uc_CharCnt]);
		uc_ColNo = uc_ColNo + 8;
	}
}


void disp_char_ascii(uchar uc_RowNo, uchar uc_ColNo, uchar uc_asciiCode)
{
	uchar uc_PageCnt, uc_ColCnt;
	uchar uc_PageAddr;
    // uc_asciiCode -= 32;
	uc_PageAddr = 0xB0 | (uc_RowNo * 2);

	for (uc_PageCnt = 0; uc_PageCnt < 1; uc_PageCnt++)
	{
		write(uc_PageAddr, 0); // Set Page Address

		write(0x10 | ((uc_ColNo >> 4) & 0x0F), 0); // Set Upper Bit Column Address
		write(0x00 | (uc_ColNo & 0x0F), 0);				 // Set Low Bit Column Address

		for (uc_ColCnt = 0; uc_ColCnt < 16; uc_ColCnt++)
			write(ascii_tbl[uc_asciiCode * 16 + uc_PageCnt * 16 + uc_ColCnt], 1);

		uc_PageAddr++;
	}
}

void disp_str_ascii(uchar uc_RowNo, uchar uc_ColNo, uchar *ascii, uchar uc_asciiCnt)
{
	uchar uc_CharCnt;

	for (uc_CharCnt = 0; uc_CharCnt < uc_asciiCnt; uc_CharCnt++)
	{
		disp_char_ascii(uc_RowNo, uc_ColNo, ascii[uc_CharCnt]);
		uc_ColNo = uc_ColNo + 16;
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

void disp()
{
	
        uint8_t str[5]={0};
        disp_HZ16str(0, 0, "abcdefghijk", 10);
        disp_HZ16str(1, 0, "AHDSDFDSFSF", 10);
		disp_HZ16str(2, 0, "DSVDVSVSDF", 10);
        disp_HZ16str(3, 0, "ab)(&^$^*&^$*", 10);
        // disp_str_ascii(2,0,"     ",5);
        // disp_HZ16(2,0,0);
		delay_ms(80);
}
