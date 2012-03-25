/*---------------------------
 coroutine
 (c) H.Buchmann FHNW 2012
 $Id$
 TODO
 ../src/sys/coroutine.c:27:12: warning: assignment from incompatible pointer type [enabled by default]
-----------------------------*/
#include "sys/coroutine.h"
#include "stdio.h"

typedef struct
{
 unsigned        r[13];   /* r0 - r12 */
 struct Status*  sp;     /* stack pointer */
 void (*lr)();           /* link register */
} Status;  

void coroutine_init(void (*code)(),
                    void* pool,
	            unsigned size_byte,
		    Coroutine* co)
{
 Status* status=(Status*)((unsigned char*)pool+(size_byte-sizeof(Status)));
 for(unsigned i=0;i<13;++i) status->r[i]=0;
 status->sp=status;
 status->lr=code;
 co->status=status;
}

void coroutine_show(Coroutine* co)
{
 Status* s=co->status;
 printf("status = %p\n"
        "r0=%x   r4=%x   r8 =%x   r12=%x\n"
	"r1=%x   r5=%x   r9 =%x\n"   
	"r2=%x   r6=%x   r10=%x\n"
	"r3=%x   r7=%x   r11=%x\n"
	"sp=%x\n"
	"lr=%x\n",
	s,
	s->r[0],s->r[1],s->r[2],s->r[3],
	s->r[4],s->r[5],s->r[6],s->r[7],
	s->r[8],s->r[9],s->r[10],s->r[11],
	s->r[12],
	s->sp,s->lr);
}

/* void coroutine_transfer(Coroutine* from¨Coroutine* to) 
  see coroutine0.S */
