/*---------------------------
 deblow0
 (c) H.Buchmann FHNW 2016
 ----------------------------*/
.thumb
.cpu cortex-m0
.text
.thumb_func              	/* very important for thumb */
.global _ZN3sys3deb4waitEj

/* wait(unsigned cnt) */
_ZN3sys3deb4waitEj:
0:	sub r0,#1
	bne 0b
	mov pc,lr

.global _ZN3sys3deb5valueEj
/* value(unsigned val) */ 
/* val in r0 */
_ZN3sys3deb5valueEj:
	0:b 0b   
