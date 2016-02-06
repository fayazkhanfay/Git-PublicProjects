import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.event.*;//used for ActionListner 
import javax.swing.*;


//FUN FACT!!!!
/*
 * CicleApplet2 will show error until you put in 
 * public void actionPerformed(ActionEvent e) at the bottom 
 * to my understanding it shows on CicleApplet but that is because the line
 * is not in 
 * */
public  class CircleApplet2 extends JApplet implements ActionListener 
{
	
	/*
	 * We are defineing variables so we can use them later to but we will actually 
	 * create the specific object later but we are currently making the pointers to them 
	 * currently these pointers are not pointing anywhere 
	 * 
	 * */
	
	//JLabel comes from JApplet 
	private JLabel description;  // Description of program's functionality
	private JLabel promptCenterX;  // Prompt for center x-coordinate
	private JLabel promptCenterY;	// Prompt for center y-coordinate
	private JLabel promptRadius;	// Prompt for radius
	
	//The below is for the user input 
	private JTextField inCenterX;	// Field to input center x-coordinate
	private JTextField inCenterY;  //Field to input center y-coordinate
	private JTextField inRadius;   // Field to input radius
	
	private int centerX;                     // Center x-coordinate of circle to draw
    private int centerY;                     // Center y-coordinate of circle to draw
    private int radius;                      // Radius of circle to draw
	
    @Override
    public void init()                            // Set up GUI, initialize variables
    {
        setLayout(new FlowLayout());

        description = new JLabel("This program will draw a circle.");
        add(description);

        promptCenterX = new JLabel("Enter center x-coordinate: "); // Set up input
        add(promptCenterX);                                        // for x-coord.
        inCenterX = new JTextField(5);
        add(inCenterX);

        promptCenterY = new JLabel("Enter center y-coordinate: "); // Set up input
        add(promptCenterY);                                        // for y-coord.
        inCenterY = new JTextField(5);
        add(inCenterY);

        promptRadius = new JLabel("Enter radius and hit Enter:"); // Set up input
        add(promptRadius);                                        // for radius
        inRadius = new JTextField(5);
        inRadius.addActionListener(this);                         // Process upon enter
        add(inRadius);
    }

    @Override
    public void paint(Graphics g)                        // Display results
    {
       int startX;                                       // Upper left x of bounding rect.
       int startY;                                       // Upper left y of bounding rect.
	   
       super.paint(g);

       startX = centerX - radius;                        // Move by radius to get top corner
       startY = centerY - radius;

       g.drawOval(startX, startY, radius*2, radius*2);   // Draw circle
    }

    public void actionPerformed(ActionEvent e)           // Process user actions
    {
        centerX = Integer.parseInt(inCenterX.getText()); // Store user inputs
        centerY = Integer.parseInt(inCenterY.getText());
        radius  = Integer.parseInt(inRadius.getText());

        repaint();                                       // Redraw circle

    }
    
    
    
	
}