//----------------------
//latency
//(c) H.Buchmann FHNW 2015
//----------------------
IMPLEMENTATION(latency,$Id$)
#include "sys/msg.h"
#include "sys/reg/scs.h" //system control space
#include "sys/soc.h"
class Latency
{
 static Latency latency;
 static void onSysTick();
 static const unsigned RVR=(1<<24)-1;
 Latency();
};

Latency Latency::latency;


Latency::Latency()
{
 while(true)
 {
 }
}
