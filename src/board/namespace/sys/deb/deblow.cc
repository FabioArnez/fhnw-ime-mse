//------------------------
//deblow
//(c) H.Buchmann FHNW 2016
//------------------------
IMPLEMENTATION(sys_deb_low,$Id$)
#include "sys/deb/deblow.h"
#include "sys/reg/port.h"
#include "sys/reg/sercom.h"
#include "sys/reg/gclk.h"
#include "sys/reg/pm.h"
#include "sys/reg/scb.h"
namespace sys
{
 namespace deb
 {
  void init()   //9600 Baud
  {
   reg::PM.APBCMASK|=(1<<7); //sercom5
  

   reg::PORT::B.mux(reg::PORT::P_22,reg::PORT::F_D); //TX SERCOM5/PAD[2]
   reg::PORT::B.mux(reg::PORT::P_23,reg::PORT::F_D); //RX SERCOM5/PAD[3]
//reset UART
   reg::SER::COM5.USART.CTRLA|=1; 
   while( (reg::SER::COM5.USART.CTRLA&1) || (reg::SER::COM5.USART.SYNCBUSY&1))
   {
   }

//G0 Clock
   reg::GCLK.gen2dev(reg::GCLK::G1,reg::GCLK::SERCOM5_CORE);
   reg::GCLK.sync();

//reverse engineered  
//   reg::SER::COM5.USART.BAUD =0x0000ff2d;  //G0=48Mhz 
   reg::SER::COM5.USART.BAUD =64278;       //G1= 8Mhz

   reg::SER::COM5.USART.CTRLA=0x40310006;
   reg::SER::COM5.USART.CTRLB=0x00030000;
   
   while(reg::SER::COM5.USART.SYNCBUSY&(1<<1)){}
  }
  
  static const unsigned CNT=0x80000;


#warning shared with CLK of SERCOM 1
#if 0
  void signal0()
  {
   static const unsigned PA_17=(1<<reg::PORT::P_17);
   reg::PORT::A.DIRSET=PA_17;
   while(true)
   {
    reg::PORT::A.OUTTGL=PA_17;
    wait(CNT);
   }
  }
#endif

  void signal1()
  {
   static const unsigned PB_03=(1<<reg::PORT::P_03);
   reg::PORT::B.DIRSET=PB_03;
   while(true)
   {
    reg::PORT::B.OUTTGL=PB_03;
    wait(CNT);
   }
  }

  void out(char ch)
  {
   if (ch=='\n') out('\r');   
   while((reg::SER::COM5.USART.INTFLAG & (1<<0))==0)
   {
   }
   reg::SER::COM5.USART.DATA=ch;
  }
  
  char get()
  {
   while((reg::SER::COM5.USART.INTFLAG & (1<<2))==0)
   {
   }
   return reg::SER::COM5.USART.DATA;
  }
  
  
  void halt()
  {
   signal1();
  }
  
  void enter()
  {
  }
  
  void reset()
  {
   reg::SCB.AIRCR=(0x05fa<<16)|(1<<2);
   while(true){}
  }
  
  bool avail()
  {
   return (reg::SER::COM5.USART.INTFLAG & (1<<2))!=0;
  }
  
  void disableInterrupts()
  {
   asm volatile
   (
    "cpsid i\n\t"
    :
    :
   );
  }
 } //namespace deb
} //namespace sys
