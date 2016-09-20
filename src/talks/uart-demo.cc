//------------------------
//uart-demo
//(c) H.Buchmann FHWN 2016
//------------------------
IMPLEMENTATION(app,$Id$)
#include "sys/msg.h"
#include "uart-poll.h"
/*
 Arduino Pins:
  0: RX
  1: TX
 Cable Pins https://www.adafruit.com/product/70
  1: BLACK   GND
  2: BROWN   CTS
  3: RED     3.3 V
  4: ORANGE  TXD
  5: YELLOW  RXD
  6: GREEN   RTS
*/
class App
{
 static App app;
 static const UART::Config Config;
 UART uart;
 App();
};

App App::app;
const UART::Config App::Config={
    sys::SOC::SERCOM::COM0,
    //PAD                    PIN                  FUNC
    {sys::reg::SER::PAD::P3,{sys::reg::PORT::PA11,sys::reg::PORT::F_C}},//RX
    {sys::reg::SER::PAD::P2,{sys::reg::PORT::PA10,sys::reg::PORT::F_C}} //TX
                               };
App::App()
:uart(Config)
{
 sys::msg<<"UART Demo\n";
 while(true)
 {
//simple echo
  uart.out(uart.in());
 }
}
