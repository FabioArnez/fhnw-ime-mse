#pragma once
//----------------------
//cpu-demo using templates
//(c) H.Buchmann FHNW 2016
//----------------------
class Ops
{
 protected:
  static unsigned op(unsigned x,unsigned y); //an operation
  static void copy(unsigned*const dst,const unsigned src);
	//*dst=src
  static void swap(unsigned*const x,unsigned*const y);
	//v=*y
	//*y=*x
	//*x=v
//-------------------- made with C++ references
  static void copy(unsigned& dst,unsigned src);
	//dst=src
  static void swap(unsigned& x,unsigned& y);
	//v=y
	//y=x
	//x=v
};

template<typename OUT>
class OpsTest:Ops
{
 public:
  OpsTest(OUT& out)
  {
   out<<"CPU-Ops\n";
   unsigned x=1;
   unsigned y=2;
   out<<"x="<<x<<" y="<<y<<"\n";
   out<<"op("<<x<<","<<y<<")="<<op(x,y)<<"\n";
   out<<"swap not yet done\n";
//   swap(&x,&y);
//   out<<"x="<<x<<" y="<<y<<"\n";
   out<<"copy "<<x<<"\n";
   copy(&y,x);
   out<<"x="<<x<<" y="<<y<<"\n";
  }
};
