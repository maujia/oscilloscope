#ifndef STM_SETUP
#define STM_SETUP

#include <stdint.h>
#include <stdbool.h>
#include <stm32f401ex.h>

































extern volatile uint32_t* const RCC_APB2ENR;

// GPIO_A registers
extern volatile uint32_t* const GPIOA_MODER;
extern volatile uint32_t* const GPIOA_AFRL;
extern volatile uint32_t* const GPIOA_BSRR;

// GPIO_B registers
extern volatile uint32_t* const GPIOB_MODER;
extern volatile uint32_t* const GPIOB_AFRL;
extern volatile uint32_t* const GPIOB_BSRR;

// SPI registers
extern volatile uint32_t* const CR1;
extern volatile uint32_t* const CR2;
extern volatile uint32_t* const SR;
extern volatile uint32_t* const DR;

// SysTick registers
extern volatile uint32_t* const STK_CTRL;
extern volatile uint32_t* const STK_LOAD;
extern volatile uint32_t* const STK_VAL;
extern volatile uint32_t* const STK_CALIB;

// ADC registers
extern volatile uint32_t* const ADC_ISR;
extern volatile uint32_t* const ADC_IER;
extern volatile uint32_t* const ADC_CR;
extern volatile uint32_t* const ADC_CFGR;
extern volatile uint32_t* const ADC_SMPR1;
extern volatile uint32_t* const ADC_SQR1;
extern volatile uint32_t* const ADC_DR;
extern volatile uint32_t* const ADC_CSR;

// Interrupt controller registers
extern volatile uint32_t* const NVIC_ISER0;

// TIM1 registers
extern volatile uint32_t* const TIM1_CR1;
extern volatile uint32_t* const TIM1_PSC;
extern volatile uint32_t* const TIM1_ARR;
extern volatile uint32_t* const TIM1_CCR1;
extern volatile uint32_t* const TIM1_CCER;
extern volatile uint32_t* const TIM1_BDTR;



// Ports
#define PORTA 1 
#define PORTB 2

// GPIO Header Pins PORT A
#define LCD_DC_PIN 2
#define LCD_DC_PORT PORTA
#define LCD_RST_PIN 3
#define LCD_RST_PORT PORTA
#define BTN_CH2_PIN 4
#define BTN_CH2_PORT PORTA


// GPIO Header Pins PORT B
#define LCD_CS_PIN   0
#define LCD_CS_PORT PORTB
#define BTN_CH1_PIN 1
#define BTN_CH1_PORT PORTB

#define LED_CH1_PIN 4
#define LED_CH1_PORT PORTB
#define LED_CH2_PIN 5
#define LED_CH2_PORT PORTB 



// Function prototypes

void init(void);
void adc_init(void);
void transmit_byte(uint8_t *pData);
void set_pin(uint8_t port, uint8_t pin, uint8_t bit);
void delay(uint32_t ms);


#endif 