/*--------------------------
 thread
 (c) H.Buchmann FHNW 2012
 $Id$
----------------------------*/
#include "sys/thread.h"
#include "stdio.h"

typedef struct Queue Queue;

struct Queue
{
 Thread* first;
 Thread* last;
};

static void queue_put(Queue* q,Thread* th)
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

static Thread* queue_get(Queue* q)
{
 if (q->first==0) return 0;
 Thread* th=q->first;
 q->first=q->first->next;
 if (q->first==0) q->last=0;
 return th; 
}

void queue_show(Queue* q)
{
 if (q->first==0) 
    {
     printf("empty\n");
     return;
    }
 Thread* th=q->first;
 while(th)
 {
  printf("%p ",&(th->cor));
  th=th->next;
 } 
}

static Thread  main_={next:0};
static Queue   ready={0,0};
static Thread* run=&main_;

void thread_init(Thread* th,
                 void (*run)(),
                 void* pool,
		 unsigned size_byte)
{
 th->next=0;
 coroutine_init(run,pool,size_byte,&(th->cor));
 queue_put(&ready,th);
}		 

void thread_yield()
{
  
 Thread* r=run;
 queue_put(&ready,r);
 run=queue_get(&ready);
 coroutine_transfer(&(r->cor),&(run->cor));   
}

