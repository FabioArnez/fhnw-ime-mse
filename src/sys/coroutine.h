#pragma once
/*---------------------------
 coroutine
 (c) H.Buchmann FHNW 2012
 $Id$
-----------------------------*/
typedef struct Status Status;
typedef union Coroutine Coroutine;

union Coroutine
{
 unsigned* pool;
 Status*   status;
};

extern void coroutine_init(void (*code)(),
                           void* pool,
			   unsigned size_byte,
                           Coroutine* co);
			   
extern void coroutine_transfer(Coroutine* from,Coroutine* to);

extern void coroutine_show(Coroutine* co);
