#include "./lib/stdbase.h"
#include "./lib/types.h"
#include "./lib/multiboot.h"
#include "./lib/string.h"
#include "./lib/isr.h"
#include "./lib/idt.h"

extern char readp(uint16_t port);
extern void writep(uint16_t port, uint8_t data);
extern void load_idt(uintptr_t *idt_ptr);

struct IDTEntry IDT[IDT_SIZE];
struct multiboot *mboot = NULL;

void idt_init(void) 
{
    unsigned long kbaddress;
    unsigned long idt_address;
    unsigned long idt_ptr[2];
}

void entry_point()
{
    prints("OS: OpenDelta\n", WHITE);
    prints("Kernel: dltkernel\n", WHITE);
}

void kmain()
{
    while (TRUE) {
        entry_point();
        for (volatile uint32_t i = 0; i < 10000000; i++) {
            __asm__ __volatile__ ("hlt");
        }
    }
}
