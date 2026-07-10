ENTRY(reset_handler)

MEMORY {
    FLASH (rx): ORIGIN = 0x08000000, LENGTH = 64K
    SRAM (rx): ORIGIN = 0x20000000, LENGTH =  12K  
    CCM SRAM (rx): ORIGIN = 0x10000000, LENGTH = 4K 
}

SECTIONS {
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } >FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    .data :
    {
        . = ALIGN(4);
        _data = .;
        *(.data)

        . = ALIGN(4);
        _edata = .;
    } >SRAM AT> FLASH

    .bss :
    {
        . = ALIGN(4)
    }







}

