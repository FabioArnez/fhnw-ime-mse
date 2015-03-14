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
.global _Z11co_transferPP9co_StatusS0_
/* void co_transfer(co_Status** from,co_Status* to) */
_Z11co_transferPP9co_StatusS0_:
        push {r0-r12,lr}
	str sp,[r0]
	mov sp,r1
	pop {r0-r12,pc}
#if 0
	pop {r0-r12,lr}
	mov r0,sp
	bl _ZN3sys3deb3hexEj
1:	b 1b
#endif
	
//	mov pc,lr
