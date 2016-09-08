//--------------------
//hello-world.
//(c) H.Buchmann FHNW 2016
//--------------------
#include <iostream>

class HelloWorld
{
 public:
   HelloWorld();
  ~HelloWorld();
};

HelloWorld::HelloWorld()
{
 std::cout<<"Hello ";
}

HelloWorld::~HelloWorld()
{
 std::cout<<"World\n";
}

int main(int argc,char** args)
{
 HelloWorld hello; 
 return 0;
}
