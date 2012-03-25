#pragma once
/*---------------------------
 coroutine
 (c) H.Buchmann FHNW 2012
 $Id$
-----------------------------*/
struct Status;

typedef union
{
 unsigned*      pool;
 struct Status* status;
} Coroutine;

extern void coroutine_init(void (*code)(),
                           void* pool,
			   unsigned size_byte,
                           Coroutine* co);
			   
extern void coroutine_transfer(Coroutine* from,Coroutine* to);

extern void coroutine_show(Coroutine* co);
