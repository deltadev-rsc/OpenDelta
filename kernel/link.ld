OUTPUT_FORMAT(elf32-i386)
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

    .heap : {
        _heap_start = .;
        . = . + 32 * 1024 * 1024;
        _heap_end = .;
    } :data

    __end = .;
}
