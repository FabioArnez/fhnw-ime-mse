//---------------------
//ButtonDemo
//(c) H.Buchmann FHNW 2015
//the classical OO call-back
//---------------------
/*--------------------------- objectives
 -the Listener
  main class implements Listener
*/
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.ImageIcon;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

class ButtonDemo implements ActionListener
{
 public void actionPerformed(ActionEvent e)
 {
//TODO show e 
  System.err.println("actionPerfomed "+e.getActionCommand());
 }
 
 private ButtonDemo()
 {
  JFrame frame=new JFrame("ButtonDemo");
  frame.getContentPane().setLayout(new FlowLayout());
  JButton button1=new JButton(new ImageIcon("../src/button-1.jpg"));
  button1.setActionCommand("button1");
  button1.addActionListener(this);
  JButton button2=new JButton(new ImageIcon("../src/button-2.jpg"));
  button2.setActionCommand("button2");
  button2.addActionListener(this);
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
