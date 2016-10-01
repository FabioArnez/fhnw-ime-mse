//-------------------------
//event-framework-demo
//(c) H.Buchmann FHNW 2016
//-------------------------
IMPLEMENTATION(event_demo,$Id$)
#include "sys/msg.h"
#include "sys/event.h"
#include "sys/deb/deb.h"
#include "systick.h"
#include "sys/soc.h"
/*----------------------------------- objectives
 all in once
  foreground-background
  driver
*/

class App:sys::SOC
         ,sys::Event
         ,sys::Event::Listener
	 ,SysTick::Listener
{
 static App app;
 static const sys::SOC::VTable VTable;  //located in FLASH *not* in RAM

//----------------------- implementation Event::Listener
 void onEvent(sys::Event&);

//----------------------- implementation SysTick::Listener
 void onTick();
 App();
};

App App::app;
const sys::SOC::VTable App::VTable= //interrupt-framework
{
  StackTop,                                              //unsigned* sp;
  defaultTrap,       //Entry   reset;
  defaultTrap,       //Entry   nmi;
  &hardFault,        //Entry   hardFault;
  {                  //Entry   reserved0[7];
   defaultTrap,
   defaultTrap,
   defaultTrap,
   defaultTrap,
   defaultTrap,
   defaultTrap,
   defaultTrap
  },        

  defaultTrap,       //Entry	svCall;
  {                  //Entry	reserved1[2];
   defaultTrap,
   defaultTrap
  },                 
  defaultTrap,       //Entry   pendSV;
  SysTick::sysTick,  //Entry   sysTick;
  {                  //Entry   external[N];
   defaultTrap,      //0x00    <---------- index in VTable 0x10 see [2] 11.2.2
   defaultTrap,      //0x01
   defaultTrap,      //0x02
   defaultTrap,      //0x03
   defaultTrap,      //0x04
   defaultTrap,      //0x05
   defaultTrap,      //0x06
   defaultTrap,      //0x07
   defaultTrap,      //0x08
   defaultTrap,      //0x09
   defaultTrap,      //0x0a
   defaultTrap,      //0x0b
   defaultTrap,      //0x0c
   defaultTrap,      //0x0d
   defaultTrap,      //0x0e
   defaultTrap,      //0x0f
   defaultTrap,      //0x10
   defaultTrap,      //0x11
   defaultTrap,      //0x12
   defaultTrap,      //0x13
   defaultTrap,      //0x14
   defaultTrap,      //0x15
   defaultTrap,      //0x16
   defaultTrap,      //0x17
   defaultTrap,      //0x18
   defaultTrap,      //0x19
   defaultTrap,      //0x1a
   defaultTrap,      //0x1b
   defaultTrap,      //0x1c
   defaultTrap,      //0x1d
   defaultTrap,      //0x1e
   defaultTrap,      //0x1f
  }
};

void App::onEvent(sys::Event&)
{
 signal();
 if (!sys::deb::avail()) return;
 sys::msg<<"you pressed '"<<sys::deb::get()<<"'\n";
}

void App::onTick()
{
 sys::msg<<'x';
}

App::App()
:sys::SOC(VTable)
,sys::Event(*this,"App")
{
 sys::msg<<"\n" __FILE__ "\n";
 signal();
 SysTick::get().start((1<<24)-1,*this);
 sys::Event::loop();  //must be last call
}
