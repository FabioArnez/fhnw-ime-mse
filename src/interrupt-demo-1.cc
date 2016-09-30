//--------------------------
//interrupt-demo-1
// showing the principle
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
 App();
};


App App::app;

App::App()
{
 SYST.RVR=(1<<24)-1;
 SYST.CSR=1;
 while(true)
 {
  sys::msg<<SYST.CVR<<"\n";
 }
}
