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


extern void thread_create(Thread* th,
                          void (*run)(),
                          void* pool,
			  unsigned size_byte);

extern void thread_yield();


extern void thread_ready(Thread* th);
 /* th *not* running */

extern __attribute__((noreturn)) void thread_run(); /* never returnS */
                                /* called from main as last function */

/* ------------------------------------------------ queues */ 
typedef struct WaitQueue WaitQueue; 

struct WaitQueue  
{
 void (*lock)();
 void (*unlock)();
 volatile Thread* first; /* accessible fore-background */
 volatile Thread* last;
};


extern void thread_wait_init(WaitQueue* q,void (*lock),void (*unlock)());
extern void thread_put(Thread* th);

