//Programmer: Fayaz Khan
//Assignment: Lab 1
//Date:       September 3, 2015
//Description: Prompts the programmer name, ask the user to enter a message and also 
//enter a valid size for the rectangle. Displays message + Programmer's name and rectangle

import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.event.*;//used for ActionListner 
import javax.swing.*; 

/*SETTING THE WINDOW FOR THE APPLET
 * You put the htm file in the same src folder next Lab01.java
 * but you have to get a class file of Lab01.java
 * in order to do this you use the terminal and type in 
 * javac Lab01.java
 * This will give you a class file 
 * but then you must go into the htm file and specify the file
 * typing Lab01.class and in here you can specify the applet window 
 * then to compile you type into terminal 
 * appletviewer lab01.html 
 * */



public class Lab01 extends JApplet
{

	/*
	 * You'll let the user specify the size of the rectangle and what text to display.
	 * Prompt the user, in two separate dialogs, to enter a message and to enter theWidthoftheborder
	 *If the user chooses a width that is not valid,keep prompting until you get an acceptableWidth
	 * */
	
	private String MyName;						// Hard coded "Fayaz Khan" 
	private String message;						//User enters a message
	private String InputBorder;					//User enters a string for the border of rectangle
	private int BorderInt;						//Takes string InputBorder now is an integer
	private int RecHeight;						//height of rectangle for drawRect
	private int RecWidth; 						//width of rectangle for drawRect
	
	@Override
    public void init()                            // Set up GUI, initialize variables
    {
		setLayout(new FlowLayout());			  			
		
		JOptionPane.showMessageDialog(null, "Fayaz Khan");
		MyName = "Fayaz Khan";
		
		message = JOptionPane.showInputDialog("Enter a message:");
		
		do										//To get a valid number for the rectangle
		{
			InputBorder = JOptionPane.showInputDialog("Enter the width of the border"); 
			BorderInt = Integer.parseInt(InputBorder);

		}while(BorderInt < 0|| BorderInt > 150);

		RecHeight = 300 - BorderInt;
		RecWidth = 400 - BorderInt;
    }

	@Override
	public void paint(Graphics g)                        // Display results
	{
		super.paint(g);
		
		int width = 400-(BorderInt*2);					//width of rectangle line 
		int height = 300- (BorderInt*2);				//height of rectangle line
		
		/*g.drawRect( x-coordinate of top left corner , y-coordinate of top left corner , 
        width , height ); 
		 * */
		g.drawRect(BorderInt, BorderInt, width, height);
		 
		//g.drawString( string , start x-coordinate , start y-coordinate );
		g.drawString(message+ " "+"(" + MyName + ")", (BorderInt+3), (BorderInt+15));
		
	}
	
	
}
