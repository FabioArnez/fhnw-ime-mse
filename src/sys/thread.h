#pragma once
/*--------------------------
 thread
 (c) H.Buchmann FHNW 2012
 $Id$
----------------------------*/
#include "sys/coroutine.h"
typedef struct Thread Thread;

struct Thread
{
 Thread*   next;
 Coroutine cor;
};

extern void thread_init(Thread* th,
                        void (*run)(),
                        void* pool,
			unsigned size_byte);

extern void thread_yield();
 
