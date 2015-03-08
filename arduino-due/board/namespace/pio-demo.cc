//--------------------------
//pio-demo
//(c) H.Buchmann FHNW 2015
// [1] AT91SAM ARM-based Flash MCU SAM3X SAM3A Series
//     at91sam3x.pdf
// see section 32 Parallel Input/Output
// [2] http://arduino.cc/en/Hacking/PinMappingSAM3X
//--------------------------
IMPLEMENTATION(pio_demo,$Id$)
#include "sys/soc.h"
#include "sys/msg.h"

class Demo
{
 static Demo demo;
 static const unsigned INPUT=(1<<25); //Due Pin2 see [2] PIOB
 Demo();
};

Demo Demo::demo;

Demo::Demo()
{
 sys::msg<<"PIO-Demo\n";
 sys::SOC::clockEnable(sys::SOC::PIOB);
 sys::SOC::PIO_B.set(sys::reg::PIO::IN,INPUT);

 unsigned inp=sys::SOC::PIO_B.PDSR&INPUT;
 sys::msg<<io::ascii::hex()<<inp<<"\n";
 while(true)
 {
  unsigned inp1=sys::SOC::PIO_B.PDSR&INPUT;
  if (inp!=inp1)
     {
      inp=inp1;
      sys::msg<<io::ascii::hex()<<inp<<"\n";
     }
 }
}
