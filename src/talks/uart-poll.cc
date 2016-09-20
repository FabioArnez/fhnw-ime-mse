//---------------------
//uart-poll 
//(c) H.Buchmann FHNW 2016
//TODO make comm parameters baud etc. 
// more flexible
//---------------------
#include "sys/reg/sercom.h"
IMPLEMENTATION(sys_uart_poll,$Id$)
#include "uart-poll.h"
#include "sys/reg/port.h"
#include "sys/reg/gclk.h"
#include "sys/reg/pm.h"
#include "sys/msg.h"

UART::UART(const Config& cfg)
:usart(sys::SOC::SERCOM[cfg.id].com.USART)
{
 sys::SOC::clkOn(sys::SOC::SERCOM[cfg.id].pid);
 sys::reg::GCLK.gen2dev(sys::reg::GCLK::G0,sys::SOC::SERCOM[cfg.id].clk);
 sys::reg::SER::mux(cfg.rx);
 sys::reg::SER::mux(cfg.tx);

 usart.CTRLA|=1; 
 while( (usart.CTRLA&1) || (usart.SYNCBUSY&1))
 {
 }
 usart.BAUD =0x0000ff2d;
 usart.CTRLA=0x40310006;
 usart.CTRLB=0x00030000;
 while(usart.SYNCBUSY&(1<<1)){}
} 

void UART::out(unsigned char ch)
{
 while((usart.INTFLAG & (1<<0))==0)
 {
 }
 usart.DATA=ch;
}

unsigned char UART::in()
{
 while((usart.INTFLAG & (1<<2))==0)
 {
 }
 return usart.DATA;
}

bool UART::avail()
{
 return (usart.INTFLAG & (1<<2))!=0;
}
