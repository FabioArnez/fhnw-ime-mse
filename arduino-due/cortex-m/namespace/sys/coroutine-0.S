/*------------------------
 coroutine-0
 (c) H.Buchmann FHNW 2015
 -------------------------*/
	.syntax unified
	.cpu cortex-m3

/*------------------------ stack
 r0
 r1
 ..
 r12
 lr 
   <--sp
*/

	.global _ZN3sys10Coroutine08transferEPPNS0_6StatusES2_
/* void Coroutine0::transfer(Status** from,Status* to)
                                      r0    r1
*/
_ZN3sys10Coroutine08transferEPPNS0_6StatusES2_:
	push {r0-r12,lr}
	str sp,[r0]
	mov sp,r1
	pop {r0-r12,pc}

/*---------------------------------------
   static Status* Coroutine0::init(Coroutine0* c,
                       unsigned*   top, //of stack
		       void (*call)(Coroutine0*)) 

*/
.global _ZN3sys10Coroutine04initEPS0_PjPFvS1_E
_ZN3sys10Coroutine04initEPS0_PjPFvS1_E:
	mov pc,lr
