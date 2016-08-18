//------------------
//event
//(c) H.Buchmann FHNW 2014
//------------------
IMPLEMENTATION(sys_event,$Id$)
#include "sys/event.h"
#include "sys/msg.h"
#include "sys/deb/deb.h"

namespace sys
{
 Event::Queue Event::queue;
 
 void Event::Queue::loop()
 {
  while(true) //at least two events in queue
  {
   Event* ev=front;
   front=ev->next;
   ev->next=0;
   ev->li.onEvent(*ev);
  } 
 }
 
 void Event::signal()
 {
  if (next)
     {
      deb::hex("Event already in queue",(void*)this);
      deb::halt();
     }
// queue.tail->next=this;
// queue.tail=this;
  __atomic_exchange_n(&queue.tail,this,__ATOMIC_RELAXED)->next=this;
 }
 
}
