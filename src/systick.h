#pragma once
//------------------------
//systick
//(c) H.Buchmann FHNW 2016
///[1] ARMv6-M Architecture Reference Manual. 
//    This documentation defines the ARMv6-M Microcontroller architecture
//    DDI0419C_arm_architecture_v6m_reference_manual.pdf
//------------------------
INTERFACE(systick,$Id$)
#include "sys/event.h"
class SysTick:sys::Event
             ,sys::Event::Listener
{
 public:
  struct Listener      //nested class/struct
  {
   virtual void onTick()=0; //see Java
  };
  
  void start(unsigned delta,Listener& li);
  static SysTick& get(); //factory: reference to the instance 
  static void sysTick(); //the trap call back
  
 private:
  SysTick();               //singelton
  static SysTick sysTick_; //used in sysTick because static 
  static volatile struct { //see [1] B3.3.2   
                          unsigned CSR;
                          unsigned RVR;
                          unsigned CVR;
                          unsigned CALIB;
		          void regs() const volatile;
                         } SYST;
  Listener* li=0;
  void onEvent(sys::Event&); //implementation sys::Event::Listener
};
