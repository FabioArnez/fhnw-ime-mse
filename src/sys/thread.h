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

extern __attribute__((noreturn)) void thread_run(); /* never returnS */
/* ------------------------------------------------ queues */ 
typedef struct ThreadQueue ThreadQueue;
struct ThreadQueue
{
 Thread* first;
 Thread* last;
};

extern unsigned thread_queue_empty(ThreadQueue* q);
extern void     thread_queue_init(ThreadQueue* q);
extern void     thread_queue_put(ThreadQueue* q,Thread* th);
extern Thread*  thread_queue_get(ThreadQueue* q);
