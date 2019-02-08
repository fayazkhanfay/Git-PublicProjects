import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;

public class Monopoly2 extends JApplet implements ActionListener, ItemListener 
{
	//Final colors for making the more user friendly
	private static final Color BOARD= new Color(178, 255, 178);
	private static final Color BROWN= new Color(102, 51, 0);
	private static final Color LIGHTBLUE= new Color(102, 178, 255);
	private static final Color DARKYELLOW= new Color(204, 204, 0);
	private static final Color DARKBLUE= new Color(0, 0, 204);
 
	//Color Array for displaying the giant card and the bottom strip of cards
	Color[] colorArray= {Color.WHITE, BROWN, Color.WHITE, BROWN, Color.WHITE, Color.WHITE, 
								LIGHTBLUE, Color.WHITE, LIGHTBLUE, LIGHTBLUE, Color.WHITE, Color.MAGENTA, 
								Color.WHITE, Color.MAGENTA, Color.MAGENTA, Color.WHITE, DARKYELLOW, 
								Color.WHITE, DARKYELLOW, DARKYELLOW, Color.WHITE, Color.RED, Color.WHITE, 
								Color.RED, Color.RED, Color.WHITE, Color.YELLOW, Color.YELLOW, Color.WHITE, 
								Color.YELLOW, Color.WHITE, Color.GREEN, Color.GREEN, Color.WHITE, 
								Color.GREEN, Color.WHITE, Color.WHITE, DARKBLUE, Color.WHITE, DARKBLUE};
 
	//First line for the bottom strip property name
	String[] oneLineProperty= {"GO", "MEDITER-", "COMMUN-", "BALTIC", "INCOME", "READING",
										"ORIENTAL", "CHANCE", "VERMONT", "CONNETI-", "JAIL", "ST.CHARL-", 
										"ELECTRIC", "STATES", "VIRGINIA", "PENNSYL-", "ST.JAMES", "COMMUN-",
										"TENNESS-", "NEW YORK", "FREE", "KENTUC-", "CHANCE", "INDIANA", 
										"ILLINOIS", "B&O", "ATLANTIC", "VENTNOR", "WATER", "MARVIN", "GO TO",
										"PACIFIC", "NORTH", "COMMUN-", "PENNSYL-", "SHORT", "CHANCE", "PARK",
										"LUXURY", "BOARD-"};
 
	//Second Line for the bottom strip property name
	String[] twoLineProperty= {"", "RANEAN", "ITY", "", "", "", "", "", "", "CUT", "", "ES", "",
										"", "", "VANIA", "", "ITY", "EE", "", "", "KY", "", "", "", "", "", 
										"", "", "", "", "", "CAROLINA", "ITY", "VANIA", "", "", "", 
										"", "WALK"};
 
	//Third Line for the bottom strip property name
	String[] threeLineProperty= {"", "AVENUE", "CHEST", "AVENUE", "TAX", "RAILROAD","AVENUE", "",
											"AVENUE", "AVENUE", "", "PLACE", "COMPANY", "AVENUE", "AVENUE",
											"RAILROAD", "PLACE", "CHEST", "AVENUE", "AVENUE", "PARKING", 
											"AVENUE", "", "AVENUE", "AVENUE", "RAILROAD", "AVENUE", "AVENUE", 
											"WORKS", "GARDENS", "JAIL", "AVENUE", "AVENUE", "CHEST", "AVENUE",
											"LINE", "", "PLACE", "TAX", "AVENUE"};
 
	//All rents for initializing board locations and for displaying them on the giant card
	int [][]mRent= {{0,0,0,0,0,0},{2,10,30,90,160,230},{0,0,0,0,0,0},{4,20,60,180,320,450},
						{0,0,0,0,0,0},{0,0,0,0,0,0},{6,30,90,270,400,550},{0,0,0,0,0,0},
						{6,30,90,270,400,550},{8,40,100,300,450,600},{0,0,0,0,0,0},
						{10,50,150,450,625,750},{0,0,0,0,0,0},{10,50,150,450,625,750},
						{12,60,180,500,700,900},{0,0,0,0,0,0},{14,70,200,550,750,950},{0,0,0,0,0,0},
						{14,70,200,550,750,950},{16,80,220,600,800,1000},{0,0,0,0,0,0},
						{18,90,250,700,875,1050},{0,0,0,0,0,0},{18,90,250,700,875,1050},
						{20,100,300,750,925,1100},{0,0,0,0,0,0},{22,110,330,800,975,1150},
				      {22,110,330,800,975,1150},{0,0,0,0,0,0},{24,120,360,850,1025,1200},{0,0,0,0,0,0},
				      {26,130,390,900,1100,1275},{26,130,390,900,1100,1275},{0,0,0,0,0,0},
				      {28,150,450,1000,1200,1400},{0,0,0,0,0,0},{0,0,0,0,0,0},
				      {35,175,500,1100,1300,1500},{0,0,0,0,0,0},{50,200,600,1400,1700,2000}};

 //Price of the property to be displayed on the bottom strip
	String []priceProperty={"","$60","","$60","$75","$200","$100","","$100","$120","","$140","$150",
						        "$140","$160","$200","$180","","$180","$200","","$220","","$220",
						        "$240","$200","$260","$260","$150","$280","","$300","$300","","$320",
						        "$200","","$350","$200","$400"};
 
	BorderLayout layout;           			 	//Layout for the applet
	Font font;                      				//Font is used to write the bottom strip
	Font fontTwo;                   				//Font is used for the giant card
	Font fontThree;                 				//Font is used to display player status
	JButton rollDice;               				//Rolls the Dice 1-12
	JButton nextTurn;               				//Ends the turn and performs task
	JButton currentPlayerProperties;        	//Displays all properties owned by player
	JButton printAll;               				//Displays all game details
	JButton exit;                   				//Ends game
	JRadioButton rent;              				//Pay Rent
	JRadioButton buyProperty;       				//Buying a property
	JRadioButton buyHouse;          				//Buying a House
	JRadioButton buyHotel;          				//Buying a Hotel
	JRadioButton sellHouse;         				//Sell a House
	JRadioButton sellHotel;         				//Sell a Hotel
	Boolean rentToPay;              				//All Boolean below are used for buttons
	Boolean hotelToBuy;
	Boolean houseToBuy;
	Boolean houseToSell;
	Boolean hotelToSell;
	Boolean propertyToBuy;
	Boolean checker;
	ButtonGroup radioGroup;          			//Groups the radio buttons to select one
	Player[] allPlayers= new Player[4];  		//Initialize Players
	Board[] locations= new Board[40];    		//Initialize Board locations
	int currentDice;                				//Current location with Dice
	int currentPlayer;              				//Current player to perform actions with
	String enforcer="";             				//Mandatory rent
 
 
 @Override
 public void init()
 {
	 layout= new BorderLayout();
	 setLayout(layout);           				//sets layout
  
  
		font= new Font("Serif", Font.BOLD, 9);     //Different sizes for different uses
		fontTwo= new Font("Serif", Font.BOLD, 20);
		fontThree= new Font("Serif", Font.BOLD, 15);
		
		JPanel panel1= new JPanel();               //Panels for GUI
		JPanel panel2= new JPanel();
		radioGroup= new ButtonGroup();
		
		rollDice= new JButton ("Roll Dice");     //Initializing buttons and attaching 
		rollDice.addActionListener(this);        //  action listeners to it.
		nextTurn= new JButton ("Next Turn");
		nextTurn.addActionListener(this);
		currentPlayerProperties= new JButton ("Properties you Own");
		currentPlayerProperties.addActionListener(this);
		printAll= new JButton ("Print All Details");
		printAll.addActionListener(this);
		exit= new JButton ("Exit");
		exit.addActionListener(this);
		rent = new JRadioButton("Rent",false);
		rent.addItemListener(this);
		
		buyProperty = new JRadioButton("Buy Property",false);//Initializing radio buttons and 
		buyProperty.addItemListener(this);        //  attaching item listeners to it.
		buyHouse = new JRadioButton("Buy House",false);
		buyHouse.addItemListener(this);
		buyHotel = new JRadioButton("Buy Hotel",false);
		buyHotel.addItemListener(this);
		sellHouse = new JRadioButton("Sell House",false);
		sellHouse.addItemListener(this);
		sellHotel = new JRadioButton("Sell Hotel",false);
		sellHotel.addItemListener(this);
		
		nextTurn.setEnabled(false);         //Initially disables all GUIs
		rent.setEnabled(false);
		buyProperty.setEnabled(false);
		buyHouse.setEnabled(false);
		buyHotel.setEnabled(false);
		sellHouse.setEnabled(false);
		sellHotel.setEnabled(false);
		
		radioGroup.add(rent);           //Grouping all radio buttons
		radioGroup.add(buyProperty);
		radioGroup.add(buyHouse);
		radioGroup.add(buyHotel);
		radioGroup.add(sellHouse);
		radioGroup.add(sellHotel);
		
		getContentPane().setBackground(Color.RED);    //sets the background to applet
		panel1.setBackground(Color.RED);
		panel2.setBackground(Color.RED);
		
		panel1.add(rollDice);           //Adds all UI to first panel which is
		panel1.add(nextTurn);           //  a gridLayout
		panel1.add(rent);
		panel1.add(buyProperty);
		panel1.add(buyHouse);
		panel1.add(buyHotel);
		panel1.add(sellHouse);
		panel1.add(sellHotel);
		panel1.add(currentPlayerProperties);
		panel1.add(printAll);
		panel1.add(exit);
		
		panel2.setLayout(new GridLayout(3,1,5,5));    //Creates gridLayout for panels
		panel1.setLayout(new GridLayout(6,2,5,10));    
		JLabel label= new JLabel("");         
		panel2.add(label);            
		panel2.add(panel1);
		add(layout.EAST,panel2);          //Adds the entire GUI to applet
		
		players();               //Initializes all Players
		locationInit();             //Initializes all Locations
		//demoMode();
		
		currentPlayer= (int) (Math.random()*4);     //Picks a random player
		JOptionPane.showMessageDialog(null, "Player " + (currentPlayer+1));
		currentDice= 0;  
 }
 
 @Override
 public void paint(Graphics g)
 { 
		int appHeight=getHeight();          //calculations for the applet when
		int appWidth= getWidth();          //  it resizes
		int borderStart= appHeight-125;
		int borderEnd= borderStart+115;
		int xBorderStart=10+((getWidth()-20)/10);
		int multiplier;
		int[] xToken= new int[10];
		int midpoint= (appWidth-20)/2;
		multiplier=xBorderStart-40;
		for(int i=0; i<10; i++)
		{
			xToken[i]= multiplier;
			multiplier+= (xBorderStart-10);
		}
		
		super.paint(g);
		
		//draws the bottom strip with the locations and price
		drawBottomStrip(g, appHeight, appWidth, borderStart, borderEnd, multiplier, xBorderStart);
		
		//draws the giant resizing card
		giantCard(g, appWidth, appHeight, midpoint);
		
		//draws the player status for all players
		statusScreen(g,midpoint);
		
		//draws token at the Dice location depending on the player
		int number= currentDice%10;
		if(currentPlayer==0)
		{
			tokenOne(g, number, borderStart, xToken);
		}
		else if(currentPlayer==1)
		{
			tokenTwo(g, number, borderStart, xToken);
		}
		else if(currentPlayer==2)
		{
			tokenThree(g, number, borderStart, xToken);
		}
		else if(currentPlayer==3)
		{
			tokenFour(g, number, borderStart, xToken);
		}
 }
 
 
 
 public void drawBottomStrip(Graphics g, int appHeight, int appWidth, int borderStart,
           int borderEnd, int multiplier, int xBorderStart)
 //PRE:  g needs to be initialized
 //      appHeight > 0
 //      appWidth > 0
 //      borderStat > 0
 //      borderEnd > 0
 //      multiplier > 0
 //      xBorderStart > 0
 //POST: Draws the bottom strip by using the appHeight and appWidth. borderStart
 //      is the start of the card divider and borderEnd of it. multiplier is
 //      used to move from card to card.
 {
	 	multiplier= xBorderStart;
	 	g.setColor(BOARD);
	 	g.fillRect(10, appHeight-125, appWidth-20, 115);
	 	g.setColor(Color.BLACK);
	 	g.drawRect(10,appHeight-125,appWidth-20, 115);
	 	for(int i =0; i<9; i++)
	 	{
	 		g.drawLine(multiplier, borderStart, multiplier, borderEnd);
	 		multiplier+=(xBorderStart-10);
	 	}
  
  
	 	g.setFont(font);
	 	//if currentDice is less than 9 then perform this else mod to find the ten cards
	 	//it draws the card color and then draws the information about the card
	 	if(currentDice<=9)
	 	{
	 		multiplier= 12;
	 		int yStartLocation= borderStart+2;
	 		for(int i=0; i<10; i++)
	 		{  
	 			g.setColor(colorArray[i]);
	 			g.fillRect(multiplier, yStartLocation, xBorderStart-14, 30);
	 			g.setColor(Color.BLACK);
	 			g.drawString(oneLineProperty[i],multiplier+2,yStartLocation+8);
	 			g.drawString(twoLineProperty[i],multiplier+10,yStartLocation+16);
	 			g.drawString(threeLineProperty[i],multiplier+2,yStartLocation+24);
	 			g.drawString("("+i+")", multiplier+10, yStartLocation+40);
	 			g.drawString(priceProperty[i], multiplier+10, appHeight-15);
	 			multiplier+=(xBorderStart-10);
	 		}
	 	}
	 	else
	 	{
	 		int sidePicker;
	 		if(currentDice==10)
	 		{
	 			sidePicker=1;
	 		}
	 		else
	 		{
	 			sidePicker= currentDice/10;
	 		}
	 		int startIndex= 10*sidePicker;
	 		multiplier= 12;
	 		int yStartLocation= borderStart+2;
	 		for(int i= startIndex; i<(startIndex+10); i++)
	 		{
	 			g.setColor(colorArray[i]);
	 			g.fillRect(multiplier, yStartLocation, xBorderStart-14, 30);
	 			g.setColor(Color.BLACK);
	 			g.drawString(oneLineProperty[i],multiplier+2,yStartLocation+8);
	 			g.drawString(twoLineProperty[i],multiplier+10,yStartLocation+16);
	 			g.drawString(threeLineProperty[i],multiplier+2,yStartLocation+24);
	 			g.drawString("("+i+")", multiplier+10, yStartLocation+40);
	 			g.drawString(priceProperty[i], multiplier+10, appHeight-15);
	 			multiplier+=(xBorderStart-10);
	 		}
	 	}
 }
 
 public void statusScreen(Graphics g, int midpoint)
 //Pre:  g is initialized
 //      midpoint > 0
 //Post: Shows the status of all players but uses midpoint to locate and
 //      Coordinate inside the CYAN box
 {
	 g.setFont(fontThree);
	 int statusW= ((getWidth()-40)/2);
	 g.setColor(Color.CYAN);
	 g.fillRect(midpoint+20, 20, statusW, 150);
	 g.setColor(Color.BLACK);
	 g.drawRect(midpoint+20, 20, statusW, 150);
	 g.drawString(allPlayers[0].getWealthAndPosition(), midpoint+30, 40);
	 g.drawString(allPlayers[1].getWealthAndPosition(), midpoint+30, 80);
	 g.drawString(allPlayers[2].getWealthAndPosition(), midpoint+30, 120);
	 g.drawString(allPlayers[3].getWealthAndPosition(), midpoint+30, 160);
 }
 
 public void giantCard(Graphics g, int appWidth, int appHeight, int midpoint)
 //PRE:  g needs to be initialized
 //      appHeight > 0
 //      appWidth > 0
 //      multiplier > 0
 //POST: creates a giant monopoly property card based on the appWidth and appHeight
 //      but the width is less than the midpoint.
 {
	 g.setFont(fontTwo);
	 g.setColor(Color.WHITE);
	 g.fillRect(10, 20, midpoint, appHeight-175);
	 g.setColor(colorArray[currentDice]);
	 g.fillRect(15, 25, midpoint-10, 65);
	 g.setColor(Color.BLACK);
	 g.drawRect(10,20, midpoint, appHeight-175);
  
	 int midMidpoint = (midpoint+50)/3;
	 //draws the name at the top
	 g.drawString(oneLineProperty[currentDice],midMidpoint,45);
	 g.drawString(twoLineProperty[currentDice],midMidpoint,65);
	 g.drawString(threeLineProperty[currentDice],midMidpoint,85);
  
	 //Railroads
	 if(currentDice==5 || currentDice==15 || currentDice==25 || currentDice==35)
	 {
		 g.drawString("Rent: ", 30, 130);
		 g.drawString("If 2 RR owned: ", 30, 200);
		 g.drawString("If 3 RR owned: ", 30, 240);
		 g.drawString("If 4 RR owned: ", 30, 280);
		 g.drawString("$25", midpoint-60, 130);
		 g.drawString("$50", midpoint-60, 200);
		 g.drawString("$100", midpoint-60, 240);
		 g.drawString("$200", midpoint-60, 280);
	 }
	 //Community Chest or Chance
	 else if(currentDice==2 || currentDice==7 || currentDice==17 || currentDice==22
			 	|| currentDice==33 || currentDice==36)
	 {
		 g.drawString("Adds or substracts $0-$200", 30, 280);
	 }
	 //Taxes
	 else if(currentDice==4 || currentDice==38)
	 {
		 g.drawString("Pay Tax(Rent) of $75 or $200", 30, 280);
	 }
	 //Utility
	 else if(currentDice==12 || currentDice==28)
	 {
		 g.drawString("If one Utility is owned,", midMidpoint-50, 200);
		 g.drawString("rent is 4 times amount", midMidpoint-50, 240);
		 g.drawString("shown on dice", midMidpoint-50, 280);
		 g.drawString("If two Utility is owned", midMidpoint-50, 320);
		 g.drawString("rent is 10 times amount", midMidpoint-50, 360);
		 g.drawString("shown on dice", midMidpoint-50, 400);
	 }
	 //Property
	 else
	 {
		 g.drawRect(15, 25, midpoint-10, 65);
		 g.drawString("Rent: $"+mRent[currentDice][0], midMidpoint, 130);
		 g.drawString("House 1: ", 30, 200);
		 g.drawString("$"+mRent[currentDice][1], midpoint-60, 200);
		 g.drawString("House 2: ", 30, 240);
		 g.drawString("$"+mRent[currentDice][2], midpoint-60, 240);
		 g.drawString("House 3: ", 30, 280);
		 g.drawString("$"+mRent[currentDice][3], midpoint-60, 280);
		 g.drawString("House 4: ", 30, 320);
		 g.drawString("$"+mRent[currentDice][4], midpoint-60, 320);
		 g.drawString("Hotel: $"+mRent[currentDice][5], midMidpoint, 400);
	 }
 	}
 
 	//dispays all the properties a player owns by a scrollable pane
 	public void playerProperties()
 	{
 		String result= allPlayers[currentPlayer].getProperties();
 		JTextArea area;
 		JScrollPane pane;
  
 		area= new JTextArea(result);
 		area.setRows(20);
 		area.setColumns(40);
 		pane= new JScrollPane(area);
 		JOptionPane.showConfirmDialog(null, pane, "Player Properties", JOptionPane.PLAIN_MESSAGE);
 	}
 
 	public void allInfo(String result)
 	//PRE:  result needs to initialized
 	//POST: Adds information to the result and then displayes it to the user in a JScrollPane
 	{
 		result+= "Players Information\n\n";
 		for(int i=0; i<4; i++)
 		{
 			result+= allPlayers[i].toString() +"\n";
 		}
 		result+= "\n Location Status:\n";
 		for(int i=0; i<40; i++)
 		{
 			result+= locations[i].toString() +"\n";
 		}
 		JTextArea area;
 		JScrollPane pane;
  
 		area= new JTextArea(result);
 		area.setRows(20);
 		area.setColumns(40);
 		pane= new JScrollPane(area);
 		JOptionPane.showConfirmDialog(null, pane, "Player Properties", JOptionPane.PLAIN_MESSAGE);
 	}
    
 	//parses for all possible actions a player can perform on a specific location
 	public void parsePossibleActions()
 	{
 		String []actions= locations[currentDice].getPossibleActions(allPlayers[currentPlayer]);
  
 		//Enables UI radio buttons based on the possible actions received
 		if(actions[0].equals("Buy Property?"))
 		{
 			buyProperty.setEnabled(true);
 		}
 		if(actions[1].equals("Do nothing"))
 		{
 			//Does Nothing
 		}
 		if(actions[2].equals("Buy House?"))
 		{
 			buyHouse.setEnabled(true);
 		}
 		if(actions[3].equals("Buy Hotel?"))
 		{
 			buyHotel.setEnabled(true);
 		}
 		if(actions[4].equals("Sell House for half value?"))
 		{
 			sellHouse.setEnabled(true);
 		}
 		if(actions[5].equals("Sell Hotel for half value?"))
 		{
 			sellHotel.setEnabled(true);
 		}
 		if(actions[6].equals("Pay Rent"))
 		{
 			enforcer = "Pay Rent";
 			rent.setEnabled(true);
 		}
 	}
 
 	public void actionPerformed(ActionEvent e)
 	{
 		int dice=0;
 		int d1=0;
 		int d2=0;
 		boolean snakeEyes=false;
 		//rolls the dice and parses possible actions
 		if(e.getSource()== rollDice)
 		{
 			d1= (int) (1+(Math.random()*6));							//Dice 1
 			d2= (int) (1+(Math.random()*6));							//Dice 2
 			dice= d1+d2;													//Dice total
 			JOptionPane.showMessageDialog(null, "You rolled " + d1 +" and "+ d2+" which is " + dice);
 			int playerLocation= allPlayers[currentPlayer].getPlayerPosition();
 			if((playerLocation+dice)>39)								//If player passes GO then pay $200
 			{
 				currentDice=(playerLocation+dice)-39;
 				allPlayers[currentPlayer].changeWealth(200);
 				allPlayers[currentPlayer].movePosition(dice);
 				JOptionPane.showMessageDialog(null, "You passed GO!! You earned $200!!" );
 			}
 			else																//else continue normal game play
 			{
 				allPlayers[currentPlayer].movePosition(dice);
 				currentDice=allPlayers[currentPlayer].getPlayerPosition();
 			}
   
 			parsePossibleActions();										//parses for possible actions and
 																				//		enables UI
 			rollDice.setEnabled(false);
 			nextTurn.setEnabled(true);
 		}
     
 		//views all possible properties owned by player
 		if(e.getSource()== currentPlayerProperties)
 		{
 			playerProperties();
 		}
 		
 		//prints all information about the game
 		if(e.getSource()==printAll)
 		{
 			String result="";
 			allInfo(result);
 		}
 		
 		//exits the game but prints all information about the game before exiting
 		if(e.getSource()==exit)
 		{
 			String result="Game Over!\n";
 			allInfo(result);
 			System.exit(0);
 		}
 		
 		//Performs the actions from the UI selected and then disables the UI. It Also goes to the 
 		//		next player.
 		if(e.getSource()==nextTurn)
 		{ 
 			performActions(dice);
   
 			rent.setEnabled(false);
 			buyProperty.setEnabled(false);
 			buyHouse.setEnabled(false);
 			buyHotel.setEnabled(false);
 			sellHouse.setEnabled(false);
 			sellHotel.setEnabled(false);
   
 			rentToPay = false;
 			hotelToBuy = false;
 			houseToBuy = false;
 			houseToSell = false;
 			hotelToSell = false;
 			propertyToBuy = false;
   
 			//if snake eyes happened during dice roll then doesn't change player
 			if(snakeEyes==false)
 			{
 				currentPlayer++;
 			}
 			if(currentPlayer>=4)
 			{
 				currentPlayer=0;
 			}
 			
 			JOptionPane.showMessageDialog(null, "Player " + (currentPlayer+1));
 			rollDice.setEnabled(true);
 			nextTurn.setEnabled(false);
 		}
 		repaint();
 	}
    
 	//performs actions based on the UI selected
 	public void performActions(int diceVal)
 	{
 		radioGroup.clearSelection();									//Clears all selection for the next turn
 		
 		int godAnswer= (int) (1+(Math.random()*1000));			//Replicates behavior of our artificial
 																				//		god.
 
 		//God class called to perform an action
 		if((godAnswer%7)==0)												
 		{
 			JOptionPane.showMessageDialog(null, God.heTakethAndHeGiveth(allPlayers[currentPlayer]));
 		}
 		else if((godAnswer%17)==0)
 		{
 			JOptionPane.showMessageDialog(null, God.heBurneth(allPlayers, locations));
 		}
  
 		//Charges rent regardless if the button is pressed
 		if(enforcer.equals("Pay Rent") || rentToPay == true)
 		{
 			rentToPay=false;
 			enforcer= "";
 			
 			//if landed on a railroad
 			if(currentDice==5 || currentDice==15 || currentDice==25 || currentDice==35)
 			{
 				int numOwned= allPlayers[currentPlayer].getNumOfRailRoads();
 				checker = locations[currentDice].payRent(allPlayers[currentPlayer], diceVal, numOwned);
 				int rent = ((Property)locations[currentDice]).calcRent(allPlayers[currentPlayer], diceVal, numOwned);
 				JOptionPane.showMessageDialog(null, "Rent charged: $" + rent);
 				for(int i=0; i<4; i++)
 				{
 					if(((Railroad)locations[currentDice]).getOwner().equals(allPlayers[i].getToken()))
 					{
 						allPlayers[currentPlayer].changeWealth(rent);
 					}
 				}
 			}
 			//if landed on a utility
 			else if(currentDice==12 || currentDice==28)
 			{
 				int numOwned= allPlayers[currentPlayer].getNumOfUtilities();
 				checker = locations[currentDice].payRent(allPlayers[currentPlayer], diceVal, numOwned);
 				int rent = ((Property)locations[currentDice]).calcRent(allPlayers[currentPlayer], diceVal, numOwned);
 				JOptionPane.showMessageDialog(null, "Rent charged: $" + rent);
 				for(int i=0; i<4; i++)
 				{
 					if(((Utility)locations[currentDice]).getOwner().equals(allPlayers[i].getToken()))
 					{
 						allPlayers[currentPlayer].changeWealth(rent);
 					}
 				}
 			}
 			//if landed on a property
 			else
 			{
 				if(locations[currentDice] instanceof Property)
 				{
 					int rent = ((Property)locations[currentDice]).calcRent(allPlayers[currentPlayer], diceVal, 0);
 					JOptionPane.showMessageDialog(null, "Rent charged: $" + rent);
 					for(int i=0; i<4; i++)
 					{
 						if(((Property)locations[currentDice]).getOwner().equals(allPlayers[i].getToken()))
 						{
 							allPlayers[i].changeWealth(rent);
 						}
 					}
 				}
 				checker = locations[currentDice].payRent(allPlayers[currentPlayer], diceVal, 0);    
 			}
 			//if rent was successfully payed
 			if(checker)
 			{
 				JOptionPane.showMessageDialog(null, "Rent Payed");
 			}
 			else
 			{
 				String result="Game Over!\n\n";
 				allInfo(result);
 				System.exit(0);
 			}
 		}
 		
 		//buys the property at current location
 		if(propertyToBuy == true)
 		{
 			propertyToBuy = false;
 			if(locations[currentDice] instanceof Property)
 			{
 				checker= ((Property) locations[currentDice]).buy(allPlayers[currentPlayer], locations);
 				if(checker)
 				{
 					JOptionPane.showMessageDialog(null, "Property Bought");
 				}
 				else
 				{
 					JOptionPane.showMessageDialog(null, "Insufficient Funds");
 				}
 			}
 		}
 		
 		//buys a hotel at any location if owned by the user.
 		if(hotelToBuy== true)
 		{
 			hotelToBuy = false;
 			String input= JOptionPane.showInputDialog("Enter Index to buy House:");
 			int stringToInput= Integer.parseInt(input);
 			if(locations[stringToInput] instanceof Lot)
 			{
 				if(((Lot)locations[stringToInput]).getOwner().equals(allPlayers[currentPlayer].getToken()))
 				{
 					checker= ((Lot) locations[stringToInput]).buyHotel(allPlayers[currentPlayer]);
 					if(checker)
 					{
 						JOptionPane.showMessageDialog(null, "Hotel Bought");
 					}
 					else
 					{
 						JOptionPane.showMessageDialog(null, "Insufficient Funds");
 					}
 				}
 				else
 				{
 					JOptionPane.showMessageDialog(null, "You do not own that Property!!");
 				}
 			}
 			else
 			{
 				JOptionPane.showMessageDialog(null, "Invalid Entry!!");
 			}
 		}
 		
 		//buys a house at any location if owned by the user.
 		if(houseToBuy== true)
 		{
 			houseToBuy = false;
 			String input= JOptionPane.showInputDialog("Enter Index to buy House:");
 			int stringToInput= Integer.parseInt(input);
 			if(locations[stringToInput] instanceof Lot)
 			{
 				if(((Lot)locations[stringToInput]).getOwner().equals(allPlayers[currentPlayer].getToken()))
 				{
 					checker= ((Lot) locations[stringToInput]).buyHouse(allPlayers[currentPlayer]);
 					if(checker)
 					{
 						JOptionPane.showMessageDialog(null, "House Bought");
 					}
 					else
 					{
 						JOptionPane.showMessageDialog(null, "Insufficient Funds");
 					}
 				}
 				else
 				{
 					JOptionPane.showMessageDialog(null, "You do not own that Property!!");
 				}
 			}
 			else
 			{
 				JOptionPane.showMessageDialog(null, "Invalid Entry!!");
 			}
 		}
 		
 		//sells a house at any location if there exists a house
 		if(houseToSell== true)
 		{
 			houseToSell = false;
 			String input= JOptionPane.showInputDialog("Enter Index to sell House:");
 			int stringToInput= Integer.parseInt(input);
 			if(locations[stringToInput] instanceof Lot)
 			{
 				if(((Lot)locations[stringToInput]).getOwner().equals(allPlayers[currentPlayer].getToken()))
 				{
 					checker= ((Lot) locations[stringToInput]).sellHouse(allPlayers[currentPlayer]);
 					if(checker)
 					{
 						JOptionPane.showMessageDialog(null, "Sold House");
 					}
 					else
 					{
 						JOptionPane.showMessageDialog(null, "Insufficient Funds");
 					}
 				}
 				else
 				{
 					JOptionPane.showMessageDialog(null, "You do not own that Property!!");
 				}
 			}
 			else
 			{
 				JOptionPane.showMessageDialog(null, "Invalid Entry!!");
 			}
 		}
 		
 		//sells a hotel at any location if there exists a hotel and gives back the houses
 		if(hotelToSell== true)
 		{
 			hotelToSell = false;
 			String input= JOptionPane.showInputDialog("Enter Index to sell Hotel:");
 			int stringToInput= Integer.parseInt(input);
 			if(locations[stringToInput] instanceof Lot)
 			{
 				if(((Lot)locations[stringToInput]).getOwner().equals(allPlayers[currentPlayer].getToken()))
 				{
 					checker= ((Lot) locations[stringToInput]).sellHotel(allPlayers[currentPlayer]);
 					if(checker)
 					{
 						JOptionPane.showMessageDialog(null, "Sold Hotel");
 					}
 					else
 					{
 						JOptionPane.showMessageDialog(null, "Insufficient Funds");
 					}
 				}
 				else
 				{
 					JOptionPane.showMessageDialog(null, "You do not own that Property!!");
 				}
 			}
 			else
 			{
 				JOptionPane.showMessageDialog(null, "Invalid Entry!!");
 			}
 		}
 	}
 
 	//Listens for a click on the radio buttons. If one is selected then specific action turns true
 	//  everything else is false.
 	public void itemStateChanged(ItemEvent e)
 	{
 		
 		//sets everything else to false so there is no chance of error.
 		if(e.getSource()== buyProperty && e.getStateChange()== ItemEvent.SELECTED)
 		{
 			rentToPay = false;
 			hotelToBuy = false;
 			houseToBuy = false;
		 	houseToSell = false;
		 	hotelToSell = false;
		 	propertyToBuy = true;
		}
		if(e.getSource()== buyHouse && e.getStateChange()== ItemEvent.SELECTED)
		{
			rentToPay = false;
			hotelToBuy = false;
			houseToBuy = true;
			houseToSell = false;
			hotelToSell = false;
			propertyToBuy = false;
		}
		if(e.getSource()== buyHotel && e.getStateChange()== ItemEvent.SELECTED)
		{
			rentToPay = false;
		 	hotelToBuy = true;
		 	houseToBuy = false;
		 	houseToSell = false;
		 	hotelToSell = false;
		 	propertyToBuy = false;
		}
		if(e.getSource()== sellHouse && e.getStateChange()== ItemEvent.SELECTED)
		{
			rentToPay = false;
		 	hotelToBuy = false;
		 	houseToBuy = false;
		 	houseToSell = true;
		 	hotelToSell = false;
		 	propertyToBuy = false;
		}
		if(e.getSource()== sellHotel && e.getStateChange()== ItemEvent.SELECTED)
		{
			rentToPay = false;
			hotelToBuy = false;
		 	houseToBuy = false;
		 	houseToSell = false;
		 	hotelToSell = true;
		 	propertyToBuy = false;
		}
		if(e.getSource()== rent && e.getStateChange()== ItemEvent.SELECTED)
		{
			rentToPay = true;
			hotelToBuy = false;
			houseToBuy = false;
			houseToSell = false;
			hotelToSell = false;
			propertyToBuy = false;
		}
		repaint();
 }
 
 
 //Demo mode also known as Quick Mode where some properties are bought and
 //houses are pre-allocated 
 public void demoMode()
 {
		boolean buy;
		boolean house;
		boolean hotel;
		buy= ((Property) locations[1]).buy(allPlayers[0], locations);
		buy= ((Property) locations[8]).buy(allPlayers[0], locations);
		buy= ((Property) locations[28]).buy(allPlayers[0], locations);
		buy= ((Property) locations[26]).buy(allPlayers[0], locations);
		buy= ((Property) locations[3]).buy(allPlayers[1], locations);
		buy= ((Property) locations[9]).buy(allPlayers[1], locations);
		buy= ((Property) locations[31]).buy(allPlayers[1], locations);
		buy= ((Property) locations[18]).buy(allPlayers[1], locations);
		buy= ((Property) locations[9]).buy(allPlayers[2], locations);
		buy= ((Property) locations[16]).buy(allPlayers[2], locations);
		buy= ((Property) locations[35]).buy(allPlayers[2], locations);
		buy= ((Property) locations[24]).buy(allPlayers[2], locations);
		buy= ((Property) locations[6]).buy(allPlayers[3], locations);
		buy= ((Property) locations[23]).buy(allPlayers[3], locations);
		buy= ((Property) locations[39]).buy(allPlayers[3], locations);
		buy= ((Property) locations[18]).buy(allPlayers[3], locations);
		allPlayers[0].changeWealth(300);
		allPlayers[1].changeWealth(1200);
		allPlayers[2].changeWealth(600);
		allPlayers[3].changeWealth(1200);
		house= ((Lot) locations[1]).buyHouse(allPlayers[0]);
		house= ((Lot) locations[1]).buyHouse(allPlayers[0]);
		house= ((Lot) locations[1]).buyHouse(allPlayers[0]);
		house= ((Lot) locations[1]).buyHouse(allPlayers[0]);
		house= ((Lot) locations[31]).buyHouse(allPlayers[1]);
		house= ((Lot) locations[31]).buyHouse(allPlayers[1]);
		house= ((Lot) locations[18]).buyHouse(allPlayers[1]);
		house= ((Lot) locations[18]).buyHouse(allPlayers[1]);
		house= ((Lot) locations[18]).buyHouse(allPlayers[1]);
		house= ((Lot) locations[18]).buyHouse(allPlayers[1]);
		hotel= ((Lot) locations[18]).buyHotel(allPlayers[1]);
		house= ((Lot) locations[16]).buyHouse(allPlayers[2]);
		house= ((Lot) locations[16]).buyHouse(allPlayers[2]);
		house= ((Lot) locations[16]).buyHouse(allPlayers[2]);
		house= ((Lot) locations[24]).buyHouse(allPlayers[2]);
		house= ((Lot) locations[6]).buyHouse(allPlayers[3]);
		house= ((Lot) locations[6]).buyHouse(allPlayers[3]);
		house= ((Lot) locations[6]).buyHouse(allPlayers[3]);
		house= ((Lot) locations[6]).buyHouse(allPlayers[3]);
		hotel= ((Lot) locations[6]).buyHotel(allPlayers[3]);
		house= ((Lot) locations[23]).buyHouse(allPlayers[3]);
		house= ((Lot) locations[39]).buyHouse(allPlayers[3]);
		house= ((Lot) locations[18]).buyHouse(allPlayers[3]);
 }
 
 //moving token for the bottom strip
 public void tokenFour(Graphics g, int number, int y, int[] xToken)
 {
		y=y+50;
		g.setColor(Color.YELLOW);
		g.fillOval(xToken[number], y, 15, 15);
		g.setColor(Color.BLACK);
		g.fillRect(xToken[number]+5, y+5, 1, 1);
		g.fillRect(xToken[number]+10, y+5, 1, 1);
		g.drawArc(xToken[number]+4, y+6, 8, 4, 0, -180);
 }
 
 //moving token for the bottom strip
 public void tokenThree(Graphics g, int number, int y, int[] xToken)
 {
		y=y+50;
		g.setColor(Color.RED);
		g.fillRect(xToken[number]+18, y, 3, 12);
		g.setColor(Color.BLACK);
		g.fillRect(xToken[number]+17, y+12, 6, 6);
		g.drawRect(xToken[number]+18, y+1, 3, 12);
 }
 
 //moving token for the bottom strip
 public void tokenTwo(Graphics g, int number, int y, int[] xToken)
 {
		y=y+50;
		g.setColor(Color.YELLOW);
		g.fillOval(xToken[number], y+20, 7, 5);
		g.fillRect(xToken[number], y+24, 7, 7);
		g.fillOval(xToken[number]-3, y+29, 13, 7);
		g.setColor(Color.BLACK);
		g.fillRect(xToken[number]+2, y+25, 1, 1);
		g.fillRect(xToken[number]+4, y+25, 1, 1);
 }
 
 //moving token for the bottom strip
 public void tokenOne(Graphics g, int number, int y, int[] xToken)
 {
		y=y+50;
		g.setColor(DARKYELLOW);
		g.fillOval(xToken[number]+18,y+26,11,11);
		g.setColor(Color.WHITE);
		g.fillOval(xToken[number]+21, y+29, 5, 5);
		g.setColor(LIGHTBLUE);
		g.fillOval(xToken[number]+20, y+21, 7, 7);
 }
 
 //Initializing all the players with tokens
 public void players()
 {
		allPlayers[0] = new Player("1");
		allPlayers[1] = new Player("2");
		allPlayers[2] = new Player("3");
		allPlayers[3] = new Player("4");
 }

 
 //Initializing all the locations of the board class
 public void locationInit()
 {
		locations[0] = new CornerSquare(0,"GO");
		locations[1] = new Lot(1,"Mediterranean Ave.",60, mRent[1]);
		locations[2] = new CardSquare(2,"Community Chest");
		locations[3] = new Lot(3,"Baltic Ave.",60,mRent[3]);
		locations[4] = new TaxSquare(4, "Income Tax");
		locations[5] = new Railroad(5, "Reading Railroads", 200);
		locations[6] = new Lot(6,"Oriental Ave.",100,mRent[6]);
		locations[7] = new CardSquare(7,"Chance");
		locations[8] = new Lot(8,"Vermont Ave.",100,mRent[8]);
		locations[9] = new Lot(9,"Connecticut Ave.",120,mRent[9]);
		locations[10] = new CornerSquare(10,"JAIL");
		locations[11] = new Lot(11,"St. Charles Place",140,mRent[11]);
		locations[12] = new Utility(12, "Electric Company",150);
		locations[13] = new Lot(13,"States Ave.",140, mRent[13]);
		locations[14] = new Lot(14,"Virginia Ave.",160, mRent[14]);
		locations[15] = new Railroad(15, "Pennsylvania Railroad",200);
		locations[16] = new Lot(16,"St. James Place",180, mRent[16]);
		locations[17] = new CardSquare(17, "Community Chest");
		locations[18] = new Lot(18,"Tennesse Ave.",180, mRent[18]);
		locations[19] = new Lot(19,"New York Ave.",200, mRent[19]);
		locations[20] = new CornerSquare(20,"FREE PARKING");
		locations[21] = new Lot(21,"Kentucky Ave.",220, mRent[21]);
		locations[22] = new CardSquare(22, "Chance");
		locations[23] = new Lot(23,"Indiana Ave",220, mRent[23]);
		locations[24] = new Lot(24,"Illinois Ave.",240, mRent[24]);
		locations[25] = new Railroad(25,"B & O Railroad", 200);
		locations[26] = new Lot(26,"Atlantic Ave.",260, mRent[26]);
		locations[27] = new Lot(27,"Ventnor Ave.",260, mRent[27]);
		locations[28] = new Utility(28, "Water Works", 150);
		locations[29] = new Lot(29,"Marvin Gardens",280, mRent[29]);
		locations[30] = new CornerSquare(30,"GO TO JAIL");
		locations[31] = new Lot(31,"Pacific Ave.",300, mRent[31]);
		locations[32] = new Lot(32,"NO. Carolina Ave.",300, mRent[32]);
		locations[33] = new CardSquare(33,"Community Chest");
		locations[34] = new Lot(34,"Pennsylvania Ave.",320, mRent[34]);
		locations[35] = new Railroad(35,"Short Line Railroad",200);
		locations[36] = new CardSquare(36, "Chance");
		locations[37] = new Lot(37,"Park Place",350, mRent[37]);
		locations[38] = new TaxSquare(38, "Luxury Tax");
		locations[39] = new Lot(39,"Boardwalk",400, mRent[39] );
 }
}