#include "scope_bm.h"

#define MIN(a,b) (((a) < (b)) ? (a):(b))
#define MAX(a,b) (((a) > (b)) ? (a):(b))

void display_Potentiometer_signal(uint8_t color[2]){

    static uint16_t prev_y[160];
    uint32_t init_signal;
    uint16_t final_signal;
    uint8_t black[2] = {0x00, 0x00};
    static uint8_t first_sweep = 0;  

    for(int i = 5; i < 160; i++){
        if(abort_flag){ break; }
        
        *ADC_CR |= (1 << 2);
        while(value_ready != 1){}
        value_ready = 0;
        if(first_sweep){
            draw_pixel(prev_y[i],i, black);
        }
            
        init_signal = adc_value;
        final_signal = 123 - (init_signal * 123 / 4095);
            
        draw_pixel(final_signal, i,color);
        prev_y[i] = final_signal;
    }
    first_sweep = 1;

    if(abort_flag){
        draw_rectangle(0, 127, 0, 159, black);
        draw_axis(white);
        abort_flag = 0; //reset the flag
        first_sweep = 0;
        switch(source){
            case 0:
                *ADC_SQR1 &= ~(0x1F << 6);
                *ADC_SQR1 |= (0x01<< 6);
                break;
            case 1:
                *ADC_SQR1 &= ~(0x1F << 6);
                *ADC_SQR1 |= (0x02 << 6);
                break;
        }
    }

    
}


