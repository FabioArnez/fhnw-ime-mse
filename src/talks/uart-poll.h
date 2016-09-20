#pragma once
//---------------------
//uart-poll 
//(c) H.Buchmann FHNW 2016
//---------------------
#include "sys/reg/sercom.h"
INTERFACE(sys_uart_poll,$Id$)
#include "sys/soc.h"
class UART
{
 public:
  struct Config
  {
   sys::SOC::SERCOM::ID id;
   sys::reg::SER::PAD   rx;
   sys::reg::SER::PAD   tx;
  };

  UART(const Config&);

  void out(unsigned char);
  void out(char ch){out((unsigned char)ch);}

  unsigned char in();
  bool avail();

 private:
  volatile typename sys::reg::SER::USART& usart; 
};
