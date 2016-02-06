//Programmer: Fayaz Khan
//Assignment: Lab 2
//Date:       September 7, 2015
//Description: Create an applet with two panels. One panel has a two radio buttons that are 
//logically linked and also a text box. Second panel will have a label,combo box, check box
//and a button

import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.event.*;//used for ActionListner 
import javax.swing.*; 


public class Lab02 extends JApplet
{
	
	private static final String[] LOCATION = {"","Random", "Top"};	// Used for ComboBox
	private JPanel   firstPanel; 			//consist of 2 Radio buttons linked and a text box
	private JRadioButton drawSquare;		//1 of 2 R button labeled Draw square
	private JRadioButton writeMessage;		//2 of 2 R button labeled Write message
	private JTextField textMessage;			//Text box next to write message R button
	private JPanel   secondPanel; 			//consist of Label, ComboBox, CheckBox and button
	private JLabel whereDraw;				//"Select where to draw: "
	private JComboBox locationMenu;			// String[] LOCATION will be used for this 
	private JCheckBox drawColor;			//Check box for "Draw in color"
	private JButton drawButton;				//button for "Draw it!"
	
	
	
	
    @Override
    public void init()                            
    {
        setLayout(new FlowLayout()); 
       
        ButtonGroup radioLink;                         			// group to link radio buttons
        drawSquare = new JRadioButton("Draw square", false);    // create radio buttons
        writeMessage = new JRadioButton("Write message", false);

        add(drawSquare);                                 		// add them to GUI
        add(writeMessage);

        radioLink = new ButtonGroup();                 			// logically link buttons
        radioLink.add(drawSquare);
        radioLink.add(writeMessage);

        textMessage = new JTextField(18);
        add(textMessage);
        
        firstPanel = new JPanel();                      		// create panel
        firstPanel.add(drawSquare);
        firstPanel.add(writeMessage);
        firstPanel.add(textMessage);
        add(firstPanel);
        
        whereDraw = new JLabel("Select where to draw: ");
        add(whereDraw); 
        
        locationMenu = new JComboBox(LOCATION);
        locationMenu.setMaximumRowCount(4);
        add(locationMenu);
        
        drawColor = new JCheckBox("Draw in color");
        add (drawColor);
       
        drawButton = new JButton("Draw It!"); 
        add(drawButton);
        
        secondPanel=  new JPanel();
        secondPanel.add(whereDraw);
        secondPanel.add(locationMenu);
        secondPanel.add(drawColor);
        secondPanel.add(drawButton);
        add(secondPanel);
        
    }

}
