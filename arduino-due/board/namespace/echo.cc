//-----------------------
//echo
//(c) H.Buchmann FHNW 2015
//-----------------------
IMPLEMENTATION(echo,$Id$)
#include "sys/deb/deb.h"
class Echo
{
 static Echo echo;
 Echo();
};

Echo Echo::echo;

Echo::Echo()
{
 while(true)
 {
  sys::deb::out(sys::deb::get());
 }
}
