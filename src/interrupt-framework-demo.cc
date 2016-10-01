//-------------------------
//interrupt-framework-demo
//(c) H.Buchmann FHNW 2016
//[1] ARMv6-M Architecture Reference Manual. 
//    This documentation defines the ARMv6-M Microcontroller architecture
//    DDI0419C_arm_architecture_v6m_reference_manual.pdf
//[2] Atmel | SMART  SAM D21J, SAM D21G, SAM D21E, 
//    ARM Cortex-M0+ based Embedded Flash Microcontroller
//    Atmel-42181-SAM-D21_Datasheet.pdf

//-------------------------
IMPLEMENTATION(interrupt_framework_demo,$Id$)
#include "sys/msg.h"
#include "sys/soc.h"
#include "sys/pin.h"
#include "sys/reg/eic.h"

class App:sys::SOC
{ 
 static App app;
 static const sys::SOC::VTable VTable;  //located in FLASH *not* in RAM
 sys::Pin::Output out;
 sys::Pin::Input  in;
 App();
 void initEIC();   //TODO make EIC as a class the code in initEIC will be moved into the
                   //     the constructor
 static void eic();
 void menu();
};
 
decltype(App::VTable) App::VTable=
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
  defaultTrap,       //Entry   sysTick;
  {                  //Entry   external[N];
   defaultTrap,      //0x00    <---------- index in VTable 0x10 see [2] 11.2.2
   defaultTrap,      //0x01
   defaultTrap,      //0x02
   defaultTrap,      //0x03
   eic,              //0x04
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

void App::eic()  //static 
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
 sys::reg::EIC.INTFLAG|=sys::reg::EIC.INTFLAG;  //clear flag
 app.out(false);
}

void App::initEIC()
{
 sys::reg::PORT::mux(sys::reg::PORT::PA06,sys::reg::PORT::F_A); //see [2] Section 7
 sys::reg::EIC.init();  //see [2] 21.6.1
 sys::reg::EIC.enable(sys::reg::EIC::P06);
 sys::reg::EIC.sense(sys::reg::EIC::P06,sys::reg::EIC::HIGH);
// sys::reg::EIC.filter(sys::reg::EIC::P06,true); //dont works with filter why
                                                  //[2] 21.6.1
 sys::SOC::arm(sys::SOC::EIC);
}

void App::menu()
{
 if (sys::deb::avail()) return;
 switch(sys::deb::get())
 {
  case 'h':
  case '?':
   sys::msg<<"h|?:help\n"
             "s:set out\n";
  break;
  case 's':
   out(true);
  break;
 }
}

App App::app;
App::App()
:sys::SOC(VTable)
,out(sys::Pin::PA19,false)
,in (sys::Pin::PA06)
{
 initEIC();
 sys::msg<<"h|? for help\n";
 while(true)
 {
   menu();
 }   
}
