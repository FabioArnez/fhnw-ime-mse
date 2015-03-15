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
  static void listen(unsigned time,Listener& li);

 private:
  static SysTick sysTick; //the instance 
  
  SysTick();              //the instance
  static void onTick();   //the Trap
  void onEvent(sys::Event&);
  Listener* li=0;
};

