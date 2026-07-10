#ifndef ST7735_BM

#define ST7735_BM

#include <STM_SETUP.h>

// ST7735 controller commands
#define ST7735_SLPOUT 0x11
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_COLMOD 0x3A

// Display Color Modes
#define SIXTEEN_BIT 5


// Display driver function prototypes
void st7735_init();
void st7735_draw_pixel(uint16_t x, uint16_t y, uint8_t color[2]);
void st7735_set_DC_pin(uint8_t bit);
void st7735_send_cmd(uint8_t Cmd);
void st7735_send_data(uint8_t Data);
void st7735_16to8(uint16_t Data);
void st7735_draw_rectangle(uint16_t x1,uint16_t x2, uint16_t y1,uint16_t y2, uint8_t color[2]);





enum states {LOW, HIGH};

extern uint8_t dc_state;

extern uint8_t red[2];
extern uint8_t white[2];
extern uint8_t black[2];


#endif