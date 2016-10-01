//--------------------------
//interrupt-nvic-demo-2
// polling
//    Arduino   SAMD Function 
//  in Pin8      PA06 A       EXTINT6
// out Pin12     PA19
//(c) H.Buchmann FHNW 2016
//[1] ARMv6-M Architecture Reference Manual. 
//    This documentation defines the ARMv6-M Microcontroller architecture
//    DDI0419C_arm_architecture_v6m_reference_manual.pdf
//[2] Atmel | SMART  SAM D21J, SAM D21G, SAM D21E, 
//    ARM Cortex-M0+ based Embedded Flash Microcontroller
//    Atmel-42181-SAM-D21_Datasheet.pdf
//--------------------------

#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/pin.h"
#include "sys/reg/eic.h"

class App
{
 static App app;
 sys::Pin::Output out;
 sys::Pin::Input  in;
 App();
 void onPin(); //the future call back
 void initEIC();   //TODO make EIC as a class the code in initEIC will be moved into the
                   //     the constructor
 void menu();
 void pin();
};

App App::app;

void App::initEIC()
{
 sys::reg::PORT::mux(sys::reg::PORT::PA06,sys::reg::PORT::F_A); //see [2] Section 7
 sys::reg::EIC.init();  //see [2] 21.6.1
 sys::reg::EIC.enable(sys::reg::EIC::P06);
 sys::reg::EIC.sense(sys::reg::EIC::P06,sys::reg::EIC::HIGH);
// sys::reg::EIC.filter(sys::reg::EIC::P06,true); //dont works with filter why
                                                  //[2] 21.6.1
  
}

void App::onPin()
{
 sys::msg<<"HIGH\n";
 out.val(false);
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
   out.val(true);
  break;
 }
}

void App::pin()
{
 if (sys::reg::EIC.INTFLAG&(1<<sys::reg::EIC.P06)) onPin();
}

App::App()
:out(sys::Pin::PA19,false)
,in (sys::Pin::PA06)
{
 initEIC();
 sys::msg<<"h|? for help\n";
 while(true)
 {
   menu();
   pin();
 }   
}
