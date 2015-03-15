//--------------------------
//ButtonListener
//(c) H.Buchmann FHNW 2015
//--------------------------

/*--------------------------- objectives
 -the Listener
   as a separate class 
*/
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

class ButtonListener implements ActionListener
{
 private final String id;
 ButtonListener(String id)
 {
  this.id=id;
 }
 
 public void actionPerformed(ActionEvent e)
 {
//TODO show e 
  System.err.println("actionPerfomed "+id);
 }
}
