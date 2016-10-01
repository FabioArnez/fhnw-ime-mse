//------------------------------
//pin
//(c) H.Buchmann FHNW 2016
//------------------------------
IMPLEMENTATION(sys_pin,$Id$)
#include "sys/pin.h"
#include "sys/deb/deb.h"
namespace sys
{
 volatile reg::PORT*const Pin::Port[]={&reg::PORT::A,&reg::PORT::B};

 void Pin::regs()
 {
  sys::deb::out("Port A\n");
  regs(*Port[0]);
  sys::deb::out("Port B\n");
  regs(*Port[1]);
 }
 
 void Pin::regs(const volatile reg::PORT& p)
 {
#define REG(name) \
{deb::hex(name);deb::out(" (");deb::hex((void*)&name);deb::out(") "#name"\n");}
  REG(p.DIR);      //0x00
  REG(p.DIRCLR);   //0x04
  REG(p.DIRSET);   //0x08
  REG(p.DIRTGL);   //0x0c
  REG(p.OUT);      //0x10
  REG(p.OUTCLR);   //0x14
  REG(p.OUTSET);   //0x18
  REG(p.OUTTGL);   //0x1c
  REG(p.IN);       //0x20
  REG(p.CTRL);     //0x24
  REG(p.WRCONFIG); //0x28
  for(unsigned i=0;i<p.PMUXN;++i)   REG(p.PMUX[i]);
  for(unsigned i=0;i<p.PINCFGN;++i) REG(p.PINCFG[i]);//0x40
 }

}
