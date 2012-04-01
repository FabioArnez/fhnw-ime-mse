/*--------------------------
 thread
 (c) H.Buchmann FHNW 2012
 $Id$
----------------------------*/
#include "sys/thread.h"
#include "stdio.h"

unsigned thread_queue_empty(ThreadQueue* q)
{
 return q->first==0;
}

void thread_queue_init(ThreadQueue* q)
{
 q->first=0;
 q->last=0;
}

void thread_queue_put(ThreadQueue* q,Thread* th)
{
 th->next=0;
 if (q->last==0)
    {
     q->first=th;
    }
    else
    {
     q->last->next=th;
    }
 q->last=th; 
}

Thread* thread_queue_get(ThreadQueue* q)
{
 if (q->first==0) return 0;
 /* q->first != 0 */
 Thread* th=q->first;


 q->first=th->next;
 if (q->first==0) q->last=0;


 return th; 
}

static Thread      main_={next:0};
static ThreadQueue ready={0,0};
static Thread*     run=&main_;

void thread_create(Thread* th,
                   void (*run)(),
                   void* pool,
		   unsigned size_byte)
{
 th->next=0;
 coroutine_init(run,pool,size_byte,&(th->cor));
 thread_queue_put(&ready,th);
}		 

void thread_yield()
{
  
 Thread* r=run;
 thread_queue_put(&ready,r);
 run=thread_queue_get(&ready);
 coroutine_transfer(&(r->cor),&(run->cor));   
}
__attribute__((noreturn)) void thread_run()
{
 while(1) thread_yield();
}

