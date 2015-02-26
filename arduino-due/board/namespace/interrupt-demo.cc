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
 VectorTable as an array of call-backs
  check proper position
*/  

//our interrupt source:
extern volatile struct {  //see [2] B3.3.2
		 unsigned CSR;
		 unsigned RVR;
		 unsigned CVR;
		 unsigned CALIB;
		} TICK;

typedef void (*Trap)(); //the callback 
                        //called by hardware

class Demo
{
 static Demo demo;
 Demo();
 static void tickInit();
 static alignas(1<<8) Trap vectorTable[46]; //see [1] Table 12-3
                                            //        12.21.5
					    //an array of call-backs
};

alignas(1<<8) Trap Demo::vectorTable[46]; //empty for 

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
         <<(void*)vectorTable<<"\n"; //show address of vectorTable
	  //check alignement|bit 29 see [1] 12.21.5
}
