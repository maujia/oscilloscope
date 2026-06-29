#include <buttons.h>

uint8_t abort_flag = 0; //starts false
uint8_t source = 0;

// Channel Switching 
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // Switch to Channel 1
    if(GPIO_Pin == BTN_CH1_Pin && source != 0){
        // Force absolute states: CH1 ON, CH2 OFF
        HAL_GPIO_WritePin(LED_CH1_GPIO_Port, LED_CH1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_CH2_GPIO_Port, LED_CH2_Pin, GPIO_PIN_RESET);
        
        source = 0;
        abort_flag = 1;
    }
    // Switch to Channel 2
    else if(GPIO_Pin == BTN_CH2_Pin && source != 1){
        // Force absolute states: CH1 OFF, CH2 ON
        HAL_GPIO_WritePin(LED_CH1_GPIO_Port, LED_CH1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_CH2_GPIO_Port, LED_CH2_Pin, GPIO_PIN_SET);
        
        source = 1;
        abort_flag = 1;
    }
}