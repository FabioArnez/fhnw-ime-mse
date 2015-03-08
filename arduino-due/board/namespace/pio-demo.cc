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
#include "sys/deb/deb.h"
class Demo
{
 static Demo demo;
 static const unsigned INPUT=(1<<25); //Due Pin2 see [2] PIOB
 static void onPin();
 Demo();
};

Demo Demo::demo;

void Demo::onPin()
{
 sys::msg<<"pin "<<io::ascii::hex()<<sys::SOC::PIO_B.ISR<<"\n"; //clears interrupt
}

Demo::Demo()
{
 sys::msg<<"PIO-Demo\n";
 sys::SOC::clockEnable(sys::SOC::PIOB);
 sys::SOC::PIO_B.set(sys::reg::PIO::IN,INPUT);
 sys::SOC::install(sys::SOC::PIOB,onPin);
 sys::SOC::arm(sys::SOC::PIOB); 
 sys::SOC::PIO_B.IER=INPUT;
 
 while(true)
 {
  sys::deb::out(sys::deb::get());
 }
}
