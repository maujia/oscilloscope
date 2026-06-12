#include "st7735.h"

uint8_t dc_state = LOW;


void init(){

    // Using GM[2:0]=“011” Reset Table

    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(120);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(120);
    set_CS_pin();
    
    st7735_write_cmd(&hspi1, ST7735_SLPOUT, 1, 100);
    HAL_Delay(120);
    st7735_write_cmd(&hspi1, ST7735_COLMOD, 1, 100);
    st7735_write_data(&hspi1, 5, 1, 100);
    st7735_write_cmd(&hspi1, ST7735_DISPON, 1, 100);
}

void set_CS_pin(){
     // set chip select pin to low to tell the controller in the display that you are talking to it
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
}

void set_DC_pin(uint8_t bit){
    if(bit){
        HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
        dc_state = HIGH;
    }
    else {
        HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
        dc_state = LOW;
    }
}

void st7735_write_cmd(SPI_HandleTypeDef *hspi1, uint8_t Cmd, uint8_t Size, uint32_t Timeout){
    if(dc_state == HIGH){
        set_DC_pin(LOW);
    }
    HAL_SPI_Transmit(hspi1, &Cmd, Size, Timeout);
}

void st7735_write_data(SPI_HandleTypeDef *hspi1, uint8_t Data, uint8_t Size, uint32_t Timeout){
    if(dc_state == LOW){
        set_DC_pin(HIGH);
    }
    HAL_SPI_Transmit(hspi1, &Data, Size, Timeout);
}


void write_16bit(SPI_HandleTypeDef *hspi, uint16_t value, uint32_t timeout) {
    uint8_t high = value >> 8;
    uint8_t low = value & 0xFF;
    st7735_write_data(hspi, high, 1, timeout);
    st7735_write_data(hspi, low, 1, timeout);
}

void draw_pixel(uint16_t x, uint16_t y, uint8_t color[2]){
    st7735_write_cmd(&hspi1, ST7735_CASET, 1, 100);
    write_16bit(&hspi1, x, 100);
    write_16bit(&hspi1, x, 100);
    
    st7735_write_cmd(&hspi1, ST7735_RASET, 1, 100);
    write_16bit(&hspi1, y, 100);
    write_16bit(&hspi1, y, 100);
    
    st7735_write_cmd(&hspi1, ST7735_RAMWR, 1, 100);
    st7735_write_data(&hspi1, color[0], 1, 100);
    st7735_write_data(&hspi1, color[1], 1, 100);
}

void draw_rectangle(uint16_t x1,uint16_t x2, uint16_t y1,uint16_t y2, uint8_t color[2]){
    st7735_write_cmd(&hspi1, ST7735_CASET, 1, 100);
    write_16bit(&hspi1, x1, 100);
    write_16bit(&hspi1, x2, 100);
    
    st7735_write_cmd(&hspi1, ST7735_RASET, 1, 100);
    write_16bit(&hspi1, y1, 100);
    write_16bit(&hspi1, y2, 100);
    
    st7735_write_cmd(&hspi1, ST7735_RAMWR, 1, 100);

    for(int i = 0; i <(x2*y2); i++){
        st7735_write_data(&hspi1, color[0], 1, 100);
        st7735_write_data(&hspi1, color[1], 1, 100);
    }
}