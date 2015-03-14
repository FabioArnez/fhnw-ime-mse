#pragma once
//--------------------------
//coroutine test
//(c) H.Buchmann FHNW 2015
//--------------------------

struct co_Status
{
 unsigned reg0_12[13];
 void (*lr)();  
};
extern void co_show(const char msg[],co_Status* s);

typedef void (*Run)();

extern void co_init(Run run,co_Status* s);
extern void co_transfer(co_Status** from,co_Status* to);
