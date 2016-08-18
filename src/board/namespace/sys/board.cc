//----------------------------
//board
//(c) H.Buchmann FHNW 2016
//----------------------------
IMPLEMENTATION(sys_board,$Id$)
#include "sys/board.h"
#include "sys/reg/sysctrl.h"
#include "sys/reg/gclk.h"
#include "sys/reg/pm.h"
#include "sys/deb/deblow.h"
#include "sys/reg/sercom.h"
#include "sys/boot/big-bang-continued.h"
#include "sys/deb/deb.h"
#include "sys/reg/nvmctrl.h"

namespace sys
{
#if 0
 extern "C"
 {
  void raise()
  {
   sys::deb::out("raise");
   sys::deb::signal1();
  } 
 }
#endif
//see layout.ld
 extern "C" unsigned _data_beg[];
 extern "C" unsigned _data_end[];
 extern "C" unsigned _text_end[];

 void Board::bigBang()
 {
  clock();
  data();
  deb::init();
  boot::start();
  deb::signal1();
 }
 
void Board::data()
{
  unsigned* src=_text_end;
  for(unsigned* dst=_data_beg;dst!=_data_end;++dst)
  {
   *dst=*src++;
  }
}

//TODO more modular 
 void Board::clock()  
 {
  unsigned osc8m=reg::SYSCTRL.OSC8M;
  osc8m&=~ ((0x3<<8) | //PRESC
            (  1<<7)); //ONDEMAND
  osc8m|= (0<<8)|      //PRESC
          (0<<7);      //ONDEMAND
  reg::SYSCTRL.OSC8M=osc8m;

 
  reg::PM.APBAMASK|=(1<<3);
  reg::SYSCTRL.XOSC32K = (0x6<<8) | //STARTUP
                         (  1<<2) | //XTALEN
                         (  1<<3) | //EN32K
                               0;
  reg::SYSCTRL.XOSC32K|=(1<<1);    //ENABLE
  
  while((reg::SYSCTRL.PCLKSR&(1<<1))==0){}

  reg::GCLK.reset();

  reg::GCLK.gendiv(reg::GCLK.G1,0);
  reg::GCLK.src2gen(reg::GCLK.OSC8M,reg::GCLK.G1);
  reg::GCLK.gen2dev(reg::GCLK.G1,reg::GCLK::DFLL48M_REF);


  reg::SYSCTRL.DFLLCTRL&=~(1<<7); //ONDEMAND=0  
  while ((reg::SYSCTRL.PCLKSR&(1<<4))==0){} 

#if 0
  reg::SYSCTRL.DFLLMUL=(
              (31<<26) |   //CSTEP
             (511<<16) |   //FSTEP
 ((48000000/32768)<<0) |   //MUL
                     0
                       );
#endif     
  reg::SYSCTRL.DFLLMUL=(
              (31<<26) |   //CSTEP
             (511<<16) |   //FSTEP
 ((48000000/8000000)<<0) |   //MUL
                     0
                       );
                                           
  while ((reg::SYSCTRL.PCLKSR&(1<<4))==0){} 
  
  reg::SYSCTRL.DFLLCTRL|=(
     (1<< 2) |   // mode closed loop
         (1<<11) |   // Output clock when DFLL is locked
         (1<< 9) |   // Quick Lock is disabled
               0
                         );
 
  while ((reg::SYSCTRL.PCLKSR&(1<<4))==0){} 
  reg::SYSCTRL.DFLLCTRL|=(1<<1); //ENABLE
  
  while(true)
  {
   static const unsigned MASK=(1<<7)|(1<<6);
   unsigned pclksr=reg::SYSCTRL.PCLKSR;
   if ((pclksr&MASK)==MASK) break; //both 1
  }

  while((reg::SYSCTRL.PCLKSR&(1<<4))==0){}

 
  reg::GCLK.gendiv(reg::GCLK.G0,0);
  reg::GCLK.sync();

  reg::PM.CPUSEL =(0<< 0)| //CPUSEL div 1
                  (0<< 8)| //APBASEL  //div 
                  (0<<16)| //APBBSEL  //div
                  (0<<24); //APBCSEL  //div 

  reg::NVMCTRL.CTRLB=(1<< 1)| //1 wait state
                     (1<< 7)| //MANW
                     (0<<18)| //cache enabled
		            0;    
  reg::GCLK.src2gen(reg::GCLK::DFLL48M,reg::GCLK::G0);
  reg::GCLK.sync();
 }
}
