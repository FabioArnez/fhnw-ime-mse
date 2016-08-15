//---------------------
//common-access-1
//(c) H.Buchmann FHNW 2015
//---------------------
#include "thread.h"
#include <iostream>
/*------------------------------- objectives
 - common access 
 - introducing the classes
   . Pool 
   . Agent
   .  Incrementer
   .  Decrementer
 - without any protection
 - the role of join
*/

class Pool
{
 public:
  Pool(){}
  void inc();
  void dec();
  int value() const{return data;}
 private:
  int data=0;
};

void Pool::inc()
{
 ++data;
}

void Pool::dec()
{
 --data;
}


class Agent:public Thread
           ,private Thread::Runnable
{
 protected:
  Agent(Pool& pool):Thread((Thread::Runnable&)*this),pool(pool){}
  Pool& pool;
  virtual void action()=0;

 private:
  static const unsigned COUNT=(1<<22);
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
 Incrementer incrementer(pool);
 Decrementer decrementer(pool);
 incrementer.start();
// incrementer.join(); 
 
 decrementer.start();
 decrementer.join(); 
 incrementer.join();
 std::cout<<"value="<<pool.value()<<"\n";
}
