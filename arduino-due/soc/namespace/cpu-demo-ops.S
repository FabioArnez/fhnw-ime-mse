/*---------------------------
 cpu-demo-ops
 (c) H.Buchmann FHNW 2015
 ----------------------------*/
.text

/* unsigned Demo::op(unsigned int, unsigned int)
   r0                r0            r1

use:
   ../tc/bin/arm-none-linux-gnueabi-nm cpu-demo.o
to figure out the real name   
*/
.global _ZN4Demo2opEjj
_ZN4Demo2opEjj:
	add r0,r0,r1
	mov pc,lr


/* void Demo::swap(unsigned int&, unsigned int&)
                   r0->           r1->
*/
.global _ZN4Demo4swapERjS0_
_ZN4Demo4swapERjS0_:
 	ldr r2,[r0]
	ldr r3,[r1]
	str r2,[r1]
	str r3,[r0]
	mov pc,lr

/* Demo::copy(unsigned int&, unsigned int&) 
*/
/* your work */
