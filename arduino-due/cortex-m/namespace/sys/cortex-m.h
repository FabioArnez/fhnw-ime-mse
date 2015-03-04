#pragma once
//-----------------------------
//cortex-m
//(c) H.Buchmann FHWN 2013
//[1] Cortex-M4 Devices Generic User Guide
//-----------------------------
INTERFACE(sys_cortex_m,$Id$)
#include "sys/reg/scs.h"
#include "sys/msg.h"

namespace sys
{
 template<unsigned TRAPN>
 class CortexM        //it is a singleton
 {
  public:
   enum Exception
   {
    RESET         = 1,
    NMI           = 2,
    HARD_FAULT    = 3,
    MEM_MANAGE    = 4,
    BUS_FAULT     = 5,
    USAGE_FAULT   = 6,
    //reserved    7-10
    SV_CALL       =11,
    DEBUG_MONITOR =12,
    //reserved     13
    PEND_SV       =14,
    SYS_TICK      =15,
    EXTERNAL      =16
   };
   
   static void arm(unsigned id)
   {if (inRange(id))reg::SCS.NVIC.ISER[id/32]=(1<<(id%32));}
   
   static void disarm(unsigned id)
   {if (inRange(id))reg::SCS.NVIC.ICER[id/32]=(1<<(id%32));}
   
   static void trigger(unsigned id); //TODO 
   static void install(unsigned id,VTable::Entry t)
   {if (inRange(id)){disarm(id);vTable[id]=t;}}


   static void cpsIE_i()
   {
    asm volatile
    (
     "cpsie i\n\t"
     :
     :
    );
   }

   static void cpsID_i()
   {
    asm volatile
    (
     "cpsid i\n\t"
     :
     :
    );
   }

   static void cpsIE_f()
   {
    asm volatile
    (
     "cpsie f\n\t"
     :
     :
    );
   }

   static void cpsID_f()
   {
    asm volatile
    (
     "cpsid f\n\t"
     :
     :
    );
   }


   static void svc()
   {
    asm volatile
    (
     "svc #4\n\t"
     :
     :
    );
   }
   
   static unsigned ipsr()
   {
    unsigned id;
    asm volatile
    (
     "mrs %[id],ipsr\n\t"
     :[id] "=r" (id) //output
     :
    );
    return id;
   }

#if 0   
   template<typename T>
   static T ldx(const T*const addr) //exclusive
   {
    T val;
    asm volatile
    (
     "@----------------------------------- ldx\n\t"
     "ldrex %[val], [%[addr]]\n\t"
     :[val] "=r" (val)
     :[addr] "r" (addr)
    );
    return val;
   }
   
   template<typename T>
   static unsigned stx(T*const addr,T val)
   {
    unsigned res;
    asm volatile
    (
     "@----------------------------------- stx\n\t"
     "strex %[res],%[val],[%[addr]]\n\t"
     :[res] "=r" (res)
     :[addr] "r" (addr),
      [val]  "r" (val)
    );
    return res;
   }
#endif  
  protected:
   CortexM()
   {
    for(unsigned i=0;i<TRAPN;++i) vTable[i]=trap;
    sys::msg<<"vTable="<<(void*)vTable<<"\n";
    sys::reg::SCS.SCB.VTOR=vTable;
   }
   
  private:
   static void trap() //always the same 
   {
    sys::msg<<"unexpected trap\n";
   }
   
   static bool inRange(unsigned id){return id<TRAPN;}

   static VTable::Entry vTable[TRAPN] alignas(256);
                                  //TRAPN
 };
 
 template<unsigned TRAPN>
 typename VTable::Entry CortexM<TRAPN>::vTable[TRAPN];
}
