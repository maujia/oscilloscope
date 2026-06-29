#ifndef ST7735_H
#define ST7735_H
#include <main.h>
#include <stm32f3xx_hal_gpio.h>
#include <stm32f3xx_hal_spi.h>
#include <stm32f3xx_hal_adc.h>
#include <stdint.h>
#include <stdio.h>

extern SPI_HandleTypeDef hspi1;
extern ADC_HandleTypeDef hadc1;
extern uint8_t dc_state;


enum states {LOW, HIGH};

// st7735 controller commands
#define ST7735_SLPOUT 0x11
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_COLMOD 0x3A



void init();
void set_CS_pin();
void set_DC_pin(uint8_t bit);
void st7735_write_cmd(SPI_HandleTypeDef *hspi1,  uint8_t Cmd, uint8_t Size, uint32_t Timeout);
void st7735_write_data(SPI_HandleTypeDef *hspi1,  uint8_t Data, uint8_t Size, uint32_t Timeout);
void draw_pixel(uint16_t x, uint16_t y, uint8_t color[2]);
void write_16bit(SPI_HandleTypeDef *hspi, uint16_t value, uint32_t timeout);
void draw_rectangle(uint16_t x1,uint16_t x2, uint16_t y1,uint16_t y2, uint8_t color[2]);

#endif