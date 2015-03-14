/*------------------------
 coroutine-0
 (c) H.Buchmann FHNW 2015
 -------------------------*/
	.syntax unified
	.cpu cortex-m3
/*------------------------ stack
 from         to  before
 ---------------
 r0           r0 <--sp
 r1           r1
 ..           ..
 r12          r12
 lr           lr
     <--sp
     
      from
 r0  <--sp    r0
 r1           r1
 ..           ..
 r12          r12
 lr           lr
                 <--sp

*/
.global _ZN2co9Coroutine8transferEPPNS0_6StatusES2_
_ZN2co9Coroutine8transferEPPNS0_6StatusES2_:
        push {r0-r12,lr}
	str sp,[r0]
	mov sp,r1
	pop {r0-r12,pc}
