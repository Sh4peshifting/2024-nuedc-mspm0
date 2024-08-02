#include "disp.h"

extern float volt_rms;
extern float curr_rms;
extern float AP,PF;
extern float curr_thd;

float volt_disp, curr_disp, power_disp, pf_disp, thd_disp;
uint8_t page;

void disp_param_calib()
{
    volt_disp = volt_rms;
    curr_disp = curr_rms;
    power_disp = AP;
    pf_disp = PF;
    thd_disp = curr_thd;
}

void disp_printf(uint8_t disp_row, uint8_t disp_col, uint8_t disp_length, char *fmt, ...)
{
    char buf[20] = {0};
    va_list ap;
    va_start(ap,fmt);
    vsprintf(buf,fmt,ap);
    va_end(ap);

    disp_str_ascii(disp_row, disp_col, buf, disp_length);


}

void disp_proc()
{
    uint8_t str[16]={0};
    CLR_SCREEN;
    switch (page) {
        case 0:
            disp_printf(0, 0, 16, "Urms=%.2fV", volt_disp);
            disp_printf(1, 0, 16, "Irms=%.3fA", curr_rms);
            disp_printf(2, 0, 16, "P=%.3fW", power_disp);
            disp_printf(3, 0, 16, "PF=%.3f", pf_disp);
            // snprintf(str, 16,"Urms=%.3f       ", volt_disp);
            // disp_str_ascii(0, 0, str, 16);
            // snprintf(str, 16, "Irms=%.3f       ", curr_rms);
	        // disp_str_ascii(1, 0, str, 16);
            // snprintf(str, 16, "P=%.3f       ", power_disp);
            // disp_str_ascii(2, 0, str, 16);
            // snprintf(str, 16, "PF=%.3f       ", pf_disp);
	        // disp_str_ascii(3, 0, str, 16);

        break;
        case 1:
            disp_printf(0, 0, 16, "THD=%.3f%%", thd_disp);
            // snprintf(str, 16, "THD=%.3f       ", thd_disp);
            // disp_str_ascii(0, 0, str, 16);
        break;
        case 2:


        break;
    
    }

}