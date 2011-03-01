/*------------------------
  bigBang
  (c) H.Buchmann FHNW 2011
  demonstrates .booting
               .outline of an image
  see ram.ld linker script	       
  $Id$
------------------------*/
.section .boot
	ldr pc,=.onReset
	ldr pc,=.onUndef
	
/*------------------------------------------ text */
.text	
.onReset:
	ldr sp,=.stack_top
	bl _start      /* call _start a C routine */ 
	b .do_reset

.onUndef:
	b deb_signal0	
/*----------------------------------------- do_reset */
.do_reset:	
	ldr r0,=0x1000000c
	orr r1,r1,#(1<<3)
	str r1,[r0]   /* reset */
	
/*----------------------------------------- stack */
.section .stack	
	.space 4*STACK_SIZE_WORD
.stack_top:
