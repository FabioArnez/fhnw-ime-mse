//--------------------------
//debug
//(c) H.Buchmann FHNW 2016
//--------------------------
IMPLEMENTATION(debug,$Id$)
#include "sys/deb/deb.h"
#include "sys/msg.h"
#include "sys/hwreg.h"
#include "sys/soc.h"

class App:sys::SOC
{
 volatile static struct DEBUG
 {
  unsigned DHCSR;
  unsigned DCRSR;
  unsigned DCRDR;
  unsigned DEMCR;
  void regs() const volatile;
 } DEBUG;
 
 volatile static struct DWT
 {
  unsigned             CTRL;
  sys::ResW<0x00,0x1c> RES0;
  unsigned             PCSR;
  struct 
  {
   unsigned COMP;
   unsigned MASK;
   unsigned FUNCTION;
  } WATCH[0];
  void regs() const volatile;
 } DWT;
 
 static App app;
 static void bkpt();
 App();
};

#define REG(name) sys::deb::hex(name);\
sys::deb::out(" (");sys::deb::hex((void*)&name);sys::deb::out(") "#name"\n")

void App::DEBUG::regs() const volatile
{
 REG(DHCSR);
 REG(DCRSR);
 REG(DCRDR);
 REG(DEMCR);
}

void App::DWT::regs() const volatile
{
 REG(CTRL);
 REG(PCSR);
 unsigned n=0xf&(CTRL>>28);
 for(unsigned i=0;i<n;++i)
 {
  REG(WATCH[i].COMP);
  REG(WATCH[i].MASK);
  REG(WATCH[i].FUNCTION);
 }
}

//0xE000ED24 SHCSR
//0xE000ED30 DFSR
void App::bkpt()
{
 asm volatile
 (
  "	bkpt #0\n"
  :
  :
 );
}

App App::app;

App::App()
{
 sys::msg<<"Debug\n";
 while(true)
 {
  sys::msg<<"(b)kpt (r)egs (e)nable\n";
  switch(sys::deb::get())
  {
   case 'b':
    bkpt();
   break;
   
   case 'r':
    sys::msg<<"DEBUG\n";
    DEBUG.regs();
    sys::msg<<"DWT\n";
    DWT.regs();
   break;
   case 'e':
    DEBUG.DHCSR=(0xa05f<<16)|1;
   break;
  }
 }
}
