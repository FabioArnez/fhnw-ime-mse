/*------------------------
  bigBang
  (c) H.Buchmann FHNW 2011
  demonstrates .booting
               .outline of an image
  see ram.ld linker script	       
  $Id$
  [1] literature/ARM-Architecture-Reference-Manual.pdf
  TODO: make a demo for .onSWI
        make an informative message for the unimplemented exceptions
	set the different stacks properly
	do the basic exception handling sys/sys.{h,c}
	set the exception stacks IRQStack alread set
------------------------*/
.section .boot  /* see [1] A2.6 */
/* one word per entry
  ldr pc,=address_of_handler
*/
	ldr pc,=.onReset           /* 0x00 A2.6.2 */
	ldr pc,=.onUndef           /* 0x04 */
	ldr pc,=.onSWI             /* 0x08 */
	ldr pc,=.onPrefetch        /* 0x0c */
	ldr pc,=.onData            /* 0x10 */
	ldr pc,=.onReserved        /* 0x14 */
	ldr pc,=.onIRQ             /* 0x18 */
	ldr pc,=.onFIQ             /* 0x1c */

/*------------------------------------------ text */
.text	
.onReset:
	bl .setStack
	bl .setIRQStack
	bl _start 
0:	b 0b				/* forever */	

.onUndef:
	ldr r0,=.onUndefTxt
	bl .string
	b .signal
.onSWI: 
	ldr r0,=.onSWITxt
	bl .string
	b .signal
.onPrefetch:
	ldr r0,=.onPrefetchTxt
	bl .string
	b .signal
.onData:
	ldr r0,=.onDataTxt
	bl .string
	b .signal
.onReserved:
	ldr r0,=.onReservedTxt
	bl .string
	b .signal
.onIRQ:
	ldr r0,=.onIRQTxt
	bl .string
	b .signal
.onFIQ:
	ldr r0,=.onFIQTxt
	bl .string
	b .signal

/*-------------------------------------- some text */ 
.align 4
.onUndefTxt:	.asciz "Undefined instruction\n"
.align 4
.onSWITxt: 	.asciz "Software switch\n"
.align 4
.onPrefetchTxt:	.asciz "Prefetch Abort\n"
.align 4
.onDataTxt:	.asciz "Data Abort\n"
.align 4
.onReservedTxt:	.asciz "Reserved\n"
.align 4
.onIRQTxt:	.asciz "IRQ\n"
.align 4
.onFIQTxt:	.asciz "FIQ\n"

.align 4
/*---------------------------- the local functions */
.setStack:
	ldr sp,=_stack_top
	mov pc,lr
	
.setIRQStack:
	mrs r0,cpsr                 /* mode bits 0..4*/
	bic r1,r0,#0x1f                 /* mode bits */
	orr r1,r1,#0x12                /* 10010 IRQ  */ 
	msr cpsr_c,r1	
	ldr sp,=_irq_stack_top
	msr cpsr_c,r0		     /* prevous mode */
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
	.space 4*IRQ_STACK_SIZE_WORD
_irq_stack_top:
	.space 4*STACK_SIZE_WORD
_stack_top:
