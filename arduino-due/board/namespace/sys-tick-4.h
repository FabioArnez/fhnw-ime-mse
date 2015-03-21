#pragma once
//-----------------------------
//sys-tick an event driven driver
//(c) H.Buchmann FHNW 2015
//-----------------------------
INTERFACE(sys_tick,$Id$)
#include "sys/event.h"

class SysTick:sys::Event
              ,sys::Event::Listener
{
 public:
  class Listener
  {
   public:
    virtual void onTick()=0; //pure virtual see Java interface
  };
  static void listenSlow(unsigned time,Listener& li){listen(time,SLOW,li);} 
  static void listenFast(unsigned time,Listener& li){listen(time,FAST,li);}

 private:
  static const unsigned FAST=1<<2;
  static const unsigned SLOW=0<<2;
  static SysTick sysTick; //the instance 
  
  SysTick();              //the instance
  static void onTick();   //the Trap
  void onEvent(sys::Event&);
  static void listen(unsigned time,unsigned clockSourceBit,Listener& li);
  Listener* li=0;
};

