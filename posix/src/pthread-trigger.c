/*------------------------
 pthread-trigger
 (c) H.Buchmann FHNW 2012
 $Id$
--------------------------*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t initialize;

#define SHOOTN 10

void* shoot(void* data)
{
 unsigned id=*(unsigned*)data; /* copy */
 printf("id= %d\n",id);
 sem_post(&initialize);
 while(1)
 {
 }
}

static void init()
{
 sem_init(&initialize,0,0);
 for(unsigned s=0;s<SHOOTN;++s)
 {
  pthread_t th;
  pthread_create(&th,0,shoot,&s);
  sem_wait(&initialize);                 /* wait until thread th initialized */
 }   
}

static void menu()
{
 while(1)
 {
  printf("Menu\n"
         "             0:exit\n"
	 "             1:trigger\n"
	 "your choice: ");
  char answer;
  int size=fread(&answer,sizeof(answer),1,stdin);
  switch(answer)
  {
   case '0':
   return;
   
   case '1':
    printf("trigger\n");
   break;
  }
 }
}

int main(int argc,char** args)
{
 init();
 menu(); 
}  
