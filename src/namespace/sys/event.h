#pragma once
//------------------------
//event
//(c) H.Buchmann FHNW 2014
//------------------------
INTERFACE(sys_event,$Id$)
#include "sys/deb/deb.h"
namespace sys
{
 class Event
 {
  public:
   struct Listener
   {
    virtual void onEvent(Event&)=0;
   };
   
   
   constexpr Event(Listener*const li,const char id[])
   :id(id),li(*li)
   {}//{deb::hex("event=",(void*)this);}
   
   constexpr Event(Listener& li,const char id[])
   :Event(&li,id)
   {}//{deb::hex("event=",(void*)this);}

   
   void signal();  //called in trap 
   
   
   [[noreturn]] static void loop();//__attribute__((noreturn)); 
   [[noreturn]] static void debug();
    
   bool inQueue(){return next!=0;}
   Event(const Event&)=delete;   //no copy
   
  private:
   void show()const;
   const char*const id;
   Listener& li;
   
   volatile Event* next=0;
   struct Nil;
   struct Queue;
   static Queue queue;
 };
 
 struct Event::Nil:Listener,Event
 {
  void onEvent(Event&){signal();}
  Nil():Event(this,"Nil"){}
 };

 struct Event::Queue
 {
  Nil    nil0;
  Nil    nil1;
           Event* front;
	   Event* curr=0;
  volatile Event* tail;
  Queue():front(&nil0),tail(&nil1){nil0.next=&nil1;} //never empty 
  [[noreturn]] void loop();// __attribute__((noreturn)); 
 };
 
 inline void Event::loop()
 {
  queue.loop();
 }
}//namespace sys
