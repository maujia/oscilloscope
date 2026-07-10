#ifndef ISR
#define ISR

#include <STM_SETUP.h>
#include <st7735_bm.h> 


extern volatile uint32_t adc_value;
extern volatile uint32_t value_ready;
extern uint8_t abort_flag; 
extern uint8_t source;

#endif