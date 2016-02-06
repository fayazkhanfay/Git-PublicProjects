//Programmer: Fayaz Khan
//Assignment: Lab 4 
//Date:       September 22, 2015
//Description:Write a method to give a visual representation of a Dice and have 
//			  test driver for the method 

import javax.swing.*; 
import java.awt.*;

public class Lab4 extends JApplet 
{
	
	@Override
	public void init()                            
    {
		setLayout(new FlowLayout()); 	
    }
	
	@Override
	public void paint(Graphics g)								 //Display results
	{
	
		super.paint(g);
		
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, 600, 600);								 //Display white background
		
		Dice(g,0,0,100, Color.CYAN,"1");	
		Dice(g,100,100,100, Color.RED,"2");
		Dice(g,200,200,100, Color.GREEN,"3");
		Dice(g,300,300,100, Color.BLUE,"4");
		Dice(g,400,400,100, Color.MAGENTA,"5");
		Dice(g,500,500,100, Color.PINK,"6");
		
	}
	
	public void Dice(Graphics g,int xRec,int yRec,int length,Color cName,String numb)
	//	PRE:	g is initialized 
	//			cName is initialized
	//		  	xRec > 0
	//			yRec > 0, and yRec is in pixels.  
	//			0 < numb < 7
	//	POST: 	A square is displayed at specified location(xRex,yRec) of size length and a 
	//			numb is also displayed with a specified color within this displayed box 
	//			symbolizing a dice. Behind the dice their is also a white background 
	{

		Font font = new Font("Serif",Font.BOLD,length);			 //Font for number 
		
		g.setFont(font);										 //Sets style of font for char
		g.setColor(cName);										 //Sets color of font for char
		
		g.drawRect(xRec,yRec,length,length);					 //Display rec at location of length
		
		g.drawString(numb,xRec+(length/4),yRec+((length*3)/4));	 //Variable size font for in square
		
	}
}


