//
// Programmer:  Fayaz Khan, Jonathan Galvan
// Assignment:  Project 4 - Final Project
// Date:        12/3/2015
// Description: This is the GUI class, and it handles the buttons, textboxes, JPanels
//				the GUI can be resized because of the use of BorderLayout and GridLayout
//				also when buttons are presses called our methods to the database to retrieve
//				the relevant data and then display in either a pop up or Text Area.
//              

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import javax.swing.*;
import java.sql.*;

public class GUI extends JApplet implements ActionListener, ItemListener
{
	
	static final String jdbc_Driver = "com.mysql.jdbc.Driver";			// JDBC Driver
	static final String url = "jdbc:mysql://localhost:3306/";			//database URL
	
	//Used to Query our database for individual drop down menus
	private static final String[] QUERY = {"CountryName", "LocalPrice",
			"DollarExchange","DollarPrice","DollarPPP", "DollarValuation"};	
	
	//Used for drop down menu for the User
	private static final String[] OPTIONS ={"Country","Local Price","Dollar ex","Dollar Price",
			 "Dollar PPP","Dollar Valuation"};
	
	static final String USER = "root"; 		//Credentials to the database
	static final String PASSWORD = "";
		
	private BackEnd localS = new BackEnd();		//An Instance of the BackEnd class
	private static Connection storage = null;		//Have the connection set to null 
	
	private JPanel base;            		// The first layer of the GUI		
	
	private JPanel bigMacPanel;				//Located to the north of GUI 
	private JLabel bigMacTitle;				//Title goes on the bigMacPanel and resizes		
	
	private JPanel centerPanel;				//contains the textArea to display results
	private JLabel centerNorthLabel;		//Labels of the individual columns of data
	private JTextArea centerTextBox;		//In the center of GUI displays ASC and DESC results
	private JScrollPane centerTextScroll;	//scroll to the textArea
	
	private JPanel southPanel;				//This contain a GridLayout two separate left and right
	
	private JPanel centerSouthPanel;		//contain a gridLayout composed of Labels,button and text
	private JButton insertCenter;			//button allows to insert data in to database
	private JTextField countryCenter;		//space to enter the country
	private JTextField localCenter;			//space to enter local value
	private JTextField exCenter;			//space to enter to exchange value
	private JTextField priceCenter;			//space to enter to country price
	private JTextField pppCenter;			//space to enter ppp value
	private JTextField valueCenter;			//space to enter exchange value 
	 
	private JLabel insertBlankLabel;		//Use for gridLayout space is used to occupy as label
	private JLabel countryCenterLabel;		//Above text box to label country
	private JLabel localCenterLabel;		//Above text box to label local
	private JLabel exCenterLabel;			//Above text box to label exchange
	private JLabel priceCenterLabel;		//Above text box to label price
	private JLabel pppCenterLabel;			//Above text box to label ppp
	private JLabel valueCenterLabel;		//Above text box to label value
	 
	private boolean countryCenterBool;		//if text in country available will be true else false
	private boolean localCenterBool;		//if text in local available will be true else false
	private boolean exCenterBool;			//if text in ex available will be true else false
	private boolean priceCenterBool;		//if text in price available will be true else false
	private boolean pppCenterBool;			//if text in ppp available will be true else false
	private boolean valueCenterBool;		//if text in value available will be true else false
	 
	private JPanel southLeft;				//contains a label, textbox and 2 buttons
	private JPanel southLeftCountryPanel;	//panel for resizing the label
	private JLabel southLeftCountryLabel;	//label to inform used for entering country 
	private JTextField southLeftCountry;	//User enters country to search or delete
	private JButton southLeftSearch;		//button to search for country
	private JButton southLeftDelete;		//button to seek and delete country 
	 
	private JPanel southRight;				//contains ComboBox,Panel and 5 buttons
	private JComboBox optionMenu;			//options to select Query from database
	private JPanel southRightCenter;		//contains a grid Layout
	private JButton southRightAsc;			//button to sort data by Ascending order 
	private JButton southRightDes;			//button to sort data by Descending order 
	private JButton southRightMax;			//button to find Max data 
	private JButton southRightMin;			//button to find Min data
	private JButton southRightAvg;			//button to find Average data
	private int optionSelect;				//to hold the selected index from JComboBox
	private String offset = "           "; //to make the result being displayed to look uniform
	 
	public void init()
	// POST: Initialize the GUI
	{
		
		
		storage = localS.getConnection(jdbc_Driver, url, USER, PASSWORD); //Connection to dataBase
		localS.createDataBase(storage);
		localS.insertDataBase(storage);
		
		base = new JPanel();					//first layer of the GUI
		setSize(800,500);             			//This is for the initial applet size
		base.setLayout(new BorderLayout());		//allow to work in regions and resizing
		bigMacPanel = new JPanel();				//Located to the north of GUI 
		bigMacPanel.setBackground(Color.YELLOW);//Color of Mcdonald's
		
		bigMacTitle = new JLabel("Big Mac Index of the WORLD");	//Goes on the bigMacPanel
		bigMacPanel.add(bigMacTitle);							//Located to the north of GUI 
		bigMacTitle.setFont(new Font("Serif", Font.BOLD, 30));	//Font to make it look attractive
		 
		 
		 centerPanel = new JPanel();				 //Center portion of the GUI 
		 centerPanel.setLayout(new BorderLayout()); //allow to work in regions and resizing
		 
		 //Labels for the our text Area
		 centerNorthLabel = new JLabel("Country         "
                             +" Local Price              "
                             + "Dollar ex               "
                             +"Dollar Price "+ "     Dollar PPP   " + "Dollar Valuation");
		 
		 centerNorthLabel.setFont(new Font("Serif", Font.BOLD, 15));//Font for above TextArea
		 optionSelect= 0;
		 
		 centerPanel.add(centerNorthLabel,BorderLayout.NORTH);	//Labels for the textArea
		 centerTextBox = new JTextArea(5,10);					//text area size
		 centerTextBox.setText("Your Results Shown Here :)");	//Initial text for text area
		 centerTextScroll = new JScrollPane(centerTextBox);		//allows text area to scroll 
		 centerTextBox.setEditable(false);						//not allowing textArea to e
		 
		 centerSouthPanel = new JPanel();					//Center South Panel to insert Data
		 centerSouthPanel.setLayout(new GridLayout(2,6));	//will include textField and button
		 centerSouthPanel.setBackground(Color.pink);
		 
		 
		 insertCenter = new JButton("Insert");				//Chunk will go centerSouthPanel
		 countryCenter = new JTextField("");  				//User enters country 
		 localCenter = new JTextField("");					//User enters local value
		 exCenter = new JTextField("");						//User enters exchange value
		 priceCenter = new JTextField("");					//User enters price value
		 pppCenter = new JTextField("");	 				//User enters ppp value
		 valueCenter = new JTextField("");					//User enter price exchange value
		 
		 insertCenter.addActionListener(this);				//ActionListeners to see if text present
		 countryCenter.addActionListener(this);				//ActionListeners to see if text present
		 localCenter.addActionListener(this);				//ActionListeners to see if text present
		 exCenter.addActionListener(this);					//ActionListeners to see if text present
		 priceCenter.addActionListener(this);				//ActionListeners to see if text present
		 pppCenter.addActionListener(this);					//ActionListeners to see if text present
		 valueCenter.addActionListener(this);				//ActionListeners to see if text present
		 
		 insertBlankLabel = new JLabel("");					//Labels to identify text boxes
		 countryCenterLabel = new JLabel(" Country");		//Labels to identify text boxes
		 localCenterLabel = new JLabel(" Local Price");		//Labels to identify text boxes
		 exCenterLabel = new JLabel(" Dollar ex");			//Labels to identify text boxes
		 priceCenterLabel = new JLabel(" Dollar Price");	//Labels to identify text boxes
		 pppCenterLabel = new JLabel(" Dollar PPP");		//Labels to identify text boxes
		 valueCenterLabel = new JLabel(" Dollar Valuation");//Labels to identify text boxes
		 
		 
		 countryCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));	//Font for labels
		 localCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));	//Font for labels
		 exCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));		//Font for labels
		 priceCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));	//Font for labels
		 pppCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));		//Font for labels
		 valueCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));	//Font for labels
		 
		 centerSouthPanel.add(insertBlankLabel);			//adding labels and text box to panels
		 centerSouthPanel.add(countryCenterLabel);			//adding labels and text box to panels
		 centerSouthPanel.add(localCenterLabel);			//adding labels and text box to panels
		 centerSouthPanel.add(exCenterLabel);				//adding labels and text box to panels
		 centerSouthPanel.add(priceCenterLabel);			//adding labels and text box to panels
		 centerSouthPanel.add(pppCenterLabel);				//adding labels and text box to panels
		 centerSouthPanel.add(valueCenterLabel);			//adding labels and text box to panels
		 centerSouthPanel.add(insertCenter);				//adding labels and text box to panels
		 centerSouthPanel.add(countryCenter);				//adding labels and text box to panels
		 centerSouthPanel.add(localCenter);					//adding labels and text box to panels
		 centerSouthPanel.add(exCenter);					//adding labels and text box to panels
		 centerSouthPanel.add(priceCenter);					//adding labels and text box to panels
		 centerSouthPanel.add(pppCenter);					//adding labels and text box to panels
		 centerSouthPanel.add(valueCenter);					//adding labels and text box to panels
		 
		 centerPanel.add(centerSouthPanel, BorderLayout.SOUTH); //putting all above on south Panel
		 
	
		 southPanel = new JPanel(); 						//The southPanel contains GridLayout
		 southPanel.setLayout(new GridLayout(0,2));			//contains two panels 
		 southLeft= new JPanel();							//new panels to have GridLayout
		 southLeft.setBackground(Color.MAGENTA);			//South Left region of GUI
		 southLeft.setLayout(new GridLayout(4,0));			//Contain Labels, textBox and buttons
		 
		 southLeftCountryPanel = new JPanel();				//This allows to resize 
		 southLeftCountryPanel.setBackground(Color.MAGENTA);//To blend in to other panel
		 southLeftCountryPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		 southLeftCountryLabel = new JLabel("Enter Country Below to Search or Delete");
		 southLeftCountryLabel.setFont(new Font("Serif", Font.BOLD, 15));
		 southLeftCountryPanel.add(southLeftCountryLabel);	//add all the above to panel
		 
		 southLeftCountry = new JTextField("");				//Allow user to enter Country
		 southLeftCountry.addActionListener(this);			//to see if User entered Text
		 southLeftSearch = new JButton("Search");			//Search for Country in database
		 southLeftDelete = new JButton("Delete");			//Delete country in database
		 
		 southLeftSearch.addActionListener(this);			//method to call database for search	
		 southLeftDelete.addActionListener(this);			//method to call database for Delete
		 
		 southLeft.add(southLeftCountryPanel);				//on the South left region of GUI
		 southLeft.add(southLeftCountry);					//on the South left region of GUI
		 southLeft.add(southLeftSearch);					//on the South left region of GUI
		 southLeft.add(southLeftDelete);					//on the South left region of GUI
		 	 
		 
		 
		 
		 southRight = new JPanel();							//on the South right panel 
		 southRight.setLayout(new BorderLayout());			//on the South right panel 
		 southRight.setBackground(Color.GREEN);				//on the South right panel 
		 optionMenu = new JComboBox(OPTIONS);				//User selects on what to QUERY
		 optionMenu.setMaximumRowCount(6);					//max row count
		 southRight.add(optionMenu, BorderLayout.NORTH);	//drop down menu is on the north of panel
		 
		 southRightCenter = new JPanel();					//south right center of panel
		 southRightCenter.setBackground(Color.green);		//south right center of panel
		 southRightCenter.setLayout(new GridLayout(2,2));	//contains buttons and drop down menu
	
		 southRightAsc = new JButton("Ascending");			//sort data in Ascending order 
		 southRightDes = new JButton("Descending");			//sort data in Descending order 
		 southRightMax = new JButton("Max");				//Retrieves max data
		 southRightMin = new JButton("Min");				//Retrieves min data
		 southRightAvg = new JButton("Average");			//Retrieves Average data
		 
		 southRightAsc.addActionListener(this);				//Action Listener to buttons
		 southRightDes.addActionListener(this);				//Action Listener to buttons
		 southRightMax.addActionListener(this);				//Action Listener to buttons
		 southRightMin.addActionListener(this);				//Action Listener to buttons
		 southRightAvg.addActionListener(this);				//Action Listener to buttons
		 
		 southRightCenter.add(southRightAsc);				//putting it all on south right center
		 southRightCenter.add(southRightDes);				//putting it all on south right center
		 southRightCenter.add(southRightMax);				//putting it all on south right center
		 southRightCenter.add(southRightMin);				//putting it all on south right center
		 southRight.add(southRightCenter,BorderLayout.CENTER);
		 southRight.add(southRightAvg, BorderLayout.SOUTH);
		 
		 
		 southPanel.add(southLeft);							//Putting all above panels together
		 southPanel.add(southRight);						//Putting all above panels together
		 
		 base.add(southPanel, BorderLayout.SOUTH);			//Putting all above panels together
		 centerPanel.add(centerTextScroll, BorderLayout.CENTER);
		 base.add(bigMacPanel, BorderLayout.NORTH);			//Putting all above panels together
		 base.add(centerPanel, BorderLayout.CENTER);		//Putting all above panels together
		 add(base);  
		 
		  
		 insertCenter.setEnabled(false);				//does not allow user to select till true
		 southLeftSearch.setEnabled(false);				//does not allow user to select till true
		 southLeftDelete.setEnabled(false);				//does not allow user to select till true
		 southRightMax.setEnabled(false);				//does not allow user to select till true
		 southRightMin.setEnabled(false);				//does not allow user to select till true
		 southRightAvg.setEnabled(false);				//does not allow user to select till true
		 
		 countryCenterBool = false;						//Used for inserting data till valid entered
		 localCenterBool = false;						//Used for inserting data till valid entered
		 exCenterBool = false;							//Used for inserting data till valid entered
		 priceCenterBool = false;						//Used for inserting data till valid entered
		 pppCenterBool = false;							//Used for inserting data till valid entered
		 valueCenterBool = false;						//Used for inserting data till valid entered
		 
		 optionMenu.addItemListener(this);
	}

	public void paint(Graphics g)
	{
		super.paint(g);	
	}
	
	@Override
	public void itemStateChanged(ItemEvent e)  
	// POST: Handles the button being visible or not visible 
	{
		
		if(e.getSource()== optionMenu)				//if on country allows buttons else all true
		{
			if(optionMenu.getSelectedIndex() == 0)
			{
				
				southRightAsc.setEnabled(true);
				southRightDes.setEnabled(true);
				southRightMax.setEnabled(false);
				southRightMin.setEnabled(false);
				southRightAvg.setEnabled(false);
			}
			else
			{
				southRightAsc.setEnabled(true);
				southRightDes.setEnabled(true);
				southRightMax.setEnabled(true);
				southRightMin.setEnabled(true);
				southRightAvg.setEnabled(true);
			}
			
			optionSelect = optionMenu.getSelectedIndex();		
		}
	}
	
	@Override
	public void actionPerformed(ActionEvent e) 
	// POST: Handles all actions performed on the GUI
	{
		
		if(e.getSource() == southLeftCountry)
		{
			southLeftSearch.setEnabled(true);
			southLeftDelete.setEnabled(true);
		}
		
		if(e.getSource() == countryCenter)
		{
			countryCenterBool = true;
		}	
		
		if(e.getSource() == localCenter)
		{
			try
			{
				Double.parseDouble(localCenter.getText());
				localCenterBool = true;
			}
			catch(Exception ex)
			{
				JOptionPane.showMessageDialog(null, "Please enter a value to Insert.");   
				localCenterBool = false;
			}
				
		}
		
		if(e.getSource() == exCenter)
		{
			try
			{
				Double.parseDouble(exCenter.getText());
				exCenterBool = true;
			}
			catch(Exception ex)
			{
				JOptionPane.showMessageDialog(null, "Please enter a value to Insert.");   
				exCenterBool = false;
			}
		}
		
		if(e.getSource() == priceCenter)
		{
			try
			{
				Double.parseDouble(priceCenter.getText());
				priceCenterBool = true;
			}
			catch(Exception ex)
			{
				JOptionPane.showMessageDialog(null, "Please enter a value to Insert.");   
				priceCenterBool = false;
			}
		}
		
		if(e.getSource() == pppCenter)
		{
			try
			{
				Double.parseDouble(pppCenter.getText());
				pppCenterBool = true;
			}
			catch(Exception ex)
			{
				JOptionPane.showMessageDialog(null, "Please enter a value to Insert.");   
				pppCenterBool = false;
			}
		}
		
		if(e.getSource() == valueCenter)
		{
			try
			{
				Double.parseDouble(valueCenter.getText());
				valueCenterBool = true;
			}
			catch(Exception ex)
			{
				JOptionPane.showMessageDialog(null, "Please enter a value to Insert.");   
				valueCenterBool = false;
			}
		}
		
		if(e.getSource() == southRightAsc)
		{
			String result;
			
			ResultSet rs = localS.sortQuaryByCommand(storage, QUERY[optionSelect], "ASC");

			centerTextBox.setText("");
			
			try 
			{
				while(rs.next()) 
				{
					
					result = rs.getString("CountryName") + offset + rs.getString("LocalPrice") + 
							offset + rs.getString("DollarExchange") + offset + 
							rs.getString("DollarPrice") + offset + rs.getString("DollarPPP") + 
							offset+ rs.getString("DollarValuation");

					centerTextBox.append(result +"\n");
				}
			} 
			catch (SQLException e1) 
			{
				e1.printStackTrace();
			}
			
			
			
		}
		
		if(e.getSource() == southRightDes)
		{
			String result;
			
			ResultSet rs = localS.sortQuaryByCommand(storage, QUERY[optionSelect], "DESC");

			centerTextBox.setText("");
			try 
			{
				while(rs.next()) 
				{
					
					result = rs.getString("CountryName") + offset + rs.getString("LocalPrice") + 
							offset + rs.getString("DollarExchange") + offset + 
							rs.getString("DollarPrice") + offset + rs.getString("DollarPPP") + 
							offset+ rs.getString("DollarValuation");

					centerTextBox.append(result +"\n");
				}
			} 
			catch (SQLException e1) 
			{
				e1.printStackTrace();
			}
			
			
			
		}
		
		if(e.getSource() == southRightMax)
		{
			
			String maxS = "Max";
			double tmp = 0.0;
			String result = null, resultTwo = null;
			
			
			ResultSet rs = localS.sortQuaryByM(storage, maxS,QUERY[optionSelect]);

			centerTextBox.setText("");
			
			try 
			{
				while(rs.next()) 
				{
					
					result = rs.getString("number");
					tmp = rs.getDouble("number");
				}
			} 
			catch (SQLException e1) 
			{
				e1.printStackTrace();
			}
			
			ResultSet two = localS.getCountryName(storage, QUERY[optionSelect], tmp);
			
			try
			{
				while(two.next()) 
				{
					resultTwo = two.getString("CountryName");
				}
				
			}
			catch(SQLException sl)
			{
				sl.printStackTrace();
			}
			
			JOptionPane.showMessageDialog(null,resultTwo +": " + result );	
		}
		
		if(e.getSource() == southRightMin)
		{
			String minS = "Min";
			double tmp = 0.0;
			String result = null, resultTwo = null;
			
			
			ResultSet rs = localS.sortQuaryByM(storage, minS,QUERY[optionSelect]);

			centerTextBox.setText("");
			
			try 
			{
				while(rs.next()) 
				{
					
					result = rs.getString("number");
					tmp = rs.getDouble("number");
				}
			} 
			catch (SQLException e1)
			{
				e1.printStackTrace();
			}
			
			ResultSet two = localS.getCountryName(storage, QUERY[optionSelect], tmp);
			
			try
			{
				while(two.next()) 
				{
					resultTwo = two.getString("CountryName");
				}
				
			}
			catch(SQLException sl) 
			{
				sl.printStackTrace();
			}
			
			JOptionPane.showMessageDialog(null,resultTwo +": " + result );
		}
		
		if(e.getSource() == southRightAvg)
		{
			
			String avgS = "Avg";
			String result = null;
			double alpha = 0.0;
			
			ResultSet rs = localS.sortQuaryByM(storage, avgS,QUERY[optionSelect]);

			centerTextBox.setText("");
			
			try 
			{
				while(rs.next()) 
				{
					result = rs.getString("number");		
				}
			} 
			catch (SQLException e1) 
			{
				e1.printStackTrace();
			}
			
			alpha = Double.parseDouble(result);
			
			JOptionPane.showMessageDialog(null,QUERY[optionSelect] +": " + String.format("%.2f", alpha));
			
		}
		
		if(e.getSource() == southLeftSearch)
		{
			
			String result;
			String country = southLeftCountry.getText();
	
			if( localS.checkCountry(storage, country) == true) 
			{

				ResultSet rs = localS.getInformationForCountry(storage, country);

				centerTextBox.setText("");
				try 
				{
					while(rs.next()) 
					{
						
						result = rs.getString("CountryName") + offset + rs.getString("LocalPrice") + 
								offset + rs.getString("DollarExchange") + offset + 
								rs.getString("DollarPrice") + offset + rs.getString("DollarPPP") + 
								offset+ rs.getString("DollarValuation");

						centerTextBox.append(result +"\n");
					}
				} 
				catch (SQLException e1) 
				{
					e1.printStackTrace();
				}					
				
				
			}
			else 
			{
				JOptionPane.showMessageDialog(null,"Country Does not exist");
			}

		}
		
		if(e.getSource() == southLeftDelete)
		{
			
			String country = southLeftCountry.getText();
	
			if( localS.checkCountry(storage, country) == true) {

				localS.delete(storage, country);
				JOptionPane.showMessageDialog(null, country + " successfully deleted");
					
			}
			else 
			{
				JOptionPane.showMessageDialog(null,"Country Does not exist");
			}

		}
		
		if(e.getSource()== insertCenter)
		{
			
			String a = countryCenter.getText();
			double b = Double.parseDouble(localCenter.getText());
			double c = Double.parseDouble(exCenter.getText());
			double d = Double.parseDouble(priceCenter.getText());
			double f = Double.parseDouble(pppCenter.getText());
			double g = Double.parseDouble(valueCenter.getText());
			
						
			
			if(localS.checkCountry(storage, a) == true) 
			{
				JOptionPane.showMessageDialog(null,"Country exists");				
			
			}
			else 
			{	
				localS.insert(storage, a, b, c, d, f, g);
				JOptionPane.showMessageDialog(null, a + " inserted into database");		
			}
			
		}
		
		if(countryCenterBool&&localCenterBool&&exCenterBool&&priceCenterBool&&pppCenterBool
				&&valueCenterBool)
		{
			insertCenter.setEnabled(true);
		}
		
		repaint();
	}
	
}