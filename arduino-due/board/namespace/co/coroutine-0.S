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
    _ZN3sys3deb3hexEj
*/
.global _ZN2co9Coroutine8transferEPPNS0_6StatusES2_
_ZN2co9Coroutine8transferEPPNS0_6StatusES2_:
        push {r0-r12,lr}
	str sp,[r0]
	mov sp,r1
	pop {r0-r12,pc}
