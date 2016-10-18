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


class App
{
 static App app;
 static const unsigned ONE_SEC=15625;  //2^9 * ONE_SEC=8000000

 void menu();
 App();
};




App App::app;

void App::menu()
{
 if (!sys::deb::avail()) return;
 switch(sys::deb::get())
 {
  case 'h':
  case '?':
   sys::msg<<"(h|?) help (c)ount (r)egs: ";
  break;
  case 'c':
   sys::msg<<sys::reg::TC3.COUNT16<<"\n";
  break;
  case 'r':
   sys::msg<<"TC3.regs()\n";
   sys::reg::TC3.regs();
  break;
 } 
}

App::App()
{
 //CLK_TCx_APB
 sys::msg<<"TC-Demo\n";
 sys::reg::PM.APBCMASK|=(1<<11); //enable TC3 

 sys::reg::GCLK.src2gen(sys::reg::GCLK::OSC8M,sys::reg::GCLK::G8,(1<<0));
 sys::reg::GCLK.gen2dev(sys::reg::GCLK::G8,sys::reg::GCLK::TC3);
 sys::reg::GCLK.gendiv(sys::reg::GCLK::G8,0xff);    //8MHz/255

 sys::msg<<"GCLK done\n"; 
 
 sys::reg::TC3.CTRLA=0x1; //reset
 while((sys::reg::TC3.CTRLA&1) && (sys::reg::TC3.STATUS&(1<<31)))
 {
 }
 
 sys::reg::TC3.CTRLA|=(7<<8);		  //prescale 2^10
 sys::reg::TC3.COUNT16=0x0000;
 sys::reg::TC3.CC16[0]=ONE_SEC;
 sys::reg::TC3.CTRLA|=(1<<1);             //enable
 while(true)
 {
  menu();
  if (sys::reg::TC3.INTFLAG&(1<<4))
     {
      sys::reg::TC3.INTFLAG=(1<<4);
      sys::LED::tgl(sys::LED::L);
     }
 }
 
}
