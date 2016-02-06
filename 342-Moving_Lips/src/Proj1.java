//Programmer: Fayaz Khan
//Assignment: Project 1 
//Date:       September 17, 2015
//Description:Implement color checkbox for the user to select a color and implement a third 
//			  option for drawing 			  

import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.event.*;
import javax.swing.*; 
import java.awt.Color;
import java.awt.*;

public class Proj1 extends JApplet implements ActionListener , ItemListener
{
	
	private static final String[] LOCATION = {"","Random", "Top-Left"};	// Used for ComboBox
	private JRadioButton drawSquare;	//labeled "Draw square" used in init() & itemStateChanged
	private JRadioButton writeMessage;	//labeled "Write message" used in init()&itemStateChanged
	private JRadioButton drawLips;		//labeled "Draw Lips" used in init()&itemStateChanged
	private JTextField textMessage;		//Text box near write message in init()&itemStateChanged
	private JLabel whereDraw;			//"Select where to draw: "
	private JComboBox locationMenu;		//String[] LOCATION will be used for this 
	private JCheckBox drawColor;		//Check box for "Draw in color"
	private JButton drawButton;			//button for "Draw it!"
	private String message;				//For the message box 
	private boolean bMessage;			//True is display message, false no message being displayed
	private boolean ;				//True if something selected from ComboBox
	private boolean bSquare;			//True if draw square button selected, false other wise 
	private boolean bButton;			//True if draw button pressed, false when completes action 
	private boolean bLips;				//True if draw lips selected,other button selected is false
	private int locSelectIndex;			//To determine which LOCATION is selected 
	private int ranX;					//random x coordinate for square, text and lips 
	private int ranY;					//random y coordinate for square, text and lips 
	private Color colorN = Color.BLACK; //user has option to choose color from Swatches
	
    @Override
    public void init()                            
    {
    	JPanel   firstPanel; 			//3 Radio buttons linked:text box, draw Square and Lips
        JPanel   secondPanel; 			//consist of Label, ComboBox, CheckBox and button
        ButtonGroup radioLink;          // group to link radio buttons
       
        setLayout(new FlowLayout()); 
       
        drawSquare = new JRadioButton("Draw square", false);    // create radio buttons
        writeMessage = new JRadioButton("Write message", false);
        drawLips =  new JRadioButton("Draw Lips", false);
        		
        add(drawSquare);                                 		// add them to GUI
        add(writeMessage);
        add(drawLips);
        
        drawSquare.addItemListener(this);
        writeMessage.addItemListener(this);
        drawLips.addItemListener(this);
        
        radioLink = new ButtonGroup();                 			// logically link buttons
        radioLink.add(drawSquare);
        radioLink.add(writeMessage);
        radioLink.add(drawLips);
        
        
        textMessage = new JTextField(18);
        add(textMessage);
        textMessage.addActionListener(this);					//ActionListenerf for text
        
        firstPanel = new JPanel();                      		// create panel
        firstPanel.add(drawLips);								
        firstPanel.add(drawSquare);
        firstPanel.add(writeMessage);
        firstPanel.add(textMessage);
        
        add(firstPanel);
        
        whereDraw = new JLabel("Select where to draw: "); 
        
        locationMenu = new JComboBox(LOCATION);
        locationMenu.setMaximumRowCount(4);
        locationMenu.addItemListener(this);
        
        drawColor = new JCheckBox("Draw in color");
        drawColor.addItemListener(this);
       
        drawButton = new JButton("Draw It!"); 
        drawButton.addActionListener(this);
        
        secondPanel=  new JPanel();
        secondPanel.add(whereDraw);
        secondPanel.add(locationMenu);
        secondPanel.add(drawColor);
        secondPanel.add(drawButton);
        add(secondPanel);
        
    }
    
    
    @Override
	public void paint(Graphics g)                        		//Display results
	{
    	Dimension appletSize = this.getSize();					//get height and width of applet
    	int appletWidth = appletSize.width;						//gets width of applet
		int appletHeight = appletSize.height;					//gets height of applet
		final int widthBuffer = 100;							//Allows for padding for drawing 
		final int heightBuffer = 60;							//Padding to prevent overlap
		final int heightExBuffer = heightBuffer + 20;			//Extra padding stay in bounds
		final int widthLessBuffer = 75;							//Decrease the buffer for width
		
		super.paint(g);
		
		if(bLips == true &&  == true && bButton == true) //Draw Lips, boxCombo & Draw button 
		{
			
			if(locationMenu.getSelectedIndex()== 1)			   //User Selects random from Combo box
			{
				ranX = (int) (Math.random() *(((appletWidth-widthBuffer)-0)+1)+0);
				ranY = (int) (Math.random() *(((appletHeight-widthBuffer)-(heightExBuffer))+1)
						     + heightExBuffer);
		 
				g.setColor(colorN);
		
				g.fillArc(ranX, ranY,widthBuffer,widthBuffer/3,heightBuffer*3,heightBuffer*3);
				g.fillArc(ranX, ranY, widthBuffer/2,widthBuffer/4,0,widthBuffer*2);
				g.fillArc(ranX+(widthBuffer/2),ranY,widthBuffer/2,widthBuffer/4,-(heightBuffer/3)
						 ,widthBuffer*2);
			}
			
			if(locationMenu.getSelectedIndex()== 2)			   //User selects Top-Left in Combo box
			{
				g.setColor(colorN);
				
				g.fillArc(widthBuffer/10, widthBuffer, widthBuffer,widthBuffer/3,
						  heightBuffer * 3, heightBuffer * 3);
				g.fillArc(widthBuffer/10, widthBuffer,widthBuffer/2,widthBuffer/4,0,
						  widthBuffer*2);
				g.fillArc(heightBuffer,widthBuffer, widthBuffer/2,widthBuffer/4,-(heightBuffer/3)
						 ,widthBuffer*2);
			}
		}
		
		
		if(bMessage== true && bCombo == true && bButton == true)//T message, boxCombo & Draw button
		{
			if(locationMenu.getSelectedIndex()== 1) 		   //User Selects random from Combo box
			{
				ranX = (int) (Math.random() *(((appletWidth-widthBuffer)-0)+1)+0);
				ranY = (int) (Math.random() *(((appletHeight-widthBuffer)-heightExBuffer)+1)
						     +heightExBuffer);
				
				g.setColor(colorN);
				g.drawString(message, ranX, ranY);
			}
			
			if(locationMenu.getSelectedIndex()== 2)			  //User selects Top-Left in Combo box
			{
				g.setColor(colorN);
				g.drawString(message, heightBuffer, widthBuffer);
			}
			
		}
		
		
		if(bSquare== true &&bCombo == true && bButton == true)//Draw Square, boxCombo&Draw button
		{
		
			if(locationMenu.getSelectedIndex()== 1)			  //User Selects random from Combo box
			{
				ranX = (int) (Math.random() *(((appletWidth-widthBuffer)-0)+1)+0);
				ranY = (int) (Math.random() *(((appletHeight-widthBuffer)-heightExBuffer)+1)
						     +heightExBuffer);
		
				g.setColor(colorN);
				g.drawRect(ranX, ranY, widthBuffer, widthBuffer); 
				g.fillRect(ranX, ranY, widthBuffer, widthBuffer);
			}
			
			if(locationMenu.getSelectedIndex()== 2) 		  //User selects Top-Left in Combo box
			{
				g.drawRect(heightBuffer/6, widthLessBuffer, widthBuffer, widthBuffer); 
				g.setColor(colorN);
				g.fillRect(heightBuffer/6, widthLessBuffer, widthBuffer, widthBuffer);
			}
		}
		
		bButton = false;
	}
    
    public void actionPerformed (ActionEvent e)
    {
    	
    	if(e.getSource()== drawButton)						  //User selects draw Button on applet
    	{
    		bButton = true;
    	}
    	
    	if(bMessage== true && bCombo == true)				  //Grabs text if text & boxCombo true
    	{
    		message = textMessage.getText();
    	}
        	
    	repaint();
    }
    
    
    public void itemStateChanged(ItemEvent e)
    {
    	
    	if(e.getSource()== drawColor && e.getStateChange() == ItemEvent.SELECTED) 
    	{													  //Check box is checked, show Swatches 
    		//JOptionPane.showMessageDialog(null,"Color ON");
    		colorN = JColorChooser.showDialog(this, "Prompt message", colorN); 
    	}
    	
    	if(e.getSource()== drawColor && e.getStateChange() == ItemEvent.DESELECTED)
    	{													  //Check box is unchecked
    		//JOptionPane.showMessageDialog(null,"Color OFF");
    		colorN = Color.BLACK;
    	}
    	
    	if(e.getSource() == writeMessage && e.getStateChange()== ItemEvent.SELECTED )
    	{													  //Displays message, set rest to false
    		bMessage = true;
    		bSquare = false;
    		bLips = false;
    	}
    	
    	if(e.getSource() == drawSquare && e.getStateChange()== ItemEvent.SELECTED )
    	{													  //Display Square, set rest to false
    		bMessage = false;
    		bSquare = true;
    		bLips = false;
    	}
    	
    	if(e.getSource() == drawLips && e.getStateChange()== ItemEvent.SELECTED )
    	{													  //Display Lips, set rest to false
    		bMessage = false;
    		bSquare = false;
    		bLips = true;
    	}
    	
    	if(e.getSource() == locationMenu && e.getStateChange()== ItemEvent.SELECTED )
    	{													  //random or topLeft selected in Combo
    		bCombo = true;
    	}
  
    	repaint();
    	
    }
    
}
