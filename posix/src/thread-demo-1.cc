//---------------------------
//thread-demo-1 
//(c) H.Buchmann FHNW 2015
// make it with
//    g++ -std=c++11 -llpthread ../src/thread-demo-1.cc -o thread-demo-1
//---------------------------
#include <iostream>
#include <thread>
/*------------------------------- objectives
 - using templates
 - the threads code is a (simple) function
*/
static void code1()
{
 std::cerr<<"code1\n";
 while(true)
 {
 }
}

static void code2()
{
 std::cerr<<"code2\n";
 while(true)
 {
 }
}


int main(int argc,char** args)
{
 std::thread th1(code1);
 std::thread th2(code2);
//TODO check cpu usage (sysmonitor)
//     make a lot of threads with the same code
 th1.join(); //wait here until t1 perhaps finishes
 th2.join(); //wait here until t1 perhaps finishes
 return 0;
}
