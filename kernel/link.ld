OUTPUT_FORMAT(binary)
ENTRY(_start)

PHDRS
{
    text PT_LOAD FLAGS(5);
    data PT_LOAD FLAGS(6);
}

SECTIONS 
{
    . = 0x10000;

    .multiboot ALIGN(4) : {
        KEEP(*(.multiboot))
    } :text 

    .text : { 
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
    } :text

    .entry : {
        __entry_start = .;
        *(.entry)
    } :text

    .data : { 
        *(.data)
        *(.data*)
    } :data
    
    .bss  : { 
        *(.bss)
        *(.bss*)
        *(COMMON)
    } :data
}
