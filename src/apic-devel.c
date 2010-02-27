/*-------------------
 apic-devel
 (c) H.Buchmann FHNW 2009
 $Id$
---------------------*/
#include "sys/screen.h"
#include "io/ascii.h"
#include "sys/io.h"
#include "io/kbd.h"
#include "sys/trap.h"

typedef unsigned Entry[4];
typedef unsigned Bits[8];

volatile Entry* APIC_BASE=0;

Bits IRR;

static void read(unsigned ofs,Bits* b)
{
 for(unsigned i=0;i<8;++i) (*b)[i]=APIC_BASE[ofs][0];
}

static unsigned cnt=10;

static tick(unsigned id)
{
 if (cnt==10)
    {
     ascii_put(Screen,'x');
     cnt=0;
    }
 ++cnt;
}

static void show(Bits* b)
{
 for(unsigned i=0;i<8;++i)
 {
  ascii_unsigned_hex(Screen,(*b)[i]);
  ascii_put(Screen,' ');
 } 
 ascii_newln(Screen);
}

int main()
{
 trap_init(); 
 trap_install(8,tick);
 sys_sti();
 MSR msr=sys_read_msr(0x1b);
 unsigned flags=sys_getFlags();
 APIC_BASE=(Entry*)(msr&~((1<<12)-1));
 APIC_BASE[0x38][0]=0x10000000;
 APIC_BASE[0x32][0]|=0x20; 
 while(1)
 {
  ascii_printf(Screen,"         EFLAGS=%x\n"
                      "      MSR[0x1b]=%x\n"
                      " VERSION[0x030]=%x\n"
                      "      ID[0x020]=%x\n"
                      "Spurious[0x0f0]=%x\n"
		      "   Timer[0x320]=%x\n"
		      "    LVT0[0x350]=%x\n"
		      "    LVT1[0x360]=%x\n"
		      "  LVTERR[0x370]=%x\n"
		      "  T_INIT[0x380]=%x\n"
		      "   T_CUR[0x390]=%x\n"
		      "   T_CFG[0x3e0]=%x\n"
		      "     ESR[0x280]=%x\n"
		      "\n",
		      flags,
		      (unsigned)msr,
		      APIC_BASE[0x03][0],
		      APIC_BASE[0x02][0],
		      APIC_BASE[0x0f][0],
		      
		      APIC_BASE[0x32][0],
		      APIC_BASE[0x35][0],
		      APIC_BASE[0x36][0],
		      APIC_BASE[0x37][0],
		      
		      APIC_BASE[0x38][0],
		      APIC_BASE[0x39][0],
		      APIC_BASE[0x3e][0],
		      APIC_BASE[0x28][0]
		      );
  
  if (kbd_get()=='r') 
     {
      APIC_BASE[0x38][0]=0x10000000;
     }
 }
#if 0
 read(0x20,IRR);
 show(IRR);
 
 while(1)
 {
  Bits irr;
  read(0x20,irr);
  for(unsigned i=0;i<8;++i)
  {
   if (1) //irr[i]!=IRR[i])
      {
       show(irr);
       break;
      }   
  }
  for(unsigned i=0;i<8;++i) IRR[i]=irr[i];
 }
#endif
 return 0;
} 
