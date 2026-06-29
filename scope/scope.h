#include <st7735.h>

/* 
In this situation i dont think you would need to have define guards because you are including a header that 
already has header guards.
*/ 

void display_PWM_signal(uint8_t color[2]);
void display_constant_signal(uint8_t color[2]);
void draw_axis(uint8_t color[2]);


extern uint8_t red[2];
extern uint8_t white[2];
extern uint8_t black[2];
#include <buttons.h>
