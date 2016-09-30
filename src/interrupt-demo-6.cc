//--------------------------
//interrupt-demo-6
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
//using SYSTICK as interrupt source

#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/reg/eic.h"
#include "sys/reg/port.h"
#include "sys/pin.h"
#include "sys/reg/nvic.h"
#include "sys/soc.h"

class App
{
 typedef void (*Trap)(); //the call back
 struct VTable  //see [1] B1.5.2/3
        {
	 unsigned SP_main; 
	 Trap Reset;  
	 Trap NMI;
	 Trap HardFault;
	 Trap Reserved0[7];
	 Trap SVCall;
	 Trap Reserved[2];
	 Trap PendSV;
	 Trap SysTick;
	 Trap External[0];
	} ;

 static const VTable VectorTable;
 static VTable* VTOR;
 	      
 static volatile struct SYST{  //see [1] B3.3.2   
                       unsigned CSR;
                       unsigned RVR;
                       unsigned CVR;
                       unsigned CALIB;
		       void regs() const volatile;
                      } SYST;

 static volatile sys::reg::NVIC<27>  NVIC;
 static App app;
//the callbacks
//TODO try to myke them as templates 
 static void reset();
 static void nmi();
 static void hardFault();
 static void reserved();
 static void svCall();
 static void pendSV();
 static void onTick();
 static void CPSIE();
 sys::Pin::Output out;
 sys::Pin::Input  in;
 App();
};

void App::reset()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

void App::nmi()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

void App::hardFault()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

void App::reserved()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

void App::svCall()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

void App::pendSV()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

void App::onTick()
{
 sys::msg<<"x";
}

void App::CPSIE() //inline assembler
{
  asm volatile
  (
   "cpsie i\n\t"
   :
   :
  );
}



//check that VectorTable is in flash
alignas(256) const App::VTable App::VectorTable=
{
0,
reset,
nmi,
hardFault,
{reserved,reserved,reserved,reserved,reserved,reserved,reserved},
svCall,
{reserved,reserved},
pendSV,
onTick
};

App App::app;


App::App()
:out(sys::Pin::PA19,false)
,in (sys::Pin::PA06)
{
 sys::reg::PORT::mux(sys::reg::PORT::PA06,sys::reg::PORT::F_A);
 VTOR=&VectorTable;
 sys::msg<<"VTOR="<<(void*)VTOR<<"\n"; //check alignement
 sys::SOC::clkOn(sys::SOC::EIC);
 sys::reg::EIC.init();
 sys::reg::EIC.enable(sys::reg::EIC::P06);
 sys::reg::EIC.sense(sys::reg::EIC::P06,sys::reg::EIC::HIGH);
// sys::reg::EIC.filter(sys::reg::EIC::P06,true);
 sys::reg::EIC.enable(sys::reg::EIC::P06);
 

 CPSIE();
 NVIC.arm(4);
 SYST.RVR=(1<<24)-1;
 SYST.CSR=(1<<0) | //start
//          (1<<1) |  //enable interrupt
              0;
 while(true)
 {
  sys::msg<<"External Interrupt\n"
            " 0:out off\n"
	    " 1:out on\n"
	    " 2:in\n"
	    " r:regs\n";
  switch(sys::deb::get())
  {
   case '0':
    out.val(false);
   break;
   case '1':
    out.val(true);
   break;
   case '2':
    sys::msg<<in.val()<<"\n";
   break;
   
   case 'r':
    sys::reg::EIC.regs();
    sys::deb::hex("PINMUX ",sys::reg::PORT::A.PMUX[0]);
    sys::deb::hex("PINCFG ",sys::reg::PORT::A.PINCFG[1]);
    sys::Pin::regs();
   break;
  }   
 }
}
