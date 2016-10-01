#pragma once
//-------------------------------
//armv6-m
//(c) H.Buchmann FHNW 2016
//[1] ARMv6-M Architecture
//    Reference Manual
//    DDI0419C_arm_architecture_v6m_reference_manual.pdf
//-------------------------------
INTERFACE(sys_armv6_m,$Id$)
#include "sys/vtable.h"
#include "sys/deb/deb.h"
#include "sys/reg/nvic.h"
#include "sys/reg/scb.h"
namespace sys
{
 class ARMv6_M
 {
  public:
   typedef sys::VTable<32,256> VTable;
   typedef reg::NVIC<32>       NVIC;

   static const VTable& vtor(){return *VTOR;}
   static volatile const NVIC& nvic(){return NVIC_;}
   static const unsigned StackTop[];
   static void CPSIE(); //Interrupt Enable
   static void CPSID(); //Interrupt Disable
   
  protected:
   ARMv6_M(const VTable& vTable)
   {
    VTOR=&vTable;
   }


   static void hardFault();
   static void defaultTrap()
   {
    deb::hex("defaultTrap ICSR=",reg::SCB.ICSR);
	deb::signal1();
   }
   static void arm(unsigned id){NVIC_.arm(id);}
   static void disarm(unsigned id){NVIC_.disarm(id);}

  private:
   static const VTable* VTOR;
   volatile static NVIC NVIC_;
 };
 
 
 inline void ARMv6_M::CPSIE()
 {
  asm volatile
  (
   "cpsie i\n\t"
   :
   :
  );
 }

 inline void ARMv6_M::CPSID()
 {
  asm volatile
  (
   "cpsid i\n\t"
   :
   :
  );
 }
 
}
