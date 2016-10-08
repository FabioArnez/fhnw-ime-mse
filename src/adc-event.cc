//-----------------------
//adc-event
//(c) H.Buchmann FHNW 2016
//[1] Atmel | SMART  SAM D21J, SAM D21G, SAM D21E, 
//    ARM Cortex-M0+ based Embedded Flash Microcontroller
//    Atmel-42181-SAM-D21_Datasheet.pdf
//-----------------------
IMPLEMENTATION(adc_random,$Id$)
#include "sys/msg.h"
#include "sys/event.h"
#include "sys/soc.h"

#include "adc.h"

class App:sys::SOC
         ,sys::Event
         ,sys::Event::Listener
	 ,ADC::Listener
{
 static App app;
 App();
 void menu();
//----------------------------------- implementation sys::Event::Listener
 void onEvent(sys::Event& ev);
//----------------------------------- implementation sys::ADC::Listener
 void onValue(unsigned); 

 static const sys::SOC::VTable VTable;  //located in FLASH *not* in RAM
 
};

App App::app;

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
   defaultTrap,      //0x00    <---------- index in VTable 0x10 see [1] 11.2.2
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
   ADC::onADC,       //0x17
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


void App::onEvent(sys::Event& ev)
{
 menu();
}

void App::onValue(unsigned v)
{
 sys::msg<<v<<"\n";
}

void App::menu()
{
 signal();
 if (!sys::deb::avail()) return;
 static const char Menu[]="(t)rigger (?|h)elp: ";

 switch(sys::deb::get())
 {
  case 't':
   ADC::trigger();
  break;
  case '?':
  case 'h':
   sys::msg<<Menu;
  break;
 }
}

App::App()
:sys::SOC(VTable)
,sys::Event(*this,"menu")
{
 ADC::start(*this);
 signal(); //start menu 
 sys::Event::loop(); 
}
