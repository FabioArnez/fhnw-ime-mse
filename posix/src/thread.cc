//---------------------
//thread java like 
//(c) H.Buchmann FHNW 2015
//---------------------
#include "thread.h"

Thread::Thread(Runnable& run)
:run(run)
{
}

Thread::~Thread()
{
 if (th) delete th;
}

void Thread::start()
{
 th=new std::thread(Thread::call,this);
// th=new std::thread(*this); //dont works yet
}

void Thread::join()
{
 if (th) th->join();
}

void Thread::call(Thread* th)
{
 th->run.run();
}
