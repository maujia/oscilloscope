#include "main.h"
int main(){

    
    
    // turning on the appropriate light initially
    if(source == 0){
        set_pin(LED_CH1_PORT, LED_CH1_PIN, HIGH);
    }
    else if(source == 1){
        set_pin(LED_CH2_PORT, LED_CH2_PIN, HIGH);
    }

    init();
    adc_init();
    st7735_init();

}