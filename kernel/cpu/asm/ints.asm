%include "asm/isr.asm"
%include "asm/irq.asm"

extern isr_handler
extern irq_handler


%macro ISR_NOERRORCODE 1

global ISR%1
ISR%1:
    push 0
    push %1
    jmp isr_common_stub

%endmacro

%macro ISR_ERRORCODE 1

global isr%1
isr%1:
    push %1
    hmp isr_common_stub

%endmacro
