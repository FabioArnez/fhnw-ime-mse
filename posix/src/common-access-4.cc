//---------------------
//common-access-1
//(c) H.Buchmann FHNW 2015
//---------------------
#include <thread>
#include <iostream>
#include <atomic>
/*------------------------------- objectives
 - common access 
   mutex
   now nearly sequentially
   atomic
*/


class Pool
{
 public:
  Pool():data(0){}
  void inc();
  void dec();
  int value() const{return data;}
 private:
  std::atomic<int> data;
};

void Pool::inc()
{
 ++data;           
}

void Pool::dec()
{
 --data;
}


class Agent
{
 public:
  void join();
  
 protected:
  Agent(Pool& pool)
  :pool(pool)
  ,th(&Agent::run,this){}
  Pool& pool;
  
  virtual void action()=0;

 private:
  std::thread th;
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

void Agent::join()
{
 th.join();
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

 incrementer.join();
 decrementer.join(); 

 
 std::cout<<"value="<<pool.value()<<"\n";
}
