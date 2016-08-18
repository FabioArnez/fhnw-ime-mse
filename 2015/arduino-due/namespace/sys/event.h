#pragma once
//------------------------
//event
//(c) H.Buchmann FHNW 2014
//------------------------
INTERFACE(sys_event,$Id$)
namespace sys
{
 class Event
 {
  public:
   struct Listener
   {
    virtual void onEvent(Event&)=0;
   };

   Event(Listener*const li)
   :li(*li)
   {}

   Event(Listener& li)
   :Event(&li)
   {}
   
   void signal();  //called in trap 
   static void loop()__attribute__((noreturn)); 

  private:
   Event(const Event&); //no copy
   Listener& li;
   volatile Event* next=0;
   struct Nil;
   struct Queue;
   static Queue queue;
 };
 
 struct Event::Nil:Listener,Event
 {
  void onEvent(Event&){signal();}
  Nil():Event(this){}
 };

 struct Event::Queue
 {
  Nil    nil0;
  Nil    nil1;
           Event* front;
  volatile Event* tail;
  Queue():front(&nil0),tail(&nil1){nil0.next=&nil1;} //never empty 
  void loop() __attribute__((noreturn)); 
 };
 
 inline void Event::loop()
 {
  queue.loop();
 }
}//namespace sys
