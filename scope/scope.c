#include <scope.h>

#define MIN(a,b) (((a) < (b)) ? (a):(b))
#define MAX(a,b) (((a) > (b)) ? (a):(b))

uint8_t red[2] = {0x78, 0x00};
uint8_t white[2] = {0xFF, 0xFF};
uint8_t black[2] = {0x00, 0x00};


void display_constant_signal(uint8_t color[2]){
    static uint16_t prev_y[160];
    uint32_t init_signal;
    uint16_t final_signal;
    uint8_t black[2] = {0x00, 0x00};
    static uint8_t first_sweep = 0;  

    for(int i = 5; i < 160; i++){
        if(abort_flag){ break; }
        
        HAL_ADC_Start(&hadc1);
        if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK){
            
            if(first_sweep){
                draw_pixel(prev_y[i],i, black);
            }
            
            init_signal = HAL_ADC_GetValue(&hadc1);
            final_signal = 123 - (init_signal * 123 / 4095);
            
            draw_pixel(final_signal, i,color);
            prev_y[i] = final_signal;
        }
    }
    first_sweep = 1;

    if(abort_flag){
        draw_rectangle(0, 127, 0, 159, black);
        draw_axis(white);
        abort_flag = 0; //reset the flag
        first_sweep = 0;
        switch(source){
            case 0:
                sConfig.Channel = ADC_CHANNEL_1;
                break;
            case 1:
                sConfig.Channel = ADC_CHANNEL_2;
                break;
        }
        HAL_ADC_ConfigChannel(&hadc1, &sConfig);
    }

    
}


void display_PWM_signal(uint8_t color[2]){
    static uint16_t prev_frame_y[160];
    uint32_t init_signal;
    uint16_t final_signal;
    uint8_t black[2] = {0x00, 0x00};
    static uint8_t first_sweep = 0;

    uint16_t curr_frame_prev = 0;
    static uint16_t prev_frame_prev = 0; // Tracks the OLD sweep's previous value


    for(int i = 5; i < 160; i++){
        if(abort_flag){ break; }
        
        HAL_ADC_Start(&hadc1);
        if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK){

            init_signal = HAL_ADC_GetValue(&hadc1);
            final_signal = 110 - (init_signal * (110 - 13) / 4095) + 13;

            // SAVE the old value from the array BEFORE we overwrite it below
            uint16_t current_old_y = prev_frame_y[i]; 

            // 1. ERASE the exact line we drew last time
            if(first_sweep){
                uint16_t erase_start, erase_end;
                if(i == 5){
                    draw_pixel(current_old_y, i, black);
                } else {
                    // Use prev_frame_prev, which safely holds the un-overwritten old value
                    erase_start = MIN(prev_frame_prev, current_old_y);
                    erase_end   = MAX(prev_frame_prev, current_old_y);
                    for(int j = erase_start; j <= erase_end; j++){
                        draw_pixel(j, i, black);
                    }
                }
            }

            // 2. DRAW the new line
            uint16_t draw_start, draw_end;
            if(i == 5){
                draw_pixel(final_signal, i, color);
            } else {
                draw_start = MIN(curr_frame_prev, final_signal);
                draw_end   = MAX(curr_frame_prev, final_signal);
                for(int j = draw_start; j <= draw_end; j++){
                    draw_pixel(j, i, color);
                }
            }

            // 3. UPDATE all state variables for the next iteration
            prev_frame_y[i] = final_signal;  // For the next sweep to erase
            curr_frame_prev = final_signal;  // For the current sweep to draw lines
            prev_frame_prev = current_old_y; // For the next iteration to erase lines safely
        }
    }
    first_sweep = 1;

    if(abort_flag){
        draw_rectangle(0, 127, 0, 159, black);
        draw_axis(white);
        abort_flag = 0;
        first_sweep = 0;
        switch(source){
            case 0: sConfig.Channel = ADC_CHANNEL_1; break;
            case 1: sConfig.Channel = ADC_CHANNEL_2; break;
        }
        HAL_ADC_ConfigChannel(&hadc1, &sConfig);
    }
}


void draw_axis(uint8_t color[2]){

    // x-axis

    for(int a = 0; a < 127; a++){

        draw_pixel(a, 2, color);

    }

    // y-axis

    for(int b = 0; b < 159; b++){

        draw_pixel(2, b, color);

    }

}



