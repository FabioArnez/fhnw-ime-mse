//--------------------------
//debug
//(c) H.Buchmann FHNW 2016
//--------------------------
IMPLEMENTATION(debug,$Id$)
#include "sys/deb/deb.h"
#include "sys/msg.h"

class App
{
 volatile static struct DEBUG
 {
  unsigned DHCSR;
  unsigned DCRSR;
  unsigned DCRDR;
  unsigned DEMCR;
  void regs() const volatile;
 } DEBUG;
 static App app;
 App();
};

void App::DEBUG::regs() const volatile
{
#define REG(name) sys::deb::hex(name);\
sys::deb::out(" (");sys::deb::hex((void*)&name);sys::deb::out(") "#name"\n")
 REG(DHCSR);
 REG(DCRSR);
 REG(DCRDR);
 REG(DEMCR);
}

App App::app;

App::App()
{
 sys::msg<<"Debug\n";
 while(true)
 {
  sys::msg<<"(r)egs (e)nable\n";
  switch(sys::deb::get())
  {
   case 'r':
    DEBUG.regs();
   break;
   case 'e':
    DEBUG.DHCSR=(0xa05f<<16)|1;
   break;
  }
 }
}
