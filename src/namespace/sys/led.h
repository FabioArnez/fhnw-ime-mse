#pragma once
//--------------------------
//led
//(c) H.Buchmann FHNW 2016
// an exercise in member function call
// TODO why LED::Map is in the .bss segment
//--------------------------
INTERFACE(sys_led,$Id$)
#include "sys/reg/port.h"
#include "sys/deb/deb.h"

namespace sys
{
 class LED
 {
  public:

   enum ID {L,RX,TX};
   static void set(ID l){(Map[l].*Map[l].set)();}
   static void clr(ID l){(Map[l].*Map[l].clr)();}
   static void tgl(ID l){Map[l].outtgl();}

  private:
   struct Port
   {
    volatile reg::PORT*const port;
    const unsigned  pin;
    typedef void (LED::Port::*Op)() const;
    void outset()const{port->OUTSET=pin;}
    void outclr()const{port->OUTCLR=pin;}
    void outtgl()const{port->OUTTGL=pin;}
    const Op set;
    const Op clr;
    Port(volatile reg::PORT& port,reg::PORT::PIN pin,
	      Op set,Op clr)
    :port(&port),pin(1<<pin),set(set),clr(clr)
    {
     port.DIRSET=this->pin;
    }
   };
   
   static const Port Map[];
 };
}
