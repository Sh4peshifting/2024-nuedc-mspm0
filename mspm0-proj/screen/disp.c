#include "disp.h"

extern float volt_rms;
extern float curr_rms;
extern float AP,PF;
extern float curr_thd;
extern float harmonic[16];

float volt_disp, curr_disp, power_disp, pf_disp, thd_disp;
uint8_t page, harm_page;

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

void disp_thd()
{
    switch (harm_page) {
        case 0:
            disp_printf(0, 0, 16, "THD=%.1f%%", curr_thd*100);
            disp_printf(1, 0, 16, "2nd:%.3fA", harmonic[2]);
            disp_printf(2, 0, 16, "3th:%.3fA", harmonic[3]);
            disp_printf(3, 0, 16, "4th:%.3fA", harmonic[4]);
        break;
        case 1:
            disp_printf(0, 0, 16, "5th:%.3fA", harmonic[5]);
            disp_printf(1, 0, 16, "6th:%.3fA", harmonic[6]);
            disp_printf(2, 0, 16, "7th:%.3fA", harmonic[7]);
            disp_printf(3, 0, 16, "8th:%.3fA", harmonic[8]);
        break;
        case 2:
            disp_printf(0, 0, 16, "9th:%.3fA", harmonic[9]);
            disp_printf(1, 0, 16, "10th:%.3fA", harmonic[10]);
            disp_printf(2, 0, 16, "11th:%.3fA", harmonic[11]);
            disp_printf(3, 0, 16, "12th:%.3fA", harmonic[12]);
        break;
        
    }
}

void disp_proc()
{
    uint8_t str[16]={0};
    switch (page) {
        case 0:
            disp_printf(0, 0, 16, "Urms=%.2fV", volt_rms);
            disp_printf(1, 0, 16, "Irms=%.3fA", curr_rms);
            disp_printf(2, 0, 16, "P=%.3fW", AP);
            disp_printf(3, 0, 16, "PF=%.3f", PF);
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
            disp_thd();
            // snprintf(str, 16, "THD=%.3f       ", thd_disp);
            // disp_str_ascii(0, 0, str, 16);
        break;
        case 2:
            

        break;
    
    }

}