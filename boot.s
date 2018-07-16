/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:


.section .text
.global _start
.type _start, @function

//.globl printX
//extern printX
.globl gdt
gdt:
	.zero 8 //NULL
	.byte 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x9A, 0xCF, 0x0 //KERNEL CODE 
	.byte 0xFF, 0xFF, 0x0, 0x0, 0x0, 0x92, 0xCF, 0x0 //KERNEL DATA
	.byte 0xFF, 0xFF, 0x0, 0x0, 0x0, 0xFA, 0xCF, 0x0 //USER CODE
	.byte 0xFF, 0xFF, 0x0, 0x0, 0x0, 0xF2, 0xCF, 0x0 //USER CODE
gdtEnd:

.globl gdtDescriptor
gdtDescriptor:
	.short	gdtEnd - gdt - 1
	.long	gdt


.globl int_handler
int_handler:
	mov $0x10, %ax
	mov %ax, %gs
	movl $0x02720174, %gs:0xB8000
	hlt

.p2align 4
idt:
	.skip 50*8
		

idtr:
	.short	(50*8)-1
	.long	idt


handlePress:
	/*
	mov $0x10, %bx
	mov %bx, %gs
	//xor %eax, %eax
	movw	$0x0130, %ax
	inb	$0x60, %al
	mov	kbdus + %al, %al
	and	$0x01FF, %ax
	movw %ax, %gs:0xB8000
	*/
	pushal
	cld
	call printX
	popal
	iret

.globl test
test:
	lidt	idtr	
	call 	picRemap
	sti
	movl 	$handlePress, %eax
	
	//movl 	$int_handler, %eax
	mov		%ax, idt+33*8
	movw	$0x8, idt+33*8+2
	movw	$0x8e00, idt+33*8+4
	shr		$16, %eax
	movw	%ax, idt+33*8+6

	jmp 	cont	
	

.globl picRemap
picRemap:
	//begin initialization	
	movb	$0x11, 	%al
	outb	%al, $0x20
	outb	%al, $0xA0
	
	//set offsets
	movb	$0x20, 	%al
	outb	%al, 	$0x21
	movb	$0x28, 	%al
	outb	%al, 	$0xA1

	//set up slave pic
	movb	$4, %al
	outb	%al, $0x21
	movb	$2, %al
	outb	%al, $0xA1

	//8086 mode
	movb	$0x1, %al
	outb %al, $0x21
	outb %al, $0xA1

	movb	$0xFD, %al
	outb	%al, $0x21
	outb	%al, $0xA1
	ret
	
_start:
	mov $stack_top, %esp
	
	lgdt	gdtDescriptor
	movw 	$0x10, %ax
	movw 	%ax, %ds
	movw 	%ax, %es
	movw 	%ax, %fs
	movw 	%ax, %gs
	movw 	%ax, %ss
	jmp 	$0x08,$flush
flush:
	//call	picRemap
	jmp 	test
	
cont:
	pushl %eax
	pushl %ebx
	call kernel_main
/*
	movl	$int_handler, %eax
	mov		%ax, idt+49*8
	movw	$1, idt+49*8+2
	movw	$0x8e00, idt+49*8+4
	shr		$16, %eax
	mov		%ax, idt+49*8+6
	lidt	idtr
	int		$49
*/
	//call test
	//call loadIdt
	//call picRemap
	

	cli
1:	hlt
	jmp 1b

.size _start, . - _start
