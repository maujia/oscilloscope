#include "st7735_bm.h"


uint8_t red[2] = {0x78, 0x00};
uint8_t white[2] = {0xFF, 0xFF};
uint8_t black[2] = {0x00, 0x00};


void st7735_init()
{
    set_pin(LCD_RST_PORT, LCD_RST_PIN, LOW);
    delay(120); // reset controller
    set_pin(LCD_CS_PORT, LCD_CS_PIN, LOW);
    
    // wait 120 ms
    set_pin(LCD_RST_PORT, LCD_RST_PIN, HIGH);
    delay(120);

    // set_CS_pin(); remove from autoset functionality

    // pull out of sleep
    st7735_send_cmd(ST7735_SLPOUT);
    delay(120);
    // set color mode
    st7735_send_cmd(ST7735_COLMOD);
    st7735_send_data(SIXTEEN_BIT);

    // turn display on
    st7735_send_cmd(ST7735_DISPON);
    
}

void st7735_set_DC_pin(uint8_t bit){
    set_pin(LCD_DC_PORT, LCD_DC_PIN, bit);
}

void st7735_send_cmd(uint8_t Cmd){
    // set LOW for cmd
    
    st7735_set_DC_pin(LOW);    
    transmit_byte(&Cmd);
}

void st7735_send_data(uint8_t Data){
    st7735_set_DC_pin(HIGH);
    transmit_byte(&Data);
    
    
}

void st7735_draw_pixel(uint16_t x, uint16_t y, uint8_t color[2]){
    // send CASET cmd
    st7735_send_cmd(ST7735_CASET);
    
    // x start
    st7735_16to8(x);
    // x end
    st7735_16to8(x);

    st7735_send_cmd(ST7735_RASET);
    // y start
    st7735_16to8(y);
    // y end
    st7735_16to8(y);

    st7735_send_cmd(ST7735_RAMWR);
    st7735_send_data(color[0]);
    st7735_send_data(color[1]);
}

void st7735_16to8(uint16_t Data){
    uint8_t high_byte, low_byte;
    low_byte = (uint8_t)(Data & 0x00FF);
    high_byte = (uint8_t)(Data >> 8);
    st7735_send_data(high_byte);
    st7735_send_data(low_byte);
}

void st7735_draw_rectangle(uint16_t x1,uint16_t x2, uint16_t y1,uint16_t y2, uint8_t color[2]){
    // set columns
    st7735_send_cmd(ST7735_CASET);
    
    // x start
    st7735_16to8(x1);
    // x end
    st7735_16to8(x2);

    // set rows
    st7735_send_cmd(ST7735_RASET);
    // y start
    st7735_16to8(y1);
    // y end
    st7735_16to8(y2);

    st7735_send_cmd(ST7735_RAMWR);
    for(int i = 0; i < ((x2-x1+1)*(y2-y1+1)); i++){
        st7735_send_data(color[0]);
        st7735_send_data(color[1]);
    }
}
