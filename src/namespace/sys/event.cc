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
 
 void Event::show() const
 {
  deb::hex((void*)this);deb::out(" ");
  deb::out(id);
  deb::newln();
 }
 
 void Event::Queue::loop()
 {
  while(true) //at least two events in queue
  {
   curr=front;
   Event* ev=front;
   front=ev->next;
   ev->next=0;
   ev->li.onEvent(*ev);
  } 
 }
 
 void Event::debug()
 {
  deb::disableInterrupts();
  Event* ev=queue.front;
  deb::out("-------------------Event\n");
  queue.curr->show();
  deb::out("------------------------\n");
  while(ev)
  {
   ev->show();
   ev=ev->next;
  }
  deb::signal1();
 }
 
 void Event::signal()
 {
  if (next)
     {
      deb::disableInterrupts();
      deb::out("Event ");
      deb::hex((void*)this);
      deb::out(" '");
      deb::out(id);
      deb::out("' already in queue\n");
      deb::halt();
     }
  __atomic_exchange_n(&queue.tail,this,__ATOMIC_RELAXED)->next=this;
 }
 
}
