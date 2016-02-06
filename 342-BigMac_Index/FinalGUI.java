import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.color.*;

import javax.swing.*;
import java.sql.*;

public class FinalGUI extends JApplet implements ActionListener, ItemListener
{
	// JDBC Driver and database URL
	static final String jdbc_Driver = "com.mysql.jdbc.Driver";
	static final String url = "jdbc:mysql://localhost:3306/";
	private static final String[] QUERY = {"CountryName", "LocalPrice","DollarExchange","DollarPrice",
			"DollarPPP", "DollarValuation"};	
	
	// Credentials for the database 
	static final String user = "root"; 
	static final String password = "";
		
	private BackEnd y = new BackEnd();
	private static Connection x = null;
	
	private String offset = "                ";
	
	
	//BorderLayout base;                // base is the base layout for all the GUI
	private JPanel base;            // bottom is the bottom panel of the GUI and 
    //    contains controls
	 private JPanel bottomRight;       // bottomRight panel contains the newsFeed section
	 private FlowLayout layout;
	 
	 private JTextArea feedContents;
	 private JScrollPane feedPane;

	 private JLabel bigMacTitle;
	 private JPanel bigMacPanel;
	 
	 private JPanel centerNorth;
	 private JPanel centerPanel;
	 private JLabel centerNorthLabel;
	 private JLabel centerDollar;
	 
	 
	 
	 private JPanel southPanel;
	 private JLabel centerLabel;
	 private JTextArea centerTextBox;
	 private JScrollPane centerTextScroll;// THIS IS FOR THE SCROLL, NOT YET IMPLEMENTED 
	 
	 private JPanel centerSouthPanel;
	 
	 private JButton insertCenter;
	 
	 private JTextField countryCenter;
	 private JTextField localCenter;
	 private JTextField exCenter;
	 private JTextField priceCenter;
	 private JTextField pppCenter;
	 private JTextField valueCenter;
	 
	 private JLabel insertBlankLabel;
	 private JLabel countryCenterLabel;
	 private JLabel localCenterLabel;
	 private JLabel exCenterLabel;
	 private JLabel priceCenterLabel;
	 private JLabel pppCenterLabel;
	 private JLabel valueCenterLabel;
	 
	 private boolean countryCenterBool;
	 private boolean localCenterBool;
	 private boolean exCenterBool;
	 private boolean priceCenterBool;
	 private boolean pppCenterBool;
	 private boolean valueCenterBool;
	 
	 private JPanel southLeft;
	 private JPanel southRight;

	 private JPanel southLeftCountryPanel;
	 private JLabel southLeftCountryLabel;
	 private JTextField southLeftCountry;
	 private JButton southLeftSearch;
	 private JButton southLeftDelete;
	 
	 private JPanel southLeftCenter;
	 
	 private static final String[] OPTIONS ={"Country","Local Price","Dollar ex","Dollar Price","Dollar PPP","Dollar Valuation"};
	 private JComboBox optionMenu;
	 private JPanel southRightCenter;
	 private JButton southRightAsc;
	 private JButton southRightDes;
	 private JButton southRightMax;
	 private JButton southRightMin;
	 private JButton southRightAvg;
	 private int optionSelect;
	 
	 
	public void init()
	{
		
		
		x = y.getConnection(jdbc_Driver, url, user, password);
		
		y.createDataBase(x);
		y.insertDataBase(x);
		 optionSelect= 0;
		 base = new JPanel();					//first layer 
		 setSize(800,500);             			//This is for the initial applet size
		 base.setBackground(Color.BLUE);
		 base.setLayout(new BorderLayout());
		 bigMacPanel = new JPanel();
		
		 bigMacPanel.setBackground(Color.YELLOW);
		 
		 bigMacTitle = new JLabel("Big Mac Index of the WORLD");		//Goes on the bigMacPanel
		 bigMacPanel.add(bigMacTitle);
		 
		 bigMacTitle.setFont(new Font("Serif", Font.BOLD, 30));
		 
		 /*BELOW IS FOR CENTER PORTION OF GUI-----------*/
		 centerPanel = new JPanel();
		 centerPanel.setLayout(new BorderLayout());
		 centerNorthLabel = new JLabel("Country         "
                             +" Local Price              "
                             + "Dollar ex               "
                             +"Dollar Price "+ "     Dollar PPP   " + "Dollar Valuation");
		 centerNorthLabel.setFont(new Font("Serif", Font.BOLD, 15));

		 centerPanel.add(centerNorthLabel,BorderLayout.NORTH);
		
		 centerTextBox = new JTextArea(5,10);
		 centerTextBox.setText("Your Results Shown Here :)");
		 
		 
		 // THIS IS FOR THE SCROLL, NOT YET IMPLEMENTED 
		 centerTextScroll = new JScrollPane(centerTextBox);
		 //add(centerTextScroll);
		 centerTextBox.setEditable(false);
		 
		 
		 /*ABOVE IS FOR CENTER PORTION OF GUI-----------*/
		 
		 /*Below is for the insert in GUI FOR CENTER SOUTH*/
		 centerSouthPanel = new JPanel();
		 centerSouthPanel.setLayout(new GridLayout(2,6));
		 centerSouthPanel.setBackground(Color.pink);
		 
		 
		 insertCenter = new JButton("Insert");
		 countryCenter = new JTextField("");  	//Country 
		 localCenter = new JTextField("");		//local
		 exCenter = new JTextField("");		//ex
		 priceCenter = new JTextField("");		//price
		 pppCenter = new JTextField("");	 	//ppp
		 valueCenter = new JTextField("");		//value
		 
		 insertCenter.addActionListener(this);
		 countryCenter.addActionListener(this);
		 localCenter.addActionListener(this);
		 exCenter.addActionListener(this);
		 priceCenter.addActionListener(this);
		 pppCenter.addActionListener(this);
		 valueCenter.addActionListener(this);
		 
		 insertBlankLabel = new JLabel("");
		 countryCenterLabel = new JLabel(" Country");
		 countryCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));
		 localCenterLabel = new JLabel(" Local Price");
		 localCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));
		 exCenterLabel = new JLabel(" Dollar ex");
		 exCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));
		 priceCenterLabel = new JLabel(" Dollar Price");
		 priceCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));
		 pppCenterLabel = new JLabel(" Dollar PPP");
		 pppCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));
		 valueCenterLabel = new JLabel(" Dollar Valuation");
		 valueCenterLabel.setFont(new Font("Serif", Font.BOLD, 15));
		 
		 centerSouthPanel.add(insertBlankLabel);
		 centerSouthPanel.add(countryCenterLabel);
		 centerSouthPanel.add(localCenterLabel);
		 centerSouthPanel.add(exCenterLabel);
		 centerSouthPanel.add(priceCenterLabel);
		 centerSouthPanel.add(pppCenterLabel);
		 centerSouthPanel.add(valueCenterLabel);
		 centerSouthPanel.add(insertCenter);
		 centerSouthPanel.add(countryCenter);
		 centerSouthPanel.add(localCenter);
		 centerSouthPanel.add(exCenter);
		 centerSouthPanel.add(priceCenter);
		 centerSouthPanel.add(pppCenter);
		 centerSouthPanel.add(valueCenter);
		 
		  centerPanel.add(centerSouthPanel, BorderLayout.SOUTH);
		 
		 /*------------ABOVEis for the insert in GUI FOR CENTER SOUTH*/
		 /*-----------------------------------ABOVE IS FOR CENTER PORTION OF GUI */
		 
		 /*Below is South Left Panel*/
		 southPanel = new JPanel(); 
		 southPanel.setLayout(new GridLayout(0,2));
		 southLeft= new JPanel();
		 southLeft.setBackground(Color.MAGENTA);
		 southLeft.setLayout(new GridLayout(4,0));
		 
		 southLeftCountryPanel = new JPanel();
		 southLeftCountryPanel.setBackground(Color.MAGENTA);
		 southLeftCountryPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		 southLeftCountryLabel = new JLabel("Enter Country Below to Search or Delete");
		 southLeftCountryLabel.setFont(new Font("Serif", Font.BOLD, 15));
		 southLeftCountryPanel.add(southLeftCountryLabel);
		 
		 southLeftCountry = new JTextField("");			//Enter Country
		 southLeftCountry.addActionListener(this);
		 southLeftSearch = new JButton("Search");
		 southLeftDelete = new JButton("Delete");
		 
		 southLeftSearch.addActionListener(this);
		 southLeftDelete.addActionListener(this);
		 
		 southLeft.add(southLeftCountryPanel);
		 southLeft.add(southLeftCountry);
		 southLeft.add(southLeftSearch);
		 southLeft.add(southLeftDelete);
		 	 
		 /*-------ABOVE is South Left Panel*/
		 
		 
		 /*BELOW IS SOUTH RIHGT PANEL---------------*/
		 southRight = new JPanel();
		 southRight.setLayout(new BorderLayout());
		 southRight.setBackground(Color.GREEN);
		 optionMenu = new JComboBox(OPTIONS);
		 optionMenu.setMaximumRowCount(6);
		 southRight.add(optionMenu, BorderLayout.NORTH);
		 
		 southRightCenter = new JPanel();
		 southRightCenter.setBackground(Color.green);
		 southRightCenter.setLayout(new GridLayout(2,2));
	
		 southRightAsc = new JButton("Ascending");
		 southRightDes = new JButton("Descending");
		 southRightMax = new JButton("Max");
		 southRightMin = new JButton("Min");
		 southRightAvg = new JButton("Average");
		 
		 southRightAsc.addActionListener(this);
		 southRightDes.addActionListener(this);
		 southRightMax.addActionListener(this);
		 southRightMin.addActionListener(this);
		 southRightAvg.addActionListener(this);
		 
		 southRightCenter.add(southRightAsc);
		 southRightCenter.add(southRightDes);
		 southRightCenter.add(southRightMax);
		 southRightCenter.add(southRightMin);
		 southRight.add(southRightCenter,BorderLayout.CENTER);
		 southRight.add(southRightAvg, BorderLayout.SOUTH);
		 
		 
		 /*ABOVE IS South Right Panel*/
		 southPanel.add(southLeft);
		 southPanel.add(southRight);
		 
		 base.add(southPanel, BorderLayout.SOUTH);
		 centerPanel.add(centerTextScroll, BorderLayout.CENTER);
		 base.add(bigMacPanel, BorderLayout.NORTH);
		 base.add(centerPanel, BorderLayout.CENTER);
		 add(base);  
		 
		  
		 insertCenter.setEnabled(false);
		 southLeftSearch.setEnabled(false);
		 southLeftDelete.setEnabled(false);
		 southRightMax.setEnabled(false);
		 southRightMin.setEnabled(false);
		 southRightAvg.setEnabled(false);
		 
		 countryCenterBool = false;
		 localCenterBool = false;
		 exCenterBool = false;
		 priceCenterBool = false;
		 pppCenterBool = false;
		 valueCenterBool = false;
		 
		 optionMenu.addItemListener(this);
	}

	public void paint(Graphics g)
	{
		super.paint(g);
		
		
	}
	
	@Override
	public void itemStateChanged(ItemEvent e)  
	{
		
		if(e.getSource()== optionMenu)
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
	{
		/*
		localCenter.getText();
		exCenter.getText();
		priceCenter.getText();
		pppCenter.getText();
		valueCenter.getText();*/
		
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
			//JOptionPane.showMessageDialog(null,"this works");
			String result;
			
			ResultSet rs = y.sortQuaryByCommand(x, QUERY[optionSelect], "ASC");

			centerTextBox.setText("");
			try {
				while(rs.next()) {
					
					result = rs.getString("CountryName") + offset + rs.getString("LocalPrice") + 
							offset + rs.getString("DollarExchange") + offset + 
							rs.getString("DollarPrice") + offset + rs.getString("DollarPPP") + offset+ rs.getString("DollarValuation");
					//centerTextBox.setText(result);
					centerTextBox.append(result +"\n");
				}
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			
			
			
		}
		
		if(e.getSource() == southRightDes)
		{
			//JOptionPane.showMessageDialog(null,"this works");
			String result;
			
			ResultSet rs = y.sortQuaryByCommand(x, QUERY[optionSelect], "DESC");

			centerTextBox.setText("");
			try {
				while(rs.next()) {
					
					result = rs.getString("CountryName") + offset + rs.getString("LocalPrice") + 
							offset + rs.getString("DollarExchange") + offset + 
							rs.getString("DollarPrice") + offset + rs.getString("DollarPPP") + offset+ rs.getString("DollarValuation");
					//centerTextBox.setText(result);
					centerTextBox.append(result +"\n");
				}
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			
			
			
		}
		
		if(e.getSource() == southRightMax)
		{
			
			//JOptionPane.showMessageDialog(null,"this works");
			String maxS = "Max";
			double tmp = 0.0;
			String result = null, resultTwo = null;
			
			
			ResultSet rs = y.sortQuaryByM(x, maxS,QUERY[optionSelect]);

			centerTextBox.setText("");
			
			try {
				while(rs.next()) {
					
					result = rs.getString("number");
					tmp = rs.getDouble("number");
					//centerTextBox.setText(result);
					//centerTextBox.append(result +"\n");
				}
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			
			ResultSet two = y.getCountryName(x, QUERY[optionSelect], tmp);
			
			try{
				while(two.next()) {
					resultTwo = two.getString("CountryName");
				}
				
			}
			catch(SQLException sl) {
				sl.printStackTrace();
			}
			
			JOptionPane.showMessageDialog(null,resultTwo +": " + result );
			
			
			
		}
		
		if(e.getSource() == southRightMin)
		{
			
			//JOptionPane.showMessageDialog(null,"this works");
			String minS = "Min";
			double tmp = 0.0;
			String result = null, resultTwo = null;
			
			
			ResultSet rs = y.sortQuaryByM(x, minS,QUERY[optionSelect]);

			centerTextBox.setText("");
			
			try {
				while(rs.next()) {
					
					result = rs.getString("number");
					tmp = rs.getDouble("number");
					//centerTextBox.setText(result);
					//centerTextBox.append(result +"\n");
				}
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			
			ResultSet two = y.getCountryName(x, QUERY[optionSelect], tmp);
			
			try{
				while(two.next()) {
					resultTwo = two.getString("CountryName");
				}
				
			}
			catch(SQLException sl) {
				sl.printStackTrace();
			}
			
			JOptionPane.showMessageDialog(null,resultTwo +": " + result );
			
			
			
		}
		
		if(e.getSource() == southRightAvg)
		{
			
			//JOptionPane.showMessageDialog(null,"this works");
			String avgS = "Avg";
			String result = null;
			double alpha = 0.0;
			
			ResultSet rs = y.sortQuaryByM(x, avgS,QUERY[optionSelect]);

			centerTextBox.setText("");
			
			try {
				while(rs.next()) {
					
					result = rs.getString("number");		
				}
			} catch (SQLException e1) {
				e1.printStackTrace();
			}
			
			alpha = Double.parseDouble(result);
			
			JOptionPane.showMessageDialog(null,QUERY[optionSelect] +": " + String.format("%.2f", alpha));
			
			
			
		}
		
		if(e.getSource() == southLeftSearch)
		{
			int i;
			String result;
			String country = southLeftCountry.getText();
	
			if( y.checkCountry(x, country) == true) {

				ResultSet rs = y.getInformationForCountry(x, country);

				centerTextBox.setText("");
				try {
					while(rs.next()) {
						
						result = rs.getString("CountryName") + offset + rs.getString("LocalPrice") + 
								offset + rs.getString("DollarExchange") + offset + 
								rs.getString("DollarPrice") + offset + rs.getString("DollarPPP") + offset+ rs.getString("DollarValuation");
						//centerTextBox.setText(result);
						centerTextBox.append(result +"\n");
					}
				} 
				
				catch (SQLException e1) {
					e1.printStackTrace();
				}					
				
				
			}
			
			else {
				JOptionPane.showMessageDialog(null,"Country Does not exist");
			}

		}
		
		if(e.getSource() == southLeftDelete)
		{
			int i;
			String result;
			String country = southLeftCountry.getText();
	
			if( y.checkCountry(x, country) == true) {

				y.delete(x, country);
				JOptionPane.showMessageDialog(null, country + " successfully deleted");
					
			}
			
			else {
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
			
						
			
			if(y.checkCountry(x, a) == true) {
				
				JOptionPane.showMessageDialog(null,"Country exists");				
			
			}
					
			
			else {
				
				y.insert(x, a, b, c, d, f, g);
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
