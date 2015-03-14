//------------------------
//co-demo
//(c) H.Buchmann FHNW 2015
//------------------------
#include "sys/msg.h"
#include "co/coroutine.h"
#include "sys/deb/deb.h"

class Demo
{
 static Demo demo;
 Demo();
};


Demo Demo::demo;

static const unsigned WS=0x400;
unsigned char ws1[WS];
unsigned char ws2[WS];
unsigned char ws3[WS];
co_Status* s0=0;
co_Status* s1=(co_Status*)(ws1+WS-sizeof(co_Status));
co_Status* s2=(co_Status*)(ws2+WS-sizeof(co_Status));
co_Status* s3=(co_Status*)(ws3+WS-sizeof(co_Status));

void run1()
{
 while(true)
 {
  sys::msg<<"run1\n";
//  sys::deb::signal0();  
  co_transfer(&s1,s2);
 }
}

void run2()
{
 while(true)
 {
  sys::msg<<"run2\n";
  co_transfer(&s2,s3);
 }
}

void run3()
{
 while(true)
 {
  sys::msg<<"run3\n";
  co_transfer(&s3,s1);
 }
}


Demo::Demo()
{
 sys::msg<<"Co-Demo\n";
 co_init(run1,s1);
 co_init(run2,s2);
 co_init(run3,s3);
 sys::msg<<"ws1="<<(void*)ws1<<" ws2="<<(void*)ws1<<"\n";
 sys::msg<<"s0="<<(void*)s0<<" "<<" s1="<<(void*)s1<<" s2="<<(void*)s2<<"\n";
 co_show("s1",s1);
 co_show("s2",s2);
 co_transfer(&s0,s1);
 sys::msg<<"s0="<<(void*)s0<<"\n";
 sys::msg<<"done\n";
}
