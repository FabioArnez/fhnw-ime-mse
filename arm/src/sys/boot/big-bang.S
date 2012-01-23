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
	ldr r0,=0x9abcdef0 
	bl .hex
	bl .signal

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

UART0=0x10009000                 /* address of UART0 */			

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
