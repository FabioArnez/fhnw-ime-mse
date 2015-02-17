//----------------------------
//interrupt-demo
//(c) H.Buchmann FHNW 2015
// [1] AT91SAM ARM-based Flash MCU SAM3X SAM3A Series
//     at91sam3x.pdf
// [2] ARMv7-M Architecture Reference Manual
//     DDI0403D_arm_architecture_v7m_reference_manual_errata_markup_1_0.pdf
// step by step see git 
// interrupt source:
//  SysTick [2] B3.3
//----------------------------
IMPLEMENTATION(interrupt_demo,$Id$)
#include "sys/deb/deb.h"
#include "sys/msg.h"
/*--------------------------------------  objective
 VectorTable init 
*/  

//our interrupt source:
extern volatile struct {  //see [2] B3.3.2
		 unsigned CSR;
		 unsigned RVR;
		 unsigned CVR;
		 unsigned CALIB;
		} TICK;

typedef void (*Trap)(); //we use it more than once

extern volatile Trap* VTOR;

class Demo
{
 static Demo demo;
 Demo();
 static const unsigned TRAPN=46; //the number of Traps
 static void tickInit();
 static void vectorTableInit();
 static void unexpectedTrap(); //is of type Trap
 alignas(1<<7) static  Trap  vectorTable[TRAPN]; //see [1] 12-3/12.21.5
};

alignas(1<<7) Trap Demo::vectorTable[46];

void Demo::tickInit() //see [2] Table B3-30
{
 TICK.RVR=(1<<24)-1; //the maximal count
 TICK.CSR=(1<<2)| //CLKSOURCE SysTick
          (1<<0); //enable
}

void Demo::vectorTableInit()
{
 for(unsigned i=0;i<TRAPN;++i) vectorTable[i]=unexpectedTrap;
}


void Demo::unexpectedTrap()
{
 sys::msg<<"unexpectedTrap\n";
 while(true){}
}

Demo Demo::demo;

Demo::Demo()
{
 sys::msg<<"interrupt-demo\n"
         <<"vectorTable= "<<(void*)vectorTable<<"\n" //show address of vectorTable
	 <<"VTOR before= "<<(void*)VTOR<<"\n";
 vectorTableInit();     //init
 VTOR=vectorTable;
 for(unsigned i=0;i<TRAPN;++i)
 {
  sys::msg<<(void*)vectorTable[i]<<"\n";
 }
 sys::msg<<"VTOR after= "<<(void*)VTOR<<"\n";	 
}
