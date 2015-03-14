//--------------------------
//coroutine test
//(c) H.Buchmann FHNW 2015
//--------------------------
#include "co/coroutine.h"
#include "sys/msg.h"

void co_init(Run run,co_Status* s)
{
 for(unsigned i=0;i<13;++i) s->reg0_12[i]=i;
 s->lr=run;
}

void co_show(const char msg[],co_Status* s)
{
 sys::msg<<msg<<"\n lr="<<(void*)(s->lr)<<"\n";
}

#if 0
void co_transfer(co_Status** from,co_Status* to)
{
}
#endif
