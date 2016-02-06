/**
 *  Programmer:   Jonathan Galvan, Fayaz Khan
 *  Assignment:   Final Project 
 *  Date:         12/03/15
 *  Description:  Back End Implementation for the DataBase. Contains all the methods for the
 *  			  front end GUI to retrieve and insert data.
 *
 */

import java.sql.*;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class BackEnd 
{
	public Connection getConnection(String driver, String url, String user, String password) 
	// PRE:  Valid driver, url, user, and password
	// POST: Returns a connection object
	{
	
		Connection myConnection = null;
		
		try 
		{
			Class.forName(driver).newInstance(); // Creates an instance of the driver for the database 
			myConnection = DriverManager.getConnection(url,user,password); // Connect to the DataBase
		}
		
		catch(Exception e) 
		{
			e.printStackTrace();
		}
		
		return myConnection;		
		
	}
	
	public void createDataBase(Connection a) 
	// PRE;  Valid connection object
	// POST: Creates the database and table 
	{
		
		Statement stt = null;
		
		try // Query the database
		{
			stt = a.createStatement();
		}
		
		catch(SQLException s) 
		{
			s.printStackTrace();
		}
		
		
		try // Create database if the name of the database does not exist
		{
			stt.execute("CREATE DATABASE IF NOT EXISTS BigMacIndex");
		} 
		
		catch (SQLException e) 
		{
			e.printStackTrace();
		}
		
		try  // Select database to utilize 
		{
			stt.execute("USE BigMacIndex");
		} 
		
		catch (SQLException e) 
		{
			e.printStackTrace();
		}
		
        try //Create an Information table
        {
			stt.execute("DROP TABLE IF EXISTS Information"); 
		} 
        
        catch (SQLException e) 
        {
			e.printStackTrace();
		}
                      
        try // Create an example table for BIGMAC INDEX 
        {
			stt.execute("CREATE TABLE Information(" 
			        + "CountryName VARCHAR(40),"
			        + "LocalPrice double,"
			        + "DollarExchange double,"
			        + "DollarPrice double,"
			        + "DollarPPP double,"
			        + "DollarValuation float,"
			        + "PRIMARY KEY(CountryName)"
			        + ")");
		} 
        
        catch (SQLException e) 
        {
			e.printStackTrace();
		}		
			
    	try // Close Statement
    	{
			if(stt != null) 
			{
				stt.close();
			}
		}
			
		catch (SQLException e) 
    	{
			e.printStackTrace();
		}        
        
		
	}
	
	public void insertDataBase(Connection a) 
	// PRE:  Valid connection object
	// POST: Inserts all the information from the source to the database
	{
		
		Statement stt = null;
		
		
		try // Query the database
		{
			stt = a.createStatement();
		} 
		
		catch (SQLException e1) 
		{
			
			e1.printStackTrace();
		}
		
		Scanner sc = null;		
			
		
		File name = new File("/Users/fayazkhanfay_gmail_com/Desktop/latestData.txt"); // File is directed to the path that contains the actual data 
		
		
		try // Checks to see if we can create a new scanner object with the given file 
		{
			sc = new Scanner(name);		
		}
		
		catch(FileNotFoundException e)  
		{
			e.printStackTrace();			
		}
		
		
		sc.nextLine();
		
		while(sc.hasNext()) 
		{
			
			String countryName = sc.next();
			double localPrice = sc.nextDouble();
			double dollarExchange = sc.nextDouble();
			double dollarPrice = sc.nextDouble();
			double dollarPPP = sc.nextDouble();
			double impliedDollarValuation = sc.nextFloat();
		          
			
			try // Insert data into database one by one  
			{
				stt.execute(String.format("INSERT INTO Information (CountryName, LocalPrice, DollarExchange, DollarPrice, DollarPPP, DollarValuation)"+
						" VALUES ('%s', %.2f, %.2f, %.2f, %.2f, %.2f)", countryName, localPrice, dollarExchange, dollarPrice, dollarPPP, impliedDollarValuation));
			} 
			
			catch (SQLException e) 
			{
				
				e.printStackTrace();
			}    			
			
		}		
		
			
		
		try // Close the Scanner and Statement objects 
		{
			
			if(sc != null) 
			{
				sc.close();
			}			
		}
		
		catch (Exception e) 
		{
			e.printStackTrace();
		}
		
		
		try  // Close statement connection
		{
			
			if(stt != null) 
			{
				stt.close();
			}
		}
			
		catch (SQLException e) 
		{
			e.printStackTrace();
		}
		
	}
	
	
	
	
	public ResultSet sortQuaryByCommand(Connection a, String category, String command) 
	// PRE: Valid connection object along with category and command not being null 
	// POST:Returns a ResultSet object that contains the query to ASC or Desc the data based on the column name
	{
		
		Statement stt = null;
		ResultSet rs = null;
		
		
		try // Query database
		{
			stt = a.createStatement();
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
		try // Execute query 
		{
			rs = stt.executeQuery(String.format("SELECT * FROM Information " +
								  "Order By %s %s", category,command)); 
		}
		
		catch(SQLException sl)  
		{
			sl.printStackTrace();
		}
		
		return rs;

	}
	
	public ResultSet sortQuaryByM(Connection a, String computation, String columnName) 
	// PRE:  Valid connection object along with computation and columname not being null
	// POST: Returns a ResultSet object that computes AVG, MIN, MAX based on computation and columname
	{
				
		Statement stt = null;
		ResultSet rs = null;
		
		
		try // Query the database 
		{
			stt = a.createStatement();
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
		try // Execute query 
		{
			rs = stt.executeQuery(String.format("Select %s(%s) as number From Information", computation, columnName));

		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
					
		return rs;
	}
	
	
	public ResultSet getCountryName(Connection a, String column, double number)
	// PRO:  Valid connection object, column not equal to null, and number not being null 
	// POST: Returns a Resultset object that contains information based on the CountryName
	{
		
		Statement stt = null;
		ResultSet rs = null;
		
		
		try  // Query the database
		{
			stt = a.createStatement();
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
		try  // Execute query
		{
			rs = stt.executeQuery(String.format("Select CountryName From Information " +
												"Where %s = %f", column, number));
		}
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
						
		return rs;
	}
	
	
	public ResultSet getInformationForCountry(Connection a, String input) 
	// PRE:  Valid connection object, and input not being null
	// POST: Returns a ResultSet object that retrieves all the information from the table based on the inputed string from the user
	{
			
		int i;
		String formatted;
		int length = input.length();
		
		char [] st = input.toCharArray(); // Turns the string into a char array
		char [] md = new char[length];
		
		Statement stt = null;
		ResultSet rs = null;
		
		for(i = 0; i < length; i++) 
		{
			
			if(st[i] == ' ') 
			{
				md[i] = '_';
			}
			
			else 
			{
				md[i] = st[i];
			}	
		}
		
		
		formatted = new String(md); // Initialized the string with the new formatted string
		
		
		try // Query the database
		{
			stt = a.createStatement();
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
		try  // Execute query
		{
			
			rs = stt.executeQuery(String.format("Select * From Information " +
											    "Where CountryName = '%s'", formatted));
		}
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
				
		return rs;
	}
	
	// Method that inserts into the database
	public void insert(Connection a, String countryName, double localPrice, double dollarExchange, double dollarPrice, double dollarPPP, double impliedDollarValuation) 
	// PRE:  Valid connection object, countryName not being null and liocalPrice, dollarExchange, dollarPrice, dollarPPP, and ImpliedValuation != null
	// POST: Inserts the data information presented into the database
	{
		
		
		int i;
		String formatted;
		int length = countryName.length();
		
		char [] st = countryName.toCharArray(); // Turns the string into a char array
		char [] md = new char[length];
		
		Statement stt = null;
		
		for(i = 0; i < length; i++) 
		{
			
			if(st[i] == ' ') 
			{
				md[i] = '_';
			}
			
			else 
			{
				md[i] = st[i];
			}	
		}
		
		formatted = new String(md); // Initialized the string with the new formatted string
		
		
		try // Query the database 
		{
			stt = a.createStatement();
		}
		
		catch(SQLException sl)  
		{
			sl.printStackTrace();
		}
		
		
		try // Inserts into the Information Table
		{
			stt.execute(String.format("INSERT INTO Information (CountryName, LocalPrice, DollarExchange, DollarPrice, DollarPPP, DollarValuation)"+
					" VALUES ('%s', %.2f, %.2f, %.2f, %.2f, %.2f)", formatted, localPrice, dollarExchange, dollarPrice, dollarPPP, impliedDollarValuation));
		}
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
		try // Closes statement connection 
		{
			if(stt != null) 
			{
				stt.close();
			}
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
	}
	
	public void delete(Connection a, String countryName) 
	// PRE: Valid Connection object, and countryName not equal to null
	// POST: Deletes the data from the information table located in the datanbase 
	{
		
		int i;
		String formatted;
		
		int length = countryName.length(); // Retrieves the length of the countryName string
		
		char [] st = countryName.toCharArray(); // Turns the string into a char array/. Turns the string into a char array
		char [] md = new char[length];
		
		Statement stt = null;
		
		for(i = 0; i < length; i++) 
		{
			
			if(st[i] == ' ') 
			{
				md[i] = '_';
			}
			
			else 
			{
				md[i] = st[i];
			}	
		}
		
		
		formatted = new String(md); // Initialized the string with the new formatted string
		
		try // Query the database 
		{
			stt = a.createStatement();
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
		try // Deletes the desired table from Information
		{
			stt.execute(String.format("Delete From Information " +
									  "Where countryName = '%s'", formatted));
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
		try // Closes statement Connection 
		{
			if(stt != null) 
			{
				stt.close();
			}
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
	}	
	
	public boolean checkCountry(Connection a, String input) 
	// PRE:  Valid connection type and input not being null
	// POST: Returns a boolean that returns true or false based on the country name in the data set
	{
		

		int i;
		String formatted;
		
		int length = input.length(); // Retrieves the length of the countryName string
		
		
		char [] st = input.toCharArray(); // Turns the string into a char array
		char [] md = new char[length];
		
		Statement stt = null;
		ResultSet rs = null;
		
		for(i = 0; i < length; i++) 
		{
			
			if(st[i] == ' ') 
			{
				md[i] = '_';
			}
			
			else 
			{
				md[i] = st[i];
			}	
		}
		
		formatted = new String(md); // Initialized the string with the new formatted string
		
		
		try // Query the database
		{
			stt = a.createStatement();
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
		try // Execute Query
		{
			rs = stt.executeQuery(String.format("Select CountryName From Information " +
											    "Where CountryName = '%s'", formatted));
		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		
		try /// Check if the name exists, if so return true
		{
			while(rs.next()) 
			{				
				return true;
			}

		}
		
		catch(SQLException sl) 
		{
			sl.printStackTrace();
		}
		
		return false; // Data does not exist in the database
	}
}