//---------------------
//common-access-1
//(c) H.Buchmann FHNW 2015
//---------------------
#include "thread.h"
#include <iostream>
#include <atomic>
/*------------------------------- objectives
 - common access 
   made with Lock
    using constructor/destructor pair
   now nearly sequentially
*/

class Pool
{
 public:
  Pool();
  void inc();
  void dec();
  int value() const{return data;}
 private:
  std::atomic<int> data;
};

Pool::Pool()
:data(0)
{
}
void Pool::inc()
{
 std::atomic_fetch_add(&data,1);
}

void Pool::dec()
{
 std::atomic_fetch_sub(&data,1);
}

class Agent:public Thread
           ,private Thread::Runnable
{
 protected:
  Agent(Pool& pool):Thread((Thread::Runnable&)*this),pool(pool){}
  Pool& pool;
  virtual void action()=0;

 private:
  static const unsigned COUNT=(1<<20);
  void run();
};

void Agent::run()
{
 for(unsigned count=0;count<COUNT;++count)
 {
  action();
 }
}

class Incrementer:public Agent
{
 public:
  Incrementer(Pool& pool):Agent(pool){}
 private:
  void action(){pool.inc();}
};

class Decrementer:public Agent
{
 public:
  Decrementer(Pool& pool):Agent(pool){}
 private:
  void action(){pool.dec();}
};

int main(int argc,char**args)
{
 Pool pool;
 Incrementer inc(pool);
 Decrementer dec(pool);
 inc.start();
 dec.start();
 inc.join();
 dec.join();
 std::cout<<"value="<<pool.value()<<"\n";
}
