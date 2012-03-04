/*-----------------------------------
  gic generic interrupt controller
  (c) H.Buchmann FHNW 2012
  $Id$
  [1] literature/realview_emulation_basebord_ug.pdf
-------------------------------------*/
#include "sys/gic.h"
#include "stdio.h"

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

void gic_init()
{
 for(unsigned i=0;i<4;++i)
 {
  IFC[i]->CPUControl=1;
  DIS[i]->Control=1;
  for(unsigned k=0;k< 3;++k) DIS[i]->Enable[k]=0xffffffff;
  for(unsigned k=0;k<24;++k) DIS[i]->CPUTargets[k]=1;
 }
 for(unsigned i=0;i<4;++i)
 {
  printf("%d\t%x\t%p\n",i,DIS[i]->ControllerType,&(DIS[i]->Software));
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
