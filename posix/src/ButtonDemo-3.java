//---------------------
//ButtonDemo
//(c) H.Buchmann FHNW 2015
//the classical OO call-back
//---------------------
/*--------------------------- objectives
 -the Listener
  as inner class
  TODO Listener as anonymous class 
*/
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.ImageIcon;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

class ButtonDemo 
{
 class Listener implements ActionListener // inner class
 {
  private final String id;
  Listener(String id)
  {
   this.id=id;
  }

  public void actionPerformed(ActionEvent e)
  {
 //TODO show e 
   System.err.println("actionPerfomed "+id);
  }
 }
 
 private ButtonDemo()
 {
  JFrame frame=new JFrame("ButtonDemo");
  frame.getContentPane().setLayout(new FlowLayout());
  JButton button1=new JButton(new ImageIcon("../src/button-1.jpg"));
  button1.addActionListener(new Listener("button1"));
  JButton button2=new JButton(new ImageIcon("../src/button-2.jpg"));
  button2.addActionListener(new Listener("button2"));
  frame.getContentPane().add(button1);
  frame.getContentPane().add(button2);
  frame.setSize(900,600);
  frame.setVisible(true);
 }
 
 public static void main(String args[])
 {
  new ButtonDemo(); //create instance calls constructor
 }
}
