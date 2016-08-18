//----------------------
//mpu-demo-1
//(c) H.Buchmann FHNW 2015
// [1] AT91SAM ARM-based Flash MCU
// [2] ARMv7-M Architecture Reference Manual
//----------------------
IMPLEMENTATION(mpu_demo_1,$Id$)
#include "sys/msg.h"
#include "sys/reg/scs.h" //system control space
/*--------------------------------------  objective
 the MPU Registers
  check for correct locations
  use a macro
*/

/*-------------------------------------- your notes

*/

class Demo
{
 static Demo demo;
 Demo();
};

Demo Demo::demo;

//the macro
#define REG(name) \
sys::msg<<io::ascii::hex()<<name<<"("<<\
(void*)&name<<") "<<#name<<"\n"

Demo::Demo()
{
 sys::msg<<"\n"<<__FILE__<<"\n";
 REG(sys::reg::SCS.MPU.TYPE); //use REG macro
 REG(sys::reg::SCS.MPU.RASR_A3); 
}
