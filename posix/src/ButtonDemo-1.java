//---------------------
//ButtonDemo
//(c) H.Buchmann FHNW 2015
//the classical OO call-back
//---------------------
/*--------------------------- objectives
 setting up the framework
 TODO: implement proper closing not only via ^C
*/
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.ImageIcon;
import java.awt.Container;
import java.awt.FlowLayout;
class ButtonDemo
{
 private ButtonDemo()
 {
  JFrame frame=new JFrame("ButtonDemo");
  frame.getContentPane().setLayout(new FlowLayout());
  JButton button1=new JButton(new ImageIcon("../src/button-1.jpg"));
  JButton button2=new JButton(new ImageIcon("../src/button-2.jpg"));
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
