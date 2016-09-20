//-------------------------------
//armv6-m
//(c) H.Buchmann FHNW 2016
//[1] ARMv6-M Architecture
//    Reference Manual
//    DDI0419C_arm_architecture_v6m_reference_manual.pdf
//-------------------------------
IMPLEMENTATION(sys_armv6_m,$Id$)
#include "sys/armv6-m.h"
namespace sys
{
 void ARMv6_M::hardFault()
 {
  deb::out("hardFault\n");
  deb::signal1();
 }

extern "C"
{
 unsigned __atomic_exchange_4(volatile void* ptr,unsigned val,int memodel)
 {
  sys::ARMv6_M::CPSID(); //disable interrupt
  unsigned v=*(unsigned*)ptr;
  *(unsigned*)ptr=val;
  sys::ARMv6_M::CPSIE(); //enable interrupt
  return v;
 }
}

}
