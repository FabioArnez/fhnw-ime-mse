/*------------------------
  bigBang
  (c) H.Buchmann FHNW 2011
  demonstrates .booting
               .outline of an image
  see ram.ld linker script	       
  $Id$
  [1] literature/ARM-Architecture-Reference-Manual.pdf
  TODO: make a demo for .onSWI
	set the different stacks properly
	set the exception stacks IRQStack alread set
	move stack segment into an own file/module
	                   or even into ram.ld
------------------------*/

/*----------------------------------------the Mode bits */
USER_MODE      =0b10000               /* see [1] A2.5.7 */
FIQ_MODE       =0b10001
IRQ_MODE       =0b10010
SUPERVISOR_MODE=0b10011
ABORT_MODE     =0b10111
UNDEF_MODE     =0b11011
SYSTEM_MODE    =0b11111

.text
.global onReset	
onReset:
	mov r0,#SUPERVISOR_MODE
	ldr r1,=_stack_top
	bl .setStack
	mov r0,#UNDEF_MODE
	ldr r1,=_undef_stack_top
	bl .setStack
	mov r0,#IRQ_MODE
	ldr r1,=_irq_stack_top
	bl .setStack
	bl _start 
0:	b 0b				    /* forever */	

/*-------------------------------- the local functions */
/* r0 mode bits 0..4
/* r1 stack top */
.setStack:
	mrs r2,cpsr /* current program status register */
        bic r3,r2,#0x1f        /* clear mode bits 0..4 */
	orr r3,r3,r0                       /* set mode */
	msr cpsr_c,r3                           /* now */
	mov sp,r1
	msr cpsr_c,r2                  /* prevous mode */
	mov pc,lr
	
.align 4
/*--------------------------------- very basic debug */
/* see first.S */
.signal:
	ldr r0,=UART0            /* address of UART0 */
	ldr r1,='1'                 /* char to print */
0:	ldr r2,[r0,#0x18]     /* wait until tx ready */
	ands r2,r2,#(1<<3)               /* tx empty */
	bne 0b
	str r1,[r0]                    /* write char */
1:	b 1b                              /* forever */

.hex:              /* prints r0 hexadecimal to UART0 */
	                            /* see src/hex.S */
	ldr r1,=UART0
	ldr r2,=8                      /* nibble cnt */

0:	mov r0,r0,ROR #28          /* rotate 28 bits */
	and r3,r0,#0xf	    /* mask nibble: 0<=r3<16 */
	cmp r3,#10
	addlt r3,r3,#'0'                  /* 0<=r3<9 */
	addge r3,r3,#('a'-10)           /* 10<=r3<16 */
	                 /* r3<-r3-10+'a'=r1+('a'-10)*/
	                    /* r3 character to print */
1:	ldr r4,[r1,#0x18]             /* UART0 flags */
	ands r4,r4,#(1<<3)                   /* BUSY */
	bne 1b
	str r3,[r1]                    /* print char */
	
	subs r2,r2,#1                 /* next nibble */
	bne 0b
2:	b 2b                         /* loop forever */	

.string:	             /* r0 pointer to string */
	ldr r1,=UART0
0:	ldrb r2,[r0],#1            /* post increment */
	cmp r2,#0	         /* terminating zero */
	moveq pc,lr    /* return if terminating zero */
1:	ldr r3,[r1,#0x18]             /* UART0 flags */
	ands r3,r3,#(1<<3)                   /* BUSY */
	bne 0b	
	str r2,[r1]
	b 0b
UART0=0x10009000                 /* address of UART0 */			

/*-------------------------------------------- stack */
                                /* see config/ram.ld */
                                 /* see Makefile for */
	      /* IRQ_STACK_SIZE_WORD/STACK_SIZE_WORD */
.section .stack
	.space 4*UNDEF_STACK_SIZE_WORD
_undef_stack_top:	
	.space 4*IRQ_STACK_SIZE_WORD
_irq_stack_top:
	.space 4*STACK_SIZE_WORD
_stack_top:
