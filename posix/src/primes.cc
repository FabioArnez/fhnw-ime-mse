//----------------------
//primes 
//(c) H.Buchmann FHNW 2015
//----------------------
#include <vector>
#include <iostream>
class Primes
{
 public:
  Primes(unsigned until);  //all primes<=until
  void show();             //the primes

 private:
  std::vector<unsigned> primes;
  bool isPrime(unsigned v); 
};


Primes::Primes(unsigned until)
{
 primes.push_back(2);
 for(unsigned z=3;z<=until;z+=2)
 {
  if (isPrime(z)) primes.push_back(z);
 }
}

bool Primes::isPrime(unsigned z)
{
 for(auto p:primes)
 {
  unsigned q=z/p;
  unsigned r=z%p;
  if (r==0) return false;
  if (q<p) return true;
 }
 return true; //for the compiles
}

void Primes::show()
{
 for(auto p:primes) std::cout<<p<<" ";
 std::cout<<"\n";
}

int main(int argc,char** args)
{
 Primes p(13);
 p.show();
 return 0;
}
