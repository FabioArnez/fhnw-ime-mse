//----------------------
//mpu-demo-2
//(c) H.Buchmann FHNW 2015
// [1] AT91SAM ARM-based Flash MCU
// [2] ARMv7-M Architecture Reference Manual
//----------------------
IMPLEMENTATION(mpu_demo_1,$Id$)
#include "sys/msg.h"
#include "sys/reg/scs.h" //system control space
#include "sys/soc.h"

/*--------------------------------------  objective
 the MPU Registers
  the cortex control register
  the basic understanding
*/

/*-------------------------------------- your notes

*/

class Demo
{
 static Demo demo;
 Demo();
 static unsigned region[256] alignas(1024); //our test region
};

unsigned Demo::region[256];

Demo Demo::demo;

//the macro
#define REG(name) \
sys::msg<<io::ascii::hex()<<name<<"("<<\
(void*)&name<<") "<<#name<<"\n"

Demo::Demo()
{
 sys::msg<<"\n"<<__FILE__<<"\n";
 sys::msg<<(void*)region<<"\n"; //check for proper align
 sys::msg<<"control="<<io::ascii::hex()<<sys::SOC::control()<<"\n";
 region[0]=1; 
//[1] B3.5 
 sys::reg::SCS.MPU.RNR=1;                 //select region
 sys::reg::SCS.MPU.RBAR=(unsigned)region; //set address
 sys::reg::SCS.MPU.RASR= ( 1<< 0) |       //enable
                         (10<< 1) |       //exp size
                          (7<<24);        //read only
 sys::reg::SCS.MPU.CTRL=(1<<0) | //enable
                        (1<<2) | //PRIVDEFENA
			    0; 

 sys::msg<<"read\n";
 sys::msg<<"region[0]="<<region[0]<<"\n";
 sys::msg<<"write\n";

 region[0]=2;
 sys::msg<<"done\n"; 
}
