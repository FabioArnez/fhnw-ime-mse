#pragma once
//---------------------
//thread.h  java like 
//(c) H.Buchmann FHNW 2015
//---------------------
#include <thread>
#include <mutex>
class Thread
{ 
 public:
  struct Runnable         //the (nested) interface
  {
   virtual void run()=0; // pure virtual method
  };
  Thread(Runnable&);
  ~Thread();
  void start();
  void join();
 private:
  std::thread* th=0;
  Runnable&    run; 
  static void call(Thread*);
  void operator()();    //dont work TODO make it work 
};

class Lock
{
 public:
  Lock(std::mutex& m):m(m){m.lock();}
  ~Lock(){m.unlock();}
 private:
  std::mutex& m;
};

