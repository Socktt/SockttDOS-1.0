#include "idt.h"
#include "vga.h"
#include "system.h"
#include "kb.h"
#include "prompt.h"

extern void kernMain(){
    idt_install();
    irq_install();
    //timer_phase(1);
    //timer_install();
    keyboard_install();
    __asm__ __volatile__ ("sti"); 

    print("SockttDOS 1.0\n");
    promptInit();
    return;
}