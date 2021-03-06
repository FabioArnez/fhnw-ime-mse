/*-------------------------
 pthread.c
 (c) H.Buchmann FHNW 2012
 $Id$
---------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNT (1ul<<25)

static int error(int cod,char* msg)
{
 if (cod<0)
    {
     perror(msg);
     exit(1);
    }
 return cod;
}

typedef struct
{
 pthread_mutex_t guard;
 volatile unsigned val; /* check if really volatile */
} Shared;

Shared theShared; /* try without volatile */

static void* increment(void* data)
{
 unsigned long count=COUNT;
 while(count--)
 {
  pthread_mutex_lock(&theShared.guard);
  ++theShared.val;
  pthread_mutex_unlock(&theShared.guard);
 }
}

static void* decrement(void *data)
{
 Shared* shared=(Shared*)data;
 unsigned long count=COUNT;
 while(count--)
 {
  pthread_mutex_lock(&theShared.guard);
  --theShared.val;
  pthread_mutex_unlock(&theShared.guard);
 }
}


static void result()
{
 printf("theShared->val=%d\n",theShared.val);    
}

static void sequentially()
{
 increment(0);
 decrement(0);
}

static void concurrent()
{
 pthread_t inc;
 pthread_t dec;
 error(pthread_create(&inc, 
		      0, /* no attributes */
		      increment,
		      0),
       "inc"
      );
 error(pthread_create(&dec, 
                0, /* no attributes */
		decrement,
		0),
       "dec"	
      );

 pthread_join(inc,0);
 pthread_join(dec,0); 
}

int main(int argc,char** args)
{
 theShared.val=0; 
 error(pthread_mutex_init(&theShared.guard,0),"pthread_mutex_init");
// sequentially();
 concurrent();
 result();
 return 0;
}
