//--------------------------
//interrupt-demo-2
// polling the status register calling onTick()
//(c) H.Buchmann FHNW 2016
//[1] ARMv6-M Architecture Reference Manual. 
//    This documentation defines the ARMv6-M Microcontroller architecture
//    DDI0419C_arm_architecture_v6m_reference_manual.pdf
//--------------------------
//using SYSTICK as interrupt source

#include "sys/msg.h"
#include "sys/deb/deb.h"

class App
{
 static volatile struct SYST{  //see [1] B3.3.2   
                       unsigned CSR;
                       unsigned RVR;
                       unsigned CVR;
                       unsigned CALIB;
		       void regs() const volatile;
                      } SYST;

 static App app;
 static void onTick();
 App();
};


App App::app;

void App::onTick()
{
 sys::msg<<"x";
}

App::App()
{
 SYST.RVR=(1<<24)-1;
 SYST.CSR=1; //start
 while(true)
 {
  if (SYST.CSR&(1<<16)) onTick();
               //COUNTFLAG
 }
}
