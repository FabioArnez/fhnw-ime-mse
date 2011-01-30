/*------------------------
  bigBang
  (c) H.Buchmann FHNW 2011
  demonstrates .booting
               .outline of an image
  see ram.ld linker script	       
  $Id$
------------------------*/
.section .boot
	ldr sp,=.stack_top
	bl _start      /* call _start a C routine */ 
	b .reset
	
/*----------------------------------------- reset */
.reset:	ldr r0,=0x1000000c
	orr r1,r1,#(1<<3)
	str r1,[r0]   /* reset */
	
/*----------------------------------------- stack */
.section .stack	
	.space 4*STACK_SIZE_WORD
.stack_top:
