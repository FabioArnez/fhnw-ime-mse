//---------------------------
//thread-demo-2
//(c) H.Buchmann FHNW 2015
// make it with
//    g++ -std=c++11 -llpthread ../src/thread-demo-1.cc -o thread-demo-1
//---------------------------
#include <iostream>
#include <thread>
/*------------------------------- objectives
 - using templates
 - the operator ()
 - thread an instance of a class 
*/

class ThreadClass
{
 public:
  ThreadClass(const char*const id);
  void operator()();     //the threads code
 private:
  const char*const id;
};

ThreadClass::ThreadClass(const char*const id)
:id(id)
{
}

void ThreadClass::operator()()
{
 while(true)
 {
  std::cerr<<id<<"\n";
 }
}

int main(int argc,char** args)
{
 ThreadClass tc1("tc1"); //instance of ThreadClass
 ThreadClass tc2("tc2"); //instance of ThreadClass
 
 std::thread th1(tc1);
 std::thread th2(tc2);
//TODO check cpu usage (sysmonitor)
 th1.join(); //wait here until t1 perhaps finishes
 th2.join(); //wait here until t1 perhaps finishes
 return 0;
}
