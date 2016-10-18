//--------------------------
//led
//(c) H.Buchmann FHNW 2016
//--------------------------
IMPLEMENTATION(sys_led,$Id$)
#include "sys/led.h"
//#define LED_TEST
//#include "sys/deb/deb.h"

namespace sys
{
 const LED::Port LED::Map[]
 {
  {sys::reg::PORT::A,sys::reg::PORT::P_17,&LED::Port::outset,&LED::Port::outclr}, //L
  {sys::reg::PORT::B,sys::reg::PORT::P_03,&LED::Port::outclr,&LED::Port::outset}, //RX
  {sys::reg::PORT::A,sys::reg::PORT::P_27,&LED::Port::outclr,&LED::Port::outset}  //TX
 };

/*
 led    Pin
 L      PA17
 RX     PB03
 TX     PA27
*/

}

#ifdef LED_TEST
class Tester
{
 static Tester tester;
 Tester();
 sys::LED::ID led=sys::LED::L;
};

Tester Tester::tester;

Tester::Tester()
{
 while(true)
 {
  sys::deb::out("Led (L),(T)X,(R)X\n (s)et (c)lr (t)gl:\n");
  switch(sys::deb::get())
  {
   case 'L':led=sys::LED::L;break;
   case 'T':led=sys::LED::TX;break;
   case 'R':led=sys::LED::RX;break;
   case 's':sys::LED::set(led);break;
   case 'c':sys::LED::clr(led);break;
   case 't':sys::LED::tgl(led);break;
  }
 }
}
#endif
