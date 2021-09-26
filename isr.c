#include "system.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();


void isrs_install()
{
    idt_set_gate(0, (unsigned)isr0, 8, 0x8e);
    idt_set_gate(1, (unsigned)isr1, 8, 0x8e);
    idt_set_gate(2, (unsigned)isr2, 8, 0x8e);
    idt_set_gate(3, (unsigned)isr3, 8, 0x8e);
    idt_set_gate(4, (unsigned)isr4, 8, 0x8e);
    idt_set_gate(5, (unsigned)isr5, 8, 0x8e);
    idt_set_gate(6, (unsigned)isr6, 8, 0x8e);
    idt_set_gate(7, (unsigned)isr7, 8, 0x8e);
    idt_set_gate(8, (unsigned)isr8, 8, 0x8e);
    idt_set_gate(9, (unsigned)isr9, 8, 0x8e);
    idt_set_gate(10, (unsigned)isr10, 8, 0x8e);
    idt_set_gate(11, (unsigned)isr11, 8, 0x8e);
    idt_set_gate(12, (unsigned)isr12, 8, 0x8e);
    idt_set_gate(13, (unsigned)isr13, 8, 0x8e);
    idt_set_gate(14, (unsigned)isr14, 8, 0x8e);
    idt_set_gate(15, (unsigned)isr15, 8, 0x8e);
    idt_set_gate(16, (unsigned)isr16, 8, 0x8e);
    idt_set_gate(17, (unsigned)isr17, 8, 0x8e);
    idt_set_gate(18, (unsigned)isr18, 8, 0x8e);
    idt_set_gate(19, (unsigned)isr19, 8, 0x8e);
    idt_set_gate(20, (unsigned)isr20, 8, 0x8e);
    idt_set_gate(21, (unsigned)isr21, 8, 0x8e);
    idt_set_gate(22, (unsigned)isr22, 8, 0x8e);
    idt_set_gate(23, (unsigned)isr23, 8, 0x8e);
    idt_set_gate(24, (unsigned)isr24, 8, 0x8e);
    idt_set_gate(25, (unsigned)isr25, 8, 0x8e);
    idt_set_gate(26, (unsigned)isr26, 8, 0x8e);
    idt_set_gate(27, (unsigned)isr27, 8, 0x8e);
    idt_set_gate(28, (unsigned)isr28, 8, 0x8e);
    idt_set_gate(29, (unsigned)isr29, 8, 0x8e);
    idt_set_gate(30, (unsigned)isr30, 8, 0x8e);
    idt_set_gate(31, (unsigned)isr31, 8, 0x8e);
    
}

unsigned char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Alignment Check Exception",
    "Machine Check Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

void fault_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
        print(exception_messages[r->int_no]);
        print(" Error. System halted!\n");
        for (;;);
    }
}