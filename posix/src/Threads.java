//--------------------------
//Threads
//(c) H.Buchmann FHNW 2012
//$Id$
//--------------------------
import java.util.Date;
class Threads //dont confuse with java.lang.Thread
{
 static final long COUNT =(1<<27);
 static final int  RUN   =32;
 
 PoC poc[];
  
 class PoC implements Runnable //the peace of code
 {
  private Date   t0=new Date();
          Thread th=new Thread(this); 
  private int    id;
  private long   count=0;
  private int    run=0;
          long[] time=new long[RUN];
   
  PoC(int id) throws Exception
  {
   this.id=id;
   poc[id]=this;
   th.start();
  }
  
  public void run() // the implementation of Runnable
  {
   while(true)  //simply run
   {
    ++count;
    if (count==COUNT) 
       {
        count=0;
        Date t1=new Date();
	time[run++]=t1.getTime()-t0.getTime();
	t0=t1;
	if (run==RUN) break; // terminates thread 
       }
   }
  }
  
  void join() throws Exception
  {
   th.join();
  }

 }
 
 private Threads(int pocN) throws Exception
 {
  poc=new PoC[pocN];
  for(int i=0;i<pocN;++i)
  {
   new PoC(i); //first PoC
  }
  for(PoC p:poc)p.join();
  
  for(int i=0;i<RUN;++i)
  {
   System.out.print(i);
   for(PoC p:poc) System.out.print("\t"+p.time[i]);
   System.out.println();
  }
 }
 
 public static void main(String args[]) throws Exception
 {
  if (args.lenght!=1)
     {
      System.err.println("usage Threads numberOfThreads");
      System.exit(1);
     }
  new Threads(Integer.parseInt(args[0]));
 }
}
