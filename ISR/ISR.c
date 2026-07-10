#include "ISR.h"

volatile uint32_t adc_value;
volatile uint32_t value_ready;
uint8_t abort_flag = 0; //starts false
uint8_t source = 0;


void ADC1_2_IRQHandler(){
    adc_value = *ADC_DR;
    *ADC_ISR &= ~(1 << 2); 
    value_ready = 1;    
}

void EXTI1_IRQHandler(){
    if(source != 0){
        set_pin(LED_CH2_PORT, LED_CH2_PIN, LOW);
        set_pin(LED_CH1_PORT, LED_CH1_PIN, HIGH);
        source = 0;
        abort_flag = 1;
    }
}

void EXTI4_IRQHandler(){
    if(source != 1){
        set_pin(LED_CH1_PORT, LED_CH1_PIN, LOW);
        set_pin(LED_CH2_PORT, LED_CH2_PIN, HIGH);
        source = 1;
        abort_flag = 1;
    }

}
