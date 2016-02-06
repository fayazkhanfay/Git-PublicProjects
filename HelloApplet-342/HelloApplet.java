package lab1;//when using the htm file it would not work if not commented out 
		//but will only work in eclispe if un commented 

/*The two imports are necessary to use the applets 
 * 
 * */
import java.awt.Graphics;
import javax.swing.JApplet;
import java.awt.FlowLayout;
import java.awt.event.*;
import javax.swing.*;


public class HelloApplet extends JApplet // extends to JApplet class which created by java 
{
	/*@Override
    public void init()                            
    {
        setLayout(new FlowLayout()); 
     
        // Code to set up the GUI
    }*/

	
	
	@Override //checks JApplet to match and  prevents stupid mistakes 
	public void paint (Graphics g)//paint & Graphics is defined in JApplet 
	{
		super.paint(g);// since paint is from JApplet we send it back into the default paint	
						//to clear everything out. This should be done when using an @Override
						//because that implies it is coming from some where else 
		g.drawString("Hello, Applet World!",20,20);//("message",x-width,y-height)
		
	}
	
	

}
	
