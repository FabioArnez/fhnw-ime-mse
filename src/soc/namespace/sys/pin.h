#pragma once
//------------------------------
//pin
//(c) H.Buchmann FHNW 2016
//------------------------------
INTERFACE(sys_pin,$Id$)
#include "sys/reg/port.h"
#include "sys/deb/deb.h"

namespace sys
{
 class Pin
 {
  public:
   enum ID
   {
    PA00,PA01,PA02,PA03,PA04,PA05,PA06,PA07,PA08,PA09,
    PA10,PA11,PA12,PA13,PA14,PA15,PA16,PA17,PA18,PA19,
    PA20,PA21,PA22,PA23,PA24,PA25,PA26,PA27,PA28,PA29,
    PA30,PA31,

    PB00,PB01,PB02,PB03,PB04,PB05,PB06,PB07,PB08,PB09,
    PB10,PB11,PB12,PB13,PB14,PB15,PB16,PB17,PB18,PB19,
    PB20,PB21,PB22,PB23,PB24,PB25,PB26,PB27,PB28,PB29,
    PB30,PB31,
   };

   void mux(reg::PORT::FUNC f){reg::PRT[port].mux(pin,f);}
   class Output;
   class Input;
   
   static void regs();
   
  protected:
   const ID id;
   const unsigned port;
   const reg::PORT::PIN pin; 
   constexpr Pin(const ID p)
   :id(p)
   ,port((p<=PA31)?0:1)
   ,pin((reg::PORT::PIN)(p%32))
   {
   }

  private:
   static volatile reg::PORT*const Port[2];
   static void regs(const volatile reg::PORT&); 
 };
 
 class Pin::Output:public Pin
 {
  public:
   Output(ID p,bool v)
   :Pin(p)
   {
    reg::PRT[port].DIRSET=(1<<pin);
//    reg::PRT[port].DIRSET=(1<<pin);
    val(v);
   }
   
   void val(bool v)
   {
    if (v)  reg::PRT[port].OUTSET=(1<<pin);
       else reg::PRT[port].OUTCLR=(1<<pin);
#if 0
    if (v)  reg::PRT[port].OUTSET=(1<<pin);
       else reg::PRT[port].OUTCLR=(1<<pin);
#endif
   }

   bool val() const
   {
    return (reg::PRT[port].OUT&(1<<pin))!=0;
   }
   
   operator bool()const {return val();}
   void operator()(bool v){val(v);}
   void tgl(){reg::PRT[port].OUTTGL=(1<<pin);}

   void operator=(bool v){val(v);}
//logical operators
   void operator&=(bool v){if(!v) val(false);}
   void operator|=(bool v){if(v) val(true);}
   void operator^=(bool v){if (v) tgl();}
 };
 
 class Pin::Input:public Pin
 {
  public:
   bool val() const
   {
    return (reg::PRT[port].IN&(1<<pin))!=0;
   }
   
   operator bool()const {return val();}

   Input(ID p)
   :Pin(p)
   {
//     deb::hex("pin=",pin);
     reg::PRT[port].DIRCLR=(1<<pin);
//     reg::PRT[port].CTRL=(1<<pin);
     reg::PRT[port].cfg(pin,(1<<1)); //INEN
   }
 };
}
