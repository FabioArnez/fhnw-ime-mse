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
  with dummy traps
  setting VTOR
  calling manually via VTOR
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

extern volatile Trap* VTOR; //its a hardwareregister

class Demo
{
 static Demo demo;
 Demo();
 static void tickInit();
 static alignas(1<<8) Trap vectorTable[46]; //see [1] Table 12-3
                                            //        12.21.5
					    //an array of call-backs
 template<unsigned N>  //using a template
 static void onTrap()
 {
  sys::msg<<"Trap# "<<N<<"\n";
 }
 
};

alignas(1<<8) Trap Demo::vectorTable[46]=
{
onTrap<0>,    //not used 
onTrap<1>,
onTrap<2>,
onTrap<3>,
onTrap<4>,
onTrap<5>,
onTrap<6>,
onTrap<7>,
onTrap<8>,
onTrap<9>,
onTrap<10>,
onTrap<11>,
onTrap<12>,
onTrap<13>,
onTrap<14>,
onTrap<15>,

onTrap<16>,  //numbering see [1] Table 11-1.
onTrap<17>,
onTrap<18>,
onTrap<19>,

onTrap<20>,
onTrap<21>,
onTrap<22>,
onTrap<23>,
onTrap<24>,
onTrap<25>,
onTrap<26>,
onTrap<27>,
onTrap<28>,
onTrap<29>,

onTrap<30>,
onTrap<31>,
onTrap<32>,
onTrap<33>,
onTrap<34>,
onTrap<35>,
onTrap<36>,
onTrap<37>,
onTrap<38>,
onTrap<39>,

onTrap<40>,
onTrap<41>,
onTrap<42>,
onTrap<43>,
onTrap<44>,
onTrap<45>
};


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
 sys::msg<<"VTOR before = "<<(void*)VTOR<<"\n";
 VTOR=vectorTable;	  
 sys::msg<<"VTOR  after = "<<(void*)VTOR<<"\n";
//calling traps manually via VTOR
 for(unsigned i=0;i<46;++i)
 {
  //call 
  VTOR[i]();
 } 
}
