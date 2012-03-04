/*-----------------------------------
  gic generic interrupt controller
  (c) H.Buchmann FHNW 2012
  $Id$
  [1] literature/realview_emulation_basebord_ug.pdf
  TODO only GIC1 is used remove unnecessary stuff
       nesting interrupts
-------------------------------------*/
#include "sys/gic.h"
#include "sys/deb.h"
#include "stdio.h"

typedef struct{
       unsigned CPUControl;         /* 000 */
       unsigned Priority;           /* 004 */   
       unsigned Point;              /* 008 */
 const unsigned Acknowledge;        /* 00c */
       unsigned EndInterrupt;       /* 010 */
 const unsigned Running;            /* 014 */
 const unsigned Highest_Pending;    /* 018 */
} GIC_IFC; 

#undef ARR
#undef RES

#define ARR(name,start,end) unsigned name[1+(end-start)/sizeof(unsigned)] 
#define RES(id,start,end) ARR(RES##id,start,end)

typedef struct{
      unsigned Control;
const unsigned ControllerType;
	       RES(0,0x1008,0x10fc);
      unsigned Enable[3];
	       RES(1,0x110c,0x117c);
      unsigned Clear[3];
	       RES(2,0x118c,0x11fc);
      unsigned PendingSet[3];
	       RES(3,0x120c,0x127c);
      unsigned PendingClear[3];
	       RES(4,0x128c,0x12fc);
const unsigned Active[3];
	       RES(5,0x130c,0x13fc);
	       ARR(Priority,0x1400,0x143c);
	       RES(6,0x1440,0x17FC);
      unsigned CPUTargets[24];
	       RES(7,0x1860,0x1bfc);
      unsigned Configuration[6];
	       RES(8,0x1c18,0x1efc);
      unsigned Software;
} GIC_DIS;

extern volatile GIC_IFC GIC1_IFC;
extern volatile GIC_IFC GIC2_IFC;
extern volatile GIC_IFC GIC3_IFC;
extern volatile GIC_IFC GIC4_IFC;

extern volatile GIC_DIS GIC1_DIS;
extern volatile GIC_DIS GIC2_DIS;
extern volatile GIC_DIS GIC3_DIS;
extern volatile GIC_DIS GIC4_DIS;

volatile GIC_IFC*const IFC[]={&GIC1_IFC,&GIC2_IFC,&GIC2_IFC,&GIC4_IFC};
volatile GIC_DIS*const DIS[]={&GIC1_DIS,&GIC2_DIS,&GIC3_DIS,&GIC4_DIS};

static Trap traps[TRAP_N]; /* the call back */

void gic_init()
{
 for(unsigned i=0;i<TRAP_N;++i) traps[i]=0;
 for(unsigned i=0;i<4;++i)
 {
  IFC[i]->CPUControl=1;
  DIS[i]->Control=1;
  for(unsigned k=0;k<24;++k) DIS[i]->CPUTargets[k]=1;
 }
 for(unsigned i=0;i<4;++i)
 {
  printf("%d\t%x\t%p\n",i,DIS[i]->ControllerType,&(DIS[i]->Software));
 }
}


void gic_enable(unsigned id)
{
 if (id>=TRAP_N) return;
 DIS[0]->Enable[id/32]|=(1<<(id%32));
}

void gic_disable(unsigned id)
{
 if (id>=TRAP_N) return;
 DIS[0]->Clear[id/32]|=(1<<(id%32));
}

void gic_install(unsigned id,Trap t)
{
 if (id>=TRAP_N) return;
 traps[id]=t;
}

/*------------------------------- called by hardware */
void gic_onIRQ()__attribute__((interrupt("IRQ")));
void gic_onIRQ()
{
 while(1)
 {
  unsigned id=IFC[0]->Acknowledge;
  if (id>=TRAP_N) break;
  Trap t=traps[id];
  if (t)t();
  IFC[0]->EndInterrupt=id;
 }
}

void gic_trigger(unsigned id)
{
 for(unsigned i=0;i<4;++i)
 {
  DIS[i]->Software=id;
 }
}

void gic_active()
{
 for(unsigned i=0;i<4;++i)
 {
  printf("%d\t",i);
  for(unsigned k=0;k<3;++k) printf("%x ",DIS[i]->Active[k]);
  printf("\n");
 }
}

void gic_info()
{
 printf("i Acknowledge Running     Highest\n");
     /*    0x12345678  0x12345678  0x12345678 */
 for(unsigned i=0;i<4;++i)
 {
         
  printf("%d %x  %x  %x\n",i,IFC[i]->Acknowledge,
                             IFC[i]->Running,
                             IFC[i]->Highest_Pending);
 }
}
