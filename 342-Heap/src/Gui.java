//
// Programmer:  Joe Kallarackel, Fayaz Khan, Jaydeep Patel, Christian Valladares
// Assignment:  Project 3 - Heap Illustration
// Date:        11/12/2015
// Description: This is the GUI class, and it handles the buttons, and graph printing
//              by referencing the array representation of the heap.  We design a 
//              GUI by using nested panels, and we also implement a message log
//              that contains all the actions performed on the heap from the beginning
//              of the application. We build a resizable heap image by referencing
//              the scaledPoint class.  
//                        
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

import javax.swing.*;

public class Gui extends JApplet implements ActionListener
{

    BorderLayout base;                // base is the base layout for all the GUI
    
    //private JPanel top;               // top is the top panel of the GUI and contains
                                      //    drawings
    private JPanel bottom;            // bottom is the bottom panel of the GUI and 
                                      //    contains controls
    
    private JPanel bottomLeft;        // bottomLeft panel contains the buttons
    private JPanel bottomRight;       // bottomRight panel contains the newsFeed section
    
    
    private JButton insertToHeap;     // insertToHeap will let the user insert 
                                      //    insert to the heap
    private JButton searchValue;      // searchValue button will let the user search
                                      //    a value
    private JButton heapify;          // heapify button will move one frame forward
                                      //    in our minHeap animation
    private JButton unHeapify;        // unHeapify button will move one frame backwards
                                      //    in our minHeap animation
    private JButton fullHeapify;      // fullHeapify button will fast forward to the 
                                      //    last frame in our minHeap animation
    private JButton deleteValue;      // deleteValue button will prompt the user to 
                                      //    delete a value (min or max depending on
                                      //    heap).
    
    private JTextField valueToInsert; // valueToInsert will hold the text value to be inserted
                                      
    private JTextField valueToSearch; // valueToSearch will hold the value to be searched
    
    

    private JTextArea feedContents;   // feedContents holds content for news feed.       
    private JScrollPane feedPane;     // feedPane holds feedContents for news feed.    
    private String feedMessage;       // feedMessage holds message for news feed.        
   
    private MinHeap theMinHeap;       // theMinHeap is a min heap

    private int heapSearchIndex;      // heapSearchIndex will contain 
                                      //    the index of the search
    
    
    private boolean enableDelete;     // Flag that determines whether delete
                                      //    can be enabled or not
    
    private int [][] animateFrames;   // animateFrames contains frames to be animated
                                      //    (by heapifying or unheapifying). 
    private int numFrames;            // numFrames contains number of frames
                                      //    in the heap animation
    private int currFrame;            // currFrame contains current frame of
                                      //    animation
    
    private String theMessage;        // theMessage holds the entire log of actions
    
    
    public void init()
    // POST: Initialize the GUI
    {
    	
    	//displayTutorial();			  // method display's the initial tutorial for program
        setSize(600,400);             // start the program to 600 by 400
                                      
        theMinHeap = new MinHeap();   // Initialize the Heaps.
                                      
    
        heapSearchIndex = -1;
        enableDelete = false;
        
        initializePanels();
        initializeWidgets();
        setUpPanels();
        addAllListeners();
        addToPanels();
        addToGui();
        
        heapify.setEnabled(false);
        unHeapify.setEnabled(false);
        fullHeapify.setEnabled(false);
        deleteValue.setEnabled(false);
        
       // scaler = new ScaledPoint(31);
    }
    
    public void paint(Graphics g)
    {
       
        
        super.paint(g);
        
      
        
        theMessage = theMinHeap.actionsUpTo(currFrame, numFrames);
        feedContents.setText(""); 
       
        if(theMessage.contentEquals("1) null\n"))    // If the message contents are null
                                                     //    Handle it as a base case 
                                                     //    and print instructions 
        {
            feedContents.setText("This box will contain all the steps while \n" +
                                 "traversing through the heap.\n\nIt will update as " +
                                 "you heapify, unheapify, \ninsert, or delete.\n");
        }
        
        else
        {
            feedContents.setText(theMessage); 
        }
        
        checkFramPosition();
    }
    
    public void displayTutorial()
    // POST: Displays a message box giving a quick tutorial of the program
    {
    	JOptionPane.showMessageDialog(null, "Welcome to our program! \n\nWe will be learning about "
    			+ "Min heaps \n\nGet PUMPED!!\n\n To build a tree please type in a integer in the "
    			+ "bottom left corner of the screen and then press Insert to Heap, repeat as "
    			+ "desired\n\nTo search for a value in your newly made tree type an integer and then "
    			+ "press Search value...peak a boo, I see you\n\nYou may notice the Heapify is visible"
    			+ " after inserting a few values.\nWe have to keep our tree balanced after pressing "
    			+ "Heapify it will attempt to balance your tree.\nPending on the value entered you "
    			+ "may have to press a heapify a few times but pay close attention on what is "
    			+ "happening each time\n\nAfter you Heapify, you can also UnHeapify this will "
    			+ "reverse the animation to the previous state, repeat till desired \n\nFull "
    			+ "Heapify does the same thing as Heapify but on steriods this will jump to "
    			+ "balanced tree, OH YEAH!!!\n\nWant to see a lame magic trick press the Delete Root"
    			+ "button and pay special attention to very top node.\n\nEnjoy and Behave yourself"
    			+  ":)");
    }
    
    public void addAllListeners()
    // POST: will add Action Listeners to all widgets expected to perform actions
    {
        insertToHeap.addActionListener(this);
        searchValue.addActionListener(this);
        deleteValue.addActionListener(this);
        heapify.addActionListener(this);
        unHeapify.addActionListener(this);
        fullHeapify.addActionListener(this);      
    }
    
    public void addToGui()
    // POST: Will add all widgets, layouts, and panels to the GUI
    {
        setLayout(base);                      //Will set a borderLayout layout as the base 
                                              //      Layout     
        
        //add(base.CENTER, top);
        add(base.SOUTH, bottom);        
    }
    
    public void addToPanels()
    // POST: Will add all widgets to their respective panels
    {        
                                              
        bottomLeft.add(insertToHeap);        // Insert Bottom Left Widgets
        bottomLeft.add(valueToInsert);
        bottomLeft.add(searchValue);
        bottomLeft.add(valueToSearch);

        bottomLeft.add(unHeapify );
        bottomLeft.add(heapify );
        bottomLeft.add(fullHeapify);
        
        bottomLeft.add(deleteValue);
        
        
        bottomRight.add(feedPane, BorderLayout.CENTER); // Insert the News Feed
        
        
    }
    
    public void setUpPanels()
    // POST: Will initialize the panel Hierarchy to before adding buttons and
    //       elements.   It will also set proportions and Initial Sizes for 
    //       these panels
    {
        
        //top.setMinimumSize(new Dimension(600,400 - 130));// Will set the minimum size
                                                         //   for the TOP panel to 
                                                         //   2/3 the required project t
                                                         //   heighT and a full width

        bottom.setMinimumSize(new Dimension(600,130));   // Will set the minimum size
                                                         //   for the bottom panel to 
                                                         //   1/3 the required project 
                                                         //   height and a full width
        
        
        
        bottom.add(bottomLeft);
        bottom.add(bottomRight);       
    }
    
    public void initializeWidgets()                                         
    // POST: Will initialize all the widgets in the applet                  
    {         
        
                                                               
        insertToHeap = new JButton("Insert To Heap");    // Left Side  
        searchValue = new JButton ("Search Value");
        deleteValue = new JButton("Delete Root");
        heapify = new JButton("Heapify"); 
        unHeapify = new JButton("UnHeapify");  
        fullHeapify = new JButton("Full Heapify"); 
                
        
        valueToInsert = new JTextField (); 
        valueToSearch = new JTextField (); 
        
        
        feedContents = new JTextArea(5,20);              // Right Side                    
        feedContents.setEditable(false);                    
        feedContents.setText(" ");                          
        
        feedPane = new JScrollPane(feedContents);
    }                                                                       
    
    public void initializePanels()                        
    //POST:  Will initialize all Panels and Layouts      
    {             
        base = new BorderLayout();        
                                        
        //top = new JPanel();                              // Set up all panels    
        bottom = new JPanel();                             
        bottomRight  = new JPanel();                              
        bottomLeft = new JPanel();   
        
        //top.setLayout(new FlowLayout());				 // Set the layout for all panels
        bottom.setLayout(new GridLayout(1,2));
        bottomLeft.setLayout(new GridLayout(4,2));
        bottomRight.setLayout(new BorderLayout()); 
        bottomLeft.setMinimumSize(new Dimension(600,130));
    }                                                     
    
   
    
    public void disableAll()
    // POST:  Enables all buttons 
    {
        insertToHeap.setEnabled(false);
        searchValue.setEnabled(false);
        deleteValue.setEnabled(false);                
    }
    
    public void enableAll()
    // POST:  Enable all buttons except for animation buttons
    {
        insertToHeap.setEnabled(true);
        searchValue.setEnabled(true);
        
        if(enableDelete == true)            		//If enableDelete flag is set to true
            deleteValue.setEnabled(true);   		//   enable the deleteValue button             
    }
    
    public void checkFramPosition()
    // POST: Disable or disables buttons based on whether the current animation
    //       frame is the last frame or not
    {
        
        if (numFrames == 0 || numFrames == 1) 		// If there are no frames (base case)
        {
            enableAll();                 			// enable all the buttons 
            heapify.setEnabled(false); 		    	// disable the forward button
            fullHeapify.setEnabled(false); 			// disable the fast forward button
            unHeapify.setEnabled(false);  			// enable all the move back button
        }
        
        else if(currFrame == (numFrames - 1) )   	// If the current frame is at last frame
        {
            enableAll();                 			// enable all buttons
            heapify.setEnabled(false);  			// disable the forward button
            fullHeapify.setEnabled(false); 			// disable the fast forward button
            unHeapify.setEnabled(true);   			// enable all the move back button
        }
        

        else if( currFrame == 0)                    // If the current frame is the first
        {
            disableAll();
            unHeapify.setEnabled(false); 
            heapify.setEnabled(true);  
            fullHeapify.setEnabled(true); 
        }
        
        else                             			// If the current frame is not at last
                                         			//   frame
        {
            disableAll();
            heapify.setEnabled(true);  				// disable the forward button
            fullHeapify.setEnabled(true); 			// disable the fast forward button
            unHeapify.setEnabled(true);  			// enable all the move back button
        }
    }
    
    @Override
    public void actionPerformed(ActionEvent e) 
    // POST: Handles all actions performed on the GUI
    {
        int targetValue;                        // target value holds the value 
                                                //    to be searched or inserted         
        checkFramPosition();
        
        if (e.getSource() == insertToHeap)      //if the event to be handled is the insert
                                                //    button
        {
            try                                 // Try to insert a value as long 
                                                //    as the user inputs a number
            {
                targetValue = Integer.parseInt(valueToInsert.getText());
                theMinHeap.addValue(targetValue);
                enableDelete = true;            // Whenever we add a value, enable
                                                //     the delete button
                
                currFrame = 0;                  // Reset the current frame
            }
            
            catch(Exception ex)                 // On failure, prompt the user to 
                                                //     type in a value
            {
                JOptionPane.showMessageDialog(null, "Please enter a value to Insert.");                
            }

           
        }
        
        if (e.getSource() == searchValue)       //if the event to be handled is the search
                                                //    button
        {
            try                                 // Try to insert a value as long 
                                                //    as the user inputs a number
            {
                targetValue = Integer.parseInt(valueToSearch.getText());
                
                heapSearchIndex = theMinHeap.search(targetValue);
                
                if(heapSearchIndex != -1)       // If the heapsearch does not return -1
                { 
                    //searchSucceeded = true;     // Then the search succeeded.  Set the flag 
                }
                
                else
                {
                    JOptionPane.showMessageDialog(null, "Value Not Found."); 
                }
                
                currFrame = 0;                  // Reset the current frame
            }
            
            catch(Exception ex)                 // On failure, prompt the user to 
                                                //    type in a value
            {
                JOptionPane.showMessageDialog(null, "Please enter a value to search.");  
            }
        }
        
        if (e.getSource() == deleteValue)       //if the event to be handled is the delete
                                                //    button
        {
            
            theMinHeap.removeRoot();
            currFrame = 0;                              // Reset the current frame
            
            numFrames = theMinHeap.getStateIndex();
            
            if (animateFrames[numFrames-1].length == 0) // If there are no nodes to 
            {
                enableDelete = false;                   // Do not allow delete to be enables
                deleteValue.setEnabled(false);          // Disable delete
            }
            
        }
        
        if (e.getSource() == heapify)                   // if the event to be handled 
                                                        //    is the heapify button
        {
            currFrame++;
            checkFramPosition();
        }
        
        if (e.getSource() == unHeapify)                 // if the event to be handled 
                                                        //    is the unHeapify button
        {
            currFrame--;                                // decrement.
            
            if (currFrame == -1)                        // If the current frame is not at the first frame.
                currFrame = 0;
            
            checkFramPosition();
        }
        
        if (e.getSource() == fullHeapify)               // if the event to be handled 
                                                        //    is the full Heapify button
        {
            currFrame = numFrames - 1;
            checkFramPosition();
        }        
        
        repaint();
    }

}
