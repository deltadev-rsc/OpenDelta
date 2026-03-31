OUTPUT_FORMAT(binary)
ENTRY(_start)

PHDRS
{
    text PT_LOAD FLAGS(5); 
    data PT_LOAD FLAGS(6);
}

SECTIONS 
{
    . = 0x100000;

    .multiboot ALIGN(4) : {
        KEEP(*(.multiboot))
    } :text 

    .fsjump : { *(.fsjump) }
    .fsheaders : { *(.fsheaders) }

    .text : { 
        *(.text)
        *(.text*)
    } :text

    .entry : {
        __entry_start = .;
        *(.entry)
    } :text

    .data : { 
        *(.data)
        *(.data*)
    } :data

    .rodata : {
        *(.rodata)
        *(.rodata*)
    } :rodata
   
    .bss  : { 
        *(.bss)
        *(.bss*)
        *(COMMON)
    } :data 
}
