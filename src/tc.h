#pragma once
//-------------------------
//tc timer/counter driver event driven
//(c) H.Buchmann FHNW 2016
//-------------------------
INTERFACE(tc,$Id$)
#include "sys/event.h"
#include "sys/reg/tc.h"
#include "sys/reg/gclk.h"
#include "sys/msg.h"

class TC:sys::Event::Listener 
{
 public:
  enum ID {TC3,TC4,TC5}; //,TC6,TC7}; not yet working
  struct Listener
  {
   virtual void onMC0()=0;
   virtual void onMC1()=0;
   virtual void onOverflow()=0;
  };
  
  struct Config //subset of sys::reg::TC registers
  {
   unsigned short CTRLA;
//   unsigned short READREQ;
   unsigned char  CTRLBCLR;
   unsigned char  CTRLBSET;
   unsigned char  CTRLC;
   unsigned short EVCTRL;
   unsigned char  INTENCLR;
   unsigned char  INTENSET;
   unsigned short COUNT16;
   unsigned short CC16[2];
  }; 
  
  template<TC::ID ID>
  static void onTC();         //the interrupt handler
 
  static void start(ID id,
               const Config& config,
               sys::reg::GCLK::GEN gclk,
               Listener& li);
  static void regs(ID id){Regs[id]->regs();}
  
 private:
  TC(ID id);
  TC(TC&&); //why we have to declare the copy constructor
  
  void onEvent(sys::Event&);
  sys::Event tick;
  Listener* li=0;
  volatile unsigned intflag=0; //from the interrupt
  unsigned intset=0;          
  static volatile sys::reg::TC*const Regs[];
  static TC tc[];
};

template<TC::ID ID>
void TC::onTC()         //the interrupt handler
{
 unsigned intflag=Regs[ID]->INTFLAG;
 tc[ID].intflag=intflag;
 Regs[ID]->INTFLAG|=intflag;
 tc[ID].tick.signal();
}
