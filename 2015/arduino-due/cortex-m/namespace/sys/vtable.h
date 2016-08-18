#pragma once
//-------------------------
//vtable vector table
//used in soc and reg/scs
//(c) H.Buchmann FHNW 2014
//-------------------------
INTERFACE(sys_vtable,$Id$)
namespace sys
{
 struct VTable
 {
  typedef void (*Entry)(); //for trap
 };
}

