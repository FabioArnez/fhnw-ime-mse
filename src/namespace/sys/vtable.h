#pragma once
//-------------------------
//vtable vector table
//used in soc and reg/scs
//(c) H.Buchmann FHNW 2014
//-------------------------
INTERFACE(sys_vtable,$Id$)
namespace sys
{
 template<unsigned N,unsigned align>
 struct VTable
 {
  static const unsigned SIZ=N;
  typedef void (Entry)(); //for trap
  const unsigned*const sp;
  Entry*    reset;
  Entry*    nmi;
  Entry*    hardFault;
  Entry*    reserved0[7];
  Entry*    svCall;
  Entry*    reserved1[2];
  Entry*    pendSV;
  Entry*    sysTick;
  Entry*    external[N];
 }__attribute__((aligned(align)));
}

