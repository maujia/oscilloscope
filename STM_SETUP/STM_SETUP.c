#include "STM_SETUP.h"

void init(){
    // Enabling the clock for GPIOA, GPIOB
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
    
    // Enabling clock for SPI1
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    
    // Enabling clock for SYSCFG
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Setting GPIOA pins PA5 and PA7 to SPI SCK and MOSI 
    // Setting the SCK and MOSI pin to Alternate Function mode in GPIOA_GPIOx_MODER
    GPIOA->MODER &= ~(0x3 << 10); // PA5 SPI_SCK
    GPIOA->MODER &= ~(0x3 << 14); // PA7 SPI_MOSI
    GPIOA->MODER &= ~(0x3 << 0); // PA0 ADC1_IN1
    GPIOA->MODER &= ~(0x3 << 2); // PA1 ADC1_IN2
    GPIOA->MODER &= ~(0x3 << 8); // PA4 BTN_CH2
    
    GPIOB->MODER &= ~(0x3 << 2);  // PB1 BTN_CH1
    GPIOB->MODER &= ~(0x3 << 8); // PB4 LED_CH1
    GPIOB->MODER &= ~(0x3 << 10); // PB5 LED_CH2

    GPIOA->MODER |= (0x2 << 10); // 10: Alternate function mode - SPI_SCK
    GPIOA->MODER |= (0x2 << 14); // 10: Alternate function mode - SPI_MOSI
    GPIOA->MODER |= (0x3 << 0); // 11: Analog mode - ADC1_IN1
    GPIOA->MODER |= (0x3 << 2);// 11: Analog mode - ADC1_IN2
    GPIOA->MODER |= (0x0 << 8); // 00: Input mode - BTN_CH2
   
    GPIOB->MODER |= (0x1 << 8); // 01: General purpose output mode - LED_CH1
    GPIOB->MODER |= (0x1 << 10); // 01: General purpose output mode - LED_CH2
    GPIOB->MODER |= (0x0 << 2); // 00: Input Mode - BTN_CH1

    // Enabling interrupts for both buttons
    NVIC->ISER[0] |= (1 << 7) | (1 << 10);

    // Alternate Function selection for PA5 and PA7
    GPIOA->AFRL &= ~(0xF << 20);  // mask:  1111 1111 0000 1111 1111 1111 1111 1111
    GPIOA->AFRL &= ~(0xF << 28); // mask: 1111 0000 1111 1111 1111 1111 1111 1111
    GPIOA->AFRL |= (0x5 << 20); // AF5 = SPI1
    GPIOA->AFRL |= (0x5 << 28); // AF5 = SPI1

    // EXTI registers
    EXTI->IMR |= (1 << 1) | (1 << 4);
    EXTI->RTSR |= (1 << 1) | (1 << 4);

    // Enabling relevant spi registers bits 
    SPI1->CR1 |= (0 << 0) | (0 << 1) | (1 << 2) | (0x2 << 3) | (1 << 6) | (1 << 9) | (1 << 14) | (1 << 15);
    SPI1->CR2 |= (0x7 << 8);

    // Enabling clocksource as AHB/8 for SysTick timer
    SysTick->CTRL |= (1 << 2);

    // Selecting the source inputs for the EXTI1 and EXTI4 interrupts
    SYSCFG->EXTICR[0] |= (0x001 << 4); // EXTI1 = PB1
    SYSCFG->EXTICR[1] |= (0x000 << 0); // EXTI4 = PA4
}

void dma_init(){
    // Enable DMA2 clock
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
    
    // Wait for DMA2 stream0 to be disabled
    DMA2_Stream0->CR &= ~DMA_SxCR_EN;
    while(DMA2_Stream0->CR & DMA_SxCR_EN);
    
    // Clear all stream0 flags
    DMA2->LIFCR |= DMA_LIFCR_CFEIF0 | DMA_LIFCR_CDMEIF0 | DMA_LIFCR_CTEIF0 | DMA_LIFCR_CHTIF0 | DMA_LIFCR_CTCIF0;
    
    // Set addresses
    DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;  // Peripheral address
    DMA2_Stream0->M0AR = (uint32_t)buffer0;   // Buffer 0
    DMA2_Stream0->M1AR = (uint32_t)buffer1;   // Buffer 1
    
    // Set number of transfers
    DMA2_Stream0->NDTR = 2000;
    
    // Configure control register
    DMA2_Stream0->CR &= ~DMA_SxCR_CHSEL; // Clear channel
    DMA2_Stream0->CR |= (0 << 25); // Channel 0 (ADC1)
    DMA2_Stream0->CR &= ~DMA_SxCR_DIR; // Peripheral-to-memory
    DMA2_Stream0->CR &= ~DMA_SxCR_PINC; // Peripheral no increment
    DMA2_Stream0->CR |= DMA_SxCR_MINC; // Memory increment
    DMA2_Stream0->CR &= ~DMA_SxCR_PSIZE; // Clear
    DMA2_Stream0->CR |= DMA_SxCR_PSIZE_0; // PSIZE = 16-bit
    DMA2_Stream0->CR &= ~DMA_SxCR_MSIZE; // Clear
    DMA2_Stream0->CR |= DMA_SxCR_MSIZE_0; // MSIZE = 16-bit
    DMA2_Stream0->CR |= DMA_SxCR_CIRC; // Circular mode
    DMA2_Stream0->CR |= DMA_SxCR_DBM; // Double buffer mode
    DMA2_Stream0->CR &= ~DMA_SxCR_PL; // Clear
    DMA2_Stream0->CR |= DMA_SxCR_PL_1; // Priority = high
    DMA2_Stream0->CR |= DMA_SxCR_TCIE; // Transfer complete interrupt
    
    // Enable stream
    DMA2_Stream0->CR |= DMA_SxCR_EN;
}

void adc_init(){
    // Calibrate
    ADC1->CR2 |= ADC_CR2_ADON; // Enable ADC
    ADC1->CR2 |= ADC_CR2_CAL;  // Start calibration
    while(ADC1->CR2 & ADC_CR2_CAL); // Wait for calibration
    
    // Configure
    ADC1->CR1 &= ~ADC_CR1_SCAN; // Single channel
    ADC1->CR2 &= ~(ADC_CR2_EXTEN | ADC_CR2_EXTSEL); // Software trigger
    ADC1->CR2 |= ADC_CR2_CONT; // Continuous mode
    
    // Sample time
    ADC1->SMPR2 = 0; // 3 cycles for channel 0
    
    // Sequence
    ADC1->SQR1 = 0; // 1 conversion
    ADC1->SQR3 = 0; // Channel 0 first
    
    // Enable interrupt
    NVIC->ISER[0] |= (1 << 18); // ADC IRQ 18
    ADC1->CR1 |= ADC_CR1_EOCIE; // End of conversion interrupt
}

void clock_init() {
    // Use HSI (16MHz) -> PLL -> 168MHz
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC; // HSI as source (default)
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
    RCC->PLLCFGR |= (16 << 0); // PLLM = 16 (16MHz/16 = 1MHz)
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
    RCC->PLLCFGR |= (336 << 6); // PLLN = 336 (1MHz * 336 = 336MHz)
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
    RCC->PLLCFGR |= (0 << 16); // PLLP = 2 (336/2 = 168MHz)
    
    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));
    
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

void transmit_byte(uint8_t *pData){   
    while((!(SPI1->SR & SPI_SR_TXE))){}
    SPI1->DR = *pData;
    while((SPI1->SR & SPI_SR_BSY)){}
}

void set_pin(uint8_t port, uint8_t pin, uint8_t bit){
    switch(port){
        case(PORTA):
            if (bit) {
                GPIOA->BSRR = (1 << pin);
            }else {
                GPIOA->BSRR = (1 << (pin + 16));
            }
            break;
        case(PORTB):
            if (bit) {
                GPIOB->BSRR = (1 << pin);
            }else {
                GPIOB->BSRR = (1 << (pin + 16));
            }
            break;
    }
}

void delay(uint32_t ms){
    SysTick->LOAD = (168000000 / 1000) * ms - 1;
    SysTick->VAL = 0;
    SysTick->CTRL |= (1 << 0);
    while((!(SysTick->CTRL & (1 << 16))));
    SysTick->CTRL &= ~(1 << 0);
    SysTick->VAL = 0;
}