//---------------------
//tc-test
//(c) H.Buchmann FHNW 2016
//---------------------
IMPLEMENTATION(test_tc,$Id$)
#include "sys/reg/tc.h"
#include "sys/msg.h"
#include "sys/reg/pm.h"
#include "sys/deb/deb.h"
#include "sys/reg/gclk.h"
#include "sys/led.h"
#include "tc.h"
#include "sys/soc.h"

class App:sys::SOC                        //for VTable
         ,sys::Event,sys::Event::Listener //for menu
	 ,TC::Listener                    //for tick
{
 static const sys::SOC::VTable  VTable;
 static const TC::Config        Config;
 static const TC::ID ID=TC::TC5;

 static App app;
  
 void onEvent(sys::Event&);
 void onMC0();
 void onMC1();
 void onOverflow();
 App();
};

decltype(App::VTable) App::VTable=                       //located in flash
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
   TC::onTC<TC::TC3>,//0x12  TC3
   TC::onTC<TC::TC4>,//0x13  TC4
   TC::onTC<TC::TC5>,//0x14  TC5
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

const TC::Config App::Config= //located in flash
{
 (1<<7),  //CTRLA;
 0,       //CTRLBCLR;
 0,       //CTRLBSET;
 0,       //CTRLC;
 0,       //EVCTRL;
 0,       //INTENCLR;
 (1<<4),  //INTENSET;
 0,            //COUNT16;
 {15625,0}     //CC16[2];
};

App App::app;

void App::onEvent(sys::Event&)
{
 signal();
 if (!sys::deb::avail()) return;
 switch(sys::deb::get())
 {
  case 'h':
  case '?':
   sys::msg<<"(h|?) help (r)egs: ";
  break;
  case 'r':
   sys::msg<<"regs\n";
   TC::regs(ID);
  break;
 } 
}

void App::onMC0()
{
 sys::LED::tgl(sys::LED::L);
}

void App::onMC1()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

void App::onOverflow()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

App::App()
:sys::SOC(VTable)
,sys::Event(*this,"menu")
{
 signal(); //for polling keyboard
 sys::msg<<"TC-Demo\n";

 sys::reg::GCLK.src2gen(sys::reg::GCLK::OSC8M,sys::reg::GCLK::G8,(1<<0));
 sys::reg::GCLK.gendiv(sys::reg::GCLK::G8,64);    

 sys::msg<<"GCLK done\n"; 

 TC::start(ID,Config,sys::reg::GCLK::G8,*this);
 sys::Event::loop();
}
