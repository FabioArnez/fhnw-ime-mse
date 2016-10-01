//------------------------
//eic external interrupt controller
//(c) H.Buchmann FHNW 2016
//------------------------
IMPLEMENTATION(sys_reg_eic,$Id$)
#include "sys/reg/eic.h"
#include "sys/deb/deb.h"
namespace sys
{
 namespace reg
 {
  void EIC::regs() const volatile
  {
#define REG(name) \
deb::hex(name,8);deb::out(" (");deb::hex((void*)&name);deb::out(") "#name"\n")

   REG(CTRL);     // 0x00 
   REG(STATUS);   // 0x01 
   REG(NMICTRL);  // 0x02 
   REG(NMIFLAG);  // 0x03 
   REG(EVCTRL);	 // 0x04 
   REG(INTENCLR); // 0x08 
   REG(INTENSET); // 0x0c 
   REG(INTFLAG);	 // 0x10 
   REG(WAKEUP);	 // 0x14 
   REG(CONFIG[0]);// 0x18 
  }
  
  void EIC::init() volatile
  {
   CTRL|=(1<<1); //enable
   while(STATUS&(1<<7)){}
  }

  void EIC::enable(PIN p) volatile
  {
   INTENSET|=(1<<p);
  }
  
  void EIC::sense(PIN p,SENSE s) volatile
  {
   unsigned bpos=p*4;
   unsigned idx=bpos/32;
   unsigned pos=bpos%32;
   unsigned config=CONFIG[idx];
   unsigned mask=~(0x7<<pos);
   config&=mask;
   config|=(s<<pos);
   CONFIG[idx]=config;
  }
  
  void EIC::filter(PIN p,bool v) volatile
  {
   unsigned bpos=p*4;
   unsigned idx=bpos/32;
   unsigned pos=3+bpos%32;
   unsigned config=CONFIG[idx];
   if (v)
      {
       CONFIG[idx]|=1<<pos;
      }
      else
      {
       CONFIG[idx]&=1<<pos;
      } 
  }

 }
}
