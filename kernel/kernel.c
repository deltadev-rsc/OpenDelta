#include "./lib/stdbase.h"
#include "./lib/types.h"
#include "./lib/multiboot.h"
#include "./lib/string.h"

extern char readp(uint16_t port);
extern void writep(uint16_t port, uint8_t data);
extern void load_idt(uintptr_t *idt_ptr);

struct IDTEntry IDT[IDT_SIZE];
struct multiboot *mboot = NULL;

void IdtInit(void) 
{
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = INTERRUPT_GATE;

    writep(0x20, 0x11);
    writep(0xA0, 0x11);

    writep(0x21, 0x20);
    writep(0xA1, 0x28);

    writep(0x21, 0x00);
    writep(0xA1, 0x00);

    writep(0x21, 0x01);
    writep(0xA1, 0x01);

    writep(0x21, 0xff);
    writep(0xA1, 0xff);

    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(struct IDTEntry) *IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}

void entry_point()
{
    const char *os_name = "OpenDelta v0.1-a\n";
    const char *kern_name = "dltkernel v0.0.6-p\n";
    prints(os_name, WHITE);
    prints(kern_name, WHITE);
    prints("Initializing IDT\n", WHITE);
    IdtInit();
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
