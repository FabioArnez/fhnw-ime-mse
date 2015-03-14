//------------------------
//coroutine0
//(c) H.Buchmann FHNW 2015
//------------------------
INTERFACE(sys_coroutine0,$Id$)
#include "sys/coroutine0.h"
#include "sys/msg.h"

namespace sys
{
 
 void Coroutine0::Status::show(const char msg[])
 {
  static const char* Reg[]=
  {
   " r0"," r1"," r2"," r3",
   " r4"," r5"," r6"," r7",
   " r8"," r9","r10","r11",
   "r12"
  };
  sys::msg<<msg<<"\n";
  sys::msg<<"status="<<(void*)this<<"\n";
  unsigned ri=0;
  for(unsigned r=0;r<3;++r)
  {
   for(unsigned c=0;c<4;++c)
   {
    sys::msg<<Reg[ri]<<"="<<io::ascii::hex()<<run.reg0_12[ri]<<" ";
    ++ri;
   }
   sys::msg<<"\n";
  }
   sys::msg<<Reg[ri]<<"="<<io::ascii::hex()<<run.reg0_12[ri]<<"\n"
           <<      " lr="<<io::ascii::hex()<<run.lr<<"\n";
 }

#if 1
 void Coroutine0::Status::show()
 {
  show("deb");
 }
#endif 
 Coroutine0::Coroutine0()
 {
 }
 
 Coroutine0::Coroutine0(unsigned workspace[],unsigned size)
 :status((Status*)(workspace+size-sizeof(Status)/sizeof(unsigned)))
 {
  status->init=(Status::Init){this,
               {1,2,3,4,5,6,7,8,9,10,11,12},
	       callInit};
  sys::msg<<"c="<<(void*)this<<" "
          <<"ws="<<(void*)workspace<<" "
	  <<"status="<<(void*)status<<" "
	  <<"sizeof(Status)="<<sizeof(Status)<<"\n";
//  status->show("Coroutine0::Coroutine0");
 }
 
#if 0
 void Coroutine0::transfer(Status** from,Status* to)
 {
  to->show("to");
 }
#endif
}
