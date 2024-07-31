#ifndef __SCREEN_DRIVER_H__
#define __SCREEN_DRIVER_H__

#include "ti_msp_dl_config.h"

const uint8_t HZK[] =
		{
				0x10, 0x60, 0x02, 0x8C, 0x00, 0x0E, 0x22, 0x12, 0x0A, 0xC2, 0x0A, 0x12, 0x22, 0x0E, 0x00, 0x00,
				0x04, 0x04, 0x7E, 0x01, 0x20, 0x21, 0x11, 0x09, 0x05, 0xFF, 0x05, 0x09, 0x11, 0x21, 0x20, 0x00, /*"??",0*/

				0x20, 0x20, 0x20, 0xFF, 0x20, 0x20, 0x00, 0xFF, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xFF, 0x00, 0x00,
				0x10, 0x30, 0x10, 0x0F, 0x08, 0x88, 0x60, 0x1F, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xFF, 0x00, 0x00, /*"??",1*/

				0x00, 0x00, 0xFE, 0x92, 0x92, 0x92, 0x92, 0xFE, 0x92, 0x92, 0x92, 0x92, 0xFE, 0x00, 0x00, 0x00,
				0x40, 0x38, 0x01, 0x00, 0x3C, 0x40, 0x40, 0x42, 0x4C, 0x40, 0x40, 0x70, 0x05, 0x08, 0x30, 0x00, /*"?",2*/

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
				0x00, 0x00, 0x00, 0x3F, 0x10, 0x10, 0x10, 0x10, 0x3F, 0x00, 0x40, 0x80, 0x7F, 0x00, 0x00, 0x00 /*"?",10*/
};

const uint8_t SMWDZ[] =
		{
				0x02, 0x03, 0x04, 0x05, 0x06};


#endif