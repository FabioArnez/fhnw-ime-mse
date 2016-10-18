//-------------------------
//tc timer/counter driver event driven
//(c) H.Buchmann FHNW 2016
//TC6/TC7 not yet working
//-------------------------
IMPLEMENTATION(tc,$Id$)
#include "tc.h"
#include "sys/soc.h"

volatile sys::reg::TC*const TC::Regs[]={&sys::reg::TC3,&sys::reg::TC4,&sys::reg::TC5};//,&sys::reg::TC6,&sys::reg::TC7};
               
TC TC::tc[]={TC::TC3,TC::TC4,TC::TC5}; //,TC::TC6,TC::TC7};

TC::TC(ID id)
:tick(*this,"TC")
{
}

void TC::start(ID id,
	       const Config& config,
	       sys::reg::GCLK::GEN gclk,
	       Listener& li)
{
 static const sys::reg::GCLK::DEVICE Clock[]={sys::reg::GCLK::TC3,sys::reg::GCLK::TC4,
                                           sys::reg::GCLK::TC5};
					   //,sys::reg::GCLK::TC6,sys::reg::GCLK::TC7};
 static const sys::SOC::PID Pid[]={sys::SOC::TC3,sys::SOC::TC4,sys::SOC::TC5};
//                                   sys::SOC::TC6,sys::SOC::TC7};
 sys::SOC::clkOn(Pid[id]);
 sys::SOC::arm(Pid[id]);
 sys::reg::GCLK.gen2dev(gclk,Clock[id]);
 tc[id].li=&li;
 tc[id].intset=config.INTENSET;
 volatile sys::reg::TC& r=*Regs[id];
 r.reset();
 r.CTRLA=config.CTRLA;
 r.CTRLBCLR=config.CTRLBCLR;
 r.CTRLBSET=config.CTRLBSET;
 r.CTRLC=config.CTRLC;
 r.EVCTRL=config.EVCTRL;
 r.INTENCLR=config.INTENCLR;
 r.INTENSET=config.INTENSET;
 r.COUNT16=config.COUNT16;
 r.CC16[0]=config.CC16[0];
 r.CC16[1]=config.CC16[1];
 r.enable();
}


void TC::onEvent(sys::Event&)
{
 if (li==0) return;
 unsigned r=intset&intflag;
 if (r&(1<<0)) li->onOverflow();
 if (r&(1<<4)) li->onMC0();
 if (r&(1<<5)) li->onMC1();
}
