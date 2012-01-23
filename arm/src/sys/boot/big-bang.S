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
/*------------------------------------------ text */
.text	
.onReset:
	bl .signal

/*--------------------------------- very basic debug */
/* see first.S */
.signal:
	ldr r0,=0x10009000       /* address of UART0 */
	ldr r1,='1'                 /* char to print */
0:	ldr r2,[r0,#0x18]     /* wait until tx ready */
	ands r2,r2,#(1<<7)               /* tx empty */
	beq 0b
	str r1,[r0]                    /* write char */
1:	b 1b                              /* forever */

	

#if 0
	ldr pc,=.onReset           /* 0x00 A2.6.2 */
	ldr pc,  onUndef           /* 0x04 A2.6.3 */
	ldr pc,=.onSWI             /* 0x08 A2.6.4 */
	ldr pc,=.onPrefetchAbort   /* 0x0c A2.6.5 */
	ldr pc,=.onData            /* 0x10 A2.6.6 */
	ldr pc,=.onReserved        /* 0x14  should never be called */
	ldr pc,= onIRQ             /* 0x18 A2.6.8 */
	ldr pc,=.onFIQ             /* 0x1c A2.6.9 */

.global onUndef
onUndef: .word .onReserved	

.global onIRQ
onIRQ: 	.word .onReserved

/*------------------------------------------ text */
.text	
.onReset:
	bl .setStack
	bl .setIRQStack

	bl _start      /* call _start a C routine */ 
	b .do_reset

.setStack:
	ldr sp,=.stack_top
	mov pc,lr
	
.setIRQStack:
	mrs r0,cpsr
	ldr r1,=0x1f        /* Mode mask [1]A2.5 */
	ldr r2,=0x12                 /* IRQ Mode */
	bic r0,r1
        orr r0,r0,r2

	msr cpsr_c,r0
	ldr sp,=.irq_stack_top
	mov pc,lr

.onIRQ:
	mov r0,sp
	bl hex
	b deb_signal1
	
/* the unimplemented traps */

.onSWI:
.onPrefetchAbort:
.onData:
.onReserved:
.onFIQ:
	b deb_signal0
	
/*----------------------------------------- do_reset */
.do_reset:	
	ldr r0,=0x1000000c
	orr r1,r1,#(1<<3)
	str r1,[r0]   /* reset */


/*-------------------------------------------- stack */
.section .stack	
	.space 4*IRQ_STACK_SIZE_WORD
.irq_stack_top:
	.space 4*STACK_SIZE_WORD
.stack_top:
#endif
