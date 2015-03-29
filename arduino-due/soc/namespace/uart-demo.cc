//-----------------------
//uart-demo and test
//(c) H.Buchmann FHNW 2015
//-----------------------
IMPLEMENTATION(uart_demo,$Id$)
#include "sys/uart.h"
#include "sys/msg.h"
#include "sys/event.h"
#include "sys/deb/deb.h"
class Demo:sys::UART::RX::Listener
          ,sys::UART::TX::Listener
{
 static Demo demo;
 static const char Msg[];
 Demo();
 void onRX(char ch);
 void onTX(const char msg[],unsigned len);
};

const char Demo::Msg[]="0123456789";

Demo Demo::demo;

void Demo::onRX(char ch)
{
 sys::msg<<"char "<<ch<<"\n";
}

void Demo::onTX(const char msg[],unsigned len)
{
 sys::UART::TX::tx(msg,*this);
// sys::deb::signal0();
}

Demo::Demo()
{
 sys::msg<<"UART Demo\n";
// sys::UART::RX::listen(*this);
 sys::UART::TX::tx(Msg,*this);
 sys::Event::loop(); 
}

