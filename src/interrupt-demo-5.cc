//--------------------------
//interrupt-demo-5
// enable the interrupt system
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
{
 VTOR=&VectorTable;
 sys::msg<<"VTOR="<<(void*)VTOR<<"\n"; //check alignement
 CPSIE();
 SYST.RVR=(1<<24)-1;
 SYST.CSR=(1<<0) | //start
          (1<<1);  //enable interrupt
 while(true)
 {
  sys::deb::out(sys::deb::get()); //background process
 }
}
