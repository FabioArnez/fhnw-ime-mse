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
 VectorTable set VTOR
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
 static void tickInit();
 alignas(1<<7) static  Trap  vectorTable[46]; //see [1] 12-3/12.21.5
};

alignas(1<<7) Trap Demo::vectorTable[46];

void Demo::tickInit() //see [2] Table B3-30
{
 TICK.RVR=(1<<24)-1; //the maximal count
 TICK.CSR=(1<<2)| //CLKSOURCE SysTick
          (1<<0); //enable
}

Demo Demo::demo;

Demo::Demo()
{
 sys::msg<<"interrupt-demo\n"
         <<"vectorTable= "<<(void*)vectorTable<<"\n" //show address of vectorTable
	 <<"VTOR before= "<<(void*)VTOR<<"\n";
 VTOR=vectorTable;
 sys::msg<<"VTOR after= "<<(void*)VTOR<<"\n";	 
}
