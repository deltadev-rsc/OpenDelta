OUTPUT_FORMAT(binary)
ENTRY(_start)

phys = 0x100000;

PHDRS
{
    text PT_LOAD FLAGS(5); 
    data PT_LOAD FLAGS(6);
}

SECTIONS 
{
    . = phys;

    .multiboot ALIGN(4) : {
        KEEP(*(.multiboot))
    } :text 

    .fsjump : { *(.fsjump) }
    .fsheaders : { *(.fsheaders) }

    .text : { 
        __text_start = .;
        *(.text)
        *(.text*)
    } :text

    .entry : {
        __entry_start = .;
        *(.entry)
    } :text

    .data : {
        __data_start = .;
        *(.data)
        *(.data*)
    } :data

    .rodata : {
        __rodata_start = .;
        *(.rodata)
        *(.rodata*)
    } :data
   
    .bss  : { 
        __bss_start = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
    } :data 

    __end = .;
}
