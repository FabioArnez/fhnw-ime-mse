//--------------------------
//interrupt-nvic-demo-1
// external interrupt pin
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

class App
{
 static App app;
 sys::Pin::Output out;
 sys::Pin::Input  in;
 App();
};

App App::app;


App::App()
:out(sys::Pin::PA19,false)
,in (sys::Pin::PA06)
{
 while(true)
 {
  sys::msg<<"External Interrupt\n"
            " s:set out\n"
	    " c:clr out\n"
	    " i:in\n";
  switch(sys::deb::get())
  {
   case 'c':
    out.val(false);
   break;
   case 's':
    out.val(true);
   break;
   case 'i':
    sys::msg<<in.val()<<"\n";
   break;
   
  }   
 }
}
