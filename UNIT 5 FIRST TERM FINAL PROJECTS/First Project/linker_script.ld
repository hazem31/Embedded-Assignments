
MEMORY {
    FLASH(RX) : o = 0x08000000 , l = 128K 
    SRAM(RWX) : o = 0x20000000 , l = 20K
}


SECTIONS {
    
    .text :
    {
        *(.vectors*)
        *(.text*)
        *(.rodata*)
        _E_text = .;
    }> FLASH

    .data :
    {
        _S_DATA = .;
        *(.data*)
        . = ALIGN(4);
        _E_DATA = .;
    }> SRAM AT > FLASH
    
    .bss :
    {
        _S_bss = .;
        *(.bss*)
        . = ALIGN(4);
        _E_bss = .;

        . = ALIGN(4);
        . = . + 0x1000;
        _stack_top = .;

    }> SRAM
}   

