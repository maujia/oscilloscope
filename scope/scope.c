#include <scope.h>









uint16_t prev_y[160];
void display_signal(uint8_t color[2]){
    // sine wave function:
    uint32_t init_signal;
    uint16_t final_signal, prev_signal;
    uint8_t black[2] = {0x00, 0x00};
    static uint8_t first_sweep = 0;  
    //uint8_t time  = 0; // consider this in terms of milliseconds x-coord
    
    enum range_conversion{input_min, input_max = 4095, output_min = 127, output_max = 0};

    //draw_rectangle(0, 127, 0, 159, black); // initial clear

    for(int i = 0; i < 160; i++){
        // get signal
        HAL_ADC_Start(&hadc1);
        
        if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK){

            if(first_sweep){
                draw_pixel(prev_y[i], i, black);
            }
            init_signal = HAL_ADC_GetValue(&hadc1);
            final_signal = output_min + (init_signal -input_min) * (output_max - output_min) / (input_max - input_min);
            draw_pixel(final_signal,i, color); // flipped the coordinates temporarily
            prev_y[i] = final_signal; 
            HAL_Delay(6);
            
            
        
        }
    }
    first_sweep = 1;
    
}