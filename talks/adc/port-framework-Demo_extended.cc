//----------------------
//port-framework-demo using sys/pin
//(c) H.Buchmann FHNW 2016
//----------------------
IMPLEMENTATION(port_demo,$Id$)
#include "sys/msg.h"
#include "sys/deb/deb.h"
#include "sys/pin.h"
#include "sys/reg/eic.h"
#include "sys/reg/nvic.h"

class App
{
 static App app;
 App();
 sys::Pin::Output rxLed; //PB03 rx Led
 sys::Pin::Output led1;  // PA08
 sys::Pin::Output led2;  // PA09
 sys::Pin::Output led3;  // PA14

 sys::Pin::Input  myInputSignal;


  static volatile sys::reg::NVIC<27>  NVIC; //see [2] 11.2.2

 typedef void (*Trap)(); //the call back
 struct VTable  //see [1] B1.5.2/3 [2] 11.2.2
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
   Trap PM;
   Trap SYSCTRL;
   Trap WDT;
   Trap RTC;
   Trap EIC;
   //more and more
  } ;

//the callbacks
//TODO try to myke them as templates 
 static void reset();
 static void nmi();
 static void hardFault();
 static void reserved();
 static void svCall();
 static void pendSV();
 static void sysTick();
 static void eic();
 static void unexpected();

 static const VTable VectorTable;
 static VTable* VTOR;
 static void CPSIE();

  // App();
 void onPin(); //the future call back
 void initEIC();   //TODO make EIC as a class the code in initEIC will be moved into the
                   //     the constructor

 void menu();
};

App App::app;

alignas(256) const App::VTable App::VectorTable=
{
0,
reset,
nmi,
hardFault,
{reserved,reserved,reserved,reserved,reserved,reserved},
svCall,
{reserved,reserved},
pendSV,
sysTick,
unexpected,
unexpected,
unexpected,
unexpected,
eic
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

void App::sysTick()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

void App::unexpected()
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
}

void App::eic() //static function
{
 sys::msg<<__PRETTY_FUNCTION__<<"\n";
 sys::reg::EIC.INTFLAG|=sys::reg::EIC.INTFLAG;
 app.onPin(); //call back
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
 sys::msg<<"Interrupt Fired!!! --->  HIGH\n";
 // out.val(false);
  rxLed^=true;
  led1^=true;
  led2^=true;
  led3^=true; 
}


void App::menu()
{
 while(true)
 {
  sys::msg<<"(c)clear (s)et (t)oggle:";
  switch(sys::deb::get())
  {
   case 'c':
    rxLed=false;
    led1=false;
    led2=false;
    led3=false;
   break;
   case 's':
    rxLed=true;
    led1=true;
    led2=true;
    led3=true;
   break;
   case 't':
    rxLed^=true;
    led1^=true;
    led2^=true;
    led3^=true;
   break;
   case 'p':
    sys::Pin::regs();
   break;
  }
  sys::msg<<"\n";
 }
}

// PB03:Rx Led
App::App()
:rxLed(sys::Pin::PB03,false),
led1(sys::Pin::PA08,false),
led2(sys::Pin::PA09,false),
led3(sys::Pin::PA14,false),
myInputSignal (sys::Pin::PA06)
{
 VTOR=&VectorTable;
 CPSIE();
 NVIC.ISER[0]|=(1<<4);
 initEIC();
 sys::msg<<"Port Framework Demo! (Extended)\n";
 menu();
}


