#pragma once
/*-----------------------------------
  gic generic interrupt controller
  (c) H.Buchmann FHNW 2012
  $Id$
  [1] literature/realview_emulation_basebord_ug.pdf
-------------------------------------*/

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

extern volatile GIC_IFC*const IFC[];
extern volatile GIC_DIS*const DIS[];

extern void gic_init();
extern void gic_trigger(unsigned id); 
extern void gic_active(); 
extern void gic_info();
