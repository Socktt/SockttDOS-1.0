# Object files
OBJS = kernel_entry.o kernel.o idt.o isr.o isrc.o irq.o irqc.o timer.o kb.o port_io.o vga.o system.o
# Files to remove during clean
REMOVABLE = kernel_entry.o kernel.o idt.o isr.o isrc.o irq.o irqc.o timer.o kb.o port_io.o vga.o system.o full_kernel.bin empty_end.bin Socktt95.bin boot.bin
# Source Files
SRC_FILES = kernel.c idt.c isr.c irq.c kb.c port_io.c vga.c system.c boot.asm empty_end.asm isr.asm irq.asm
# Compiler options
COMPILER_OPTIONS = -ffreestanding -m32 -g -c -w
# Linker options
LINKER_OPTIONS = -Ttext 0x1000 --oformat binary

all: $(SRC_FILES)
	nasm -f bin boot.asm -o boot.bin
	nasm -f bin empty_end.asm -o empty_end.bin
	nasm -f elf kernel_entry.asm -o kernel_entry.o
	nasm -f elf isr.asm -o isr.o
	nasm -f elf irq.asm -o irq.o
	i386-elf-gcc $(COMPILER_OPTIONS) "kernel.c" -o "kernel.o"
	i386-elf-gcc $(COMPILER_OPTIONS) "idt.c" -o "idt.o"
	i386-elf-gcc $(COMPILER_OPTIONS) "isr.c" -o "isrc.o"
	i386-elf-gcc $(COMPILER_OPTIONS) "irq.c" -o "irqc.o"
	i386-elf-gcc $(COMPILER_OPTIONS) "timer.c" -o "timer.o"
	i386-elf-gcc $(COMPILER_OPTIONS) "kb.c" -o "kb.o"
	i386-elf-gcc $(COMPILER_OPTIONS) "port_io.c" -o "port_io.o"
	i386-elf-gcc $(COMPILER_OPTIONS) "vga.c" -o "vga.o"
	i386-elf-gcc $(COMPILER_OPTIONS) "system.c" -o "system.o"
	i386-elf-ld -o "full_kernel.bin" $(OBJS) $(LINKER_OPTIONS)
	cat "boot.bin" "full_kernel.bin" "empty_end.bin" > "Socktt95.bin"
	qemu-system-x86_64 Socktt95.bin

clean: $(REMOVABLE)
	rm $(REMOVABLE)