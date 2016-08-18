//--------------------------
//scb system control block
//(c) H.Buchmann FHNW 2014
//[1] superfluous/eo3s/arm/doc/DDI0403D_arm_architecture_v7m_reference_manual_errata_markup_1_0.pdf
//--------------------------
INTERFACE(sys_reg_scb,$Id$)
#include "sys/hwreg.h"
namespace sys
{
 namespace reg //[1] B3.2.2
 {
  extern volatile struct SCB
  {
   const unsigned CPUID;  // 0xe000ed00 RO IMPLEMENTATION CPUID Base Register on page B3-713.
	 unsigned ICSR;   // 0xe000ed04 RW 0x00000000 Interrupt Control and State Register, ICSR on
	 unsigned VTOR;   // 0xe000ed08 RW 0x00000000 a Vector Table Offset Register, VTOR on page B3-716.
	 unsigned AIRCR;  // 0xe000ed0c RW Application Interrupt and Reset Control Register,
	 unsigned SCR;    // 0xe000ed10 RW 0x00000000 System Control Register, SCR on page B3-718.
	 unsigned CCR;    // 0xe000ed14 RW 0x00000000 Configuration and Control Register, CCR on
	 unsigned SHPR1;  // 0xe000ed18 RW 0x00000000 System Handler Priority Register 1, SHPR1 on
	 unsigned SHPR2;  // 0xe000ed1c RW 0x00000000 System Handler Priority Register 2, SHPR2 on
	 unsigned SHPR3;  // 0xe000ed20 RW 0x00000000 System Handler Priority Register 3, SHPR3 on
	 unsigned SHCSR;  // 0xe000ed24 RW 0x00000000 System Handler Control and State Register, SHCSR on
	 unsigned CFSR;   // 0xe000ed28 RW 0x00000000 Configurable Fault Status Register, CFSR on
	 unsigned HFSR;   // 0xe000ed2c RW 0x00000000 HardFault Status Register, HFSR on page B3-732.
	 unsigned DFSR;   // 0xe000ed30 RW 0x00000000 c Debug Fault Status Register, DFSR on page C1-828.
	 unsigned MMFAR;  // 0xe000ed34 RW UNKNOWN MemManage Fault Address Register, MMFAR on
	 unsigned BFAR;   // 0xe000ed38 RW UNKNOWN BusFault Address Register, BFAR on page B3-734.
	 unsigned AFSR;   // 0xe000ed3c RW UNKNOWN Auxiliary Fault Status Register, AFSR on page B3-735,
   const Res<unsigned,0xE000ED40,0xE000ED88> RES0;
         unsigned CPACR;  // 0xE000ED88 RW UNKNOWN Coprocessor Access Control Register, CPACR on
  } SCB;
 }//namespace reg
}//namespace sys

