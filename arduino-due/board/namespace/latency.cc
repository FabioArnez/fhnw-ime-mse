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

void Latency::onSysTick()
{
 static const unsigned IDX=10;
 static unsigned cnt[IDX];
 static unsigned idx=0;
 cnt[idx++]=sys::reg::SCS.SYSTICK.CVR;
 if (idx==IDX)
    {
     for(unsigned i=0;i<IDX;++i)
     {
      sys::msg<<(RVR-cnt[i])<<"\n";
     }
     while(true)
     {
     }
    }
}

Latency::Latency()
{
 sys::msg<<"Latency\n";
 sys::SOC::install(sys::SOC::SYS_TICK,onSysTick);
 sys::reg::SCS.SYSTICK.RVR=RVR;
 sys::reg::SCS.SYSTICK.CSR=(1<<0) | //enable
                            (1<<1) | //interrupt
			    (1<<2) |
			         0;  //processor clock

 while(true)
 {
 }
}
