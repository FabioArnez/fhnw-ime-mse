//----------------------
//port-demo
//(c) H.Buchmann FHNW 2016
//using Arduino LED L,PA17 as output 
//[1] Atmel | SMART  SAM D21J, SAM D21G, SAM D21E, 
//    ARM Cortex-M0+ based Embedded Flash Microcontroller
//    Atmel-42181-SAM-D21_Datasheet.pdf
//----------------------
IMPLEMENTATION(port_demo,$Id$)
#include "sys/msg.h"
#include "sys/deb/deb.h"

class App
{
 static App app;
  struct PORT  //see [1] 23.7
  {
   unsigned DIR;             //0x00
   unsigned DIRCLR;          //0x04
   unsigned DIRSET;          //0x08
   unsigned DIRTGL;          //0x0c
   unsigned OUT;             //0x10
   unsigned OUTCLR;          //0x14
   unsigned OUTSET;          //0x18
   unsigned OUTTGL;          //0x1c
   unsigned IN;              //0x20
   unsigned CTRL;            //0x24
   unsigned WRCONFIG;        //0x28
   unsigned RES;             //0x2c
   static const unsigned PMUXN=32/(2*4);
   unsigned PMUX[PMUXN];     //0x30
   static const unsigned PINCFGN=32/4;
   unsigned PINCFG[PINCFGN]; //0x40
   static volatile PORT A;   //address defined in linker script layout.ld
  };

 static const unsigned PA17=(1<<17);
 App();
 void init();
 void clear();
 void set();
 void toggle();
 void menu();
};


App App::app;

void App::init()
{
 PORT::A.DIRSET=PA17;  //as output
}

void App::clear()
{
 PORT::A.OUTCLR=PA17;
}

void App::set()
{
 PORT::A.OUTSET=PA17;
}

void App::toggle()
{
 PORT::A.OUTTGL=PA17;
}

void App::menu()
{
 while(true)
 {
  sys::msg<<"(c)clear (s)et (t)oggle:";
  switch(sys::deb::get())
  {
   case 'c':
    clear();
   break;
   case 's':
    set();
   break;
   case 't':
    toggle();
   break;
  }
  sys::msg<<"\n";
 }
}

App::App()
{
 sys::msg<<"Port Demo\n";
 init();
 menu();
}


