/*-----------------------
 coroutine0 
 (c) H.Buchmann FHNW 2012
 $Id$
-------------------------*/ 
#include "sys/coroutine0.h"

.text
/* void coroutine_transfer(Coroutine* from,Coroutine* to) 
 r0 -> from
 r1 -> to
*/
coroutine_transfer:
	push {r0-r12,lr}
	str sp,[r0]
	ldr sp,[r1]
	add r2,sp,#(14*4)
	str r2,[r1]
	pop {r0-r12,pc}
	
