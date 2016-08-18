//--------------------
//big-bang
//(c) H.Buchmann FHWN 2016
//-------------------
.thumb
.cpu cortex-m0

.section .boot, "x"                               /* see layout.ld */
/* vector table */
	.word STACK_TOP                            /* inital stack ptr */
	.word _ZN3sys5Board7bigBangEv           /* bit 0 *must* be set */

