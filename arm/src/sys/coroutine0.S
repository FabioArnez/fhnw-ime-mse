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
	mov pc,lr
