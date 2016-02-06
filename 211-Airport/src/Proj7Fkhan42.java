import java.io.*;
import java.util.*;
import java.util.Scanner;//for the File open 


public class Proj7Fkhan42
{
	public static Airport [] air;//putting it here so it communitcates with everythinh
	public static Airport [] linkfile;//array of 1 to store link list of filenames
 public static void main (String[] args)
 {
	 Proj7Fkhan42 airportData = new Proj7Fkhan42();
	   
	   airportData.initialize();
	   String fileN = "proj7data2.txt";
	   
	 File f = new File(fileN);
	 Scanner sc = null; 
	 
	 try
	 {
		sc = new Scanner(f);
	 }
	 catch(FileNotFoundException fnfe)
	 {
		 System.out.println("File does not exist");
		 return;
	 }
	 
	 linkfile = new Airport[1];
	 linkfile[0]= new Airport(0);
	 
	 linkfile[0].link(fileN);
	 
   airportData.processCommandLoop (sc);
   
   System.out.println ("Goodbye");
 }
   
   
  public void processCommandLoop (Scanner sc)//provided by Prof.Troy
  {
   // loop until all integers are read from the file
   while (sc.hasNext())
   {
     String command = sc.next();
     System.out.println ("*" + command + "*");
     
     if (command.equals("q") == true)
       System.exit(1);
     
     else if (command.equals("?") == true)
       showCommands();
     
     else if (command.equals("t") == true)
       doTravel(sc);
     
     else if (command.equals("r") == true)
       doResize(sc);

     else if (command.equals("i") == true)
       doInsert(sc);

     else if (command.equals("d") == true)
       doDelete(sc);

     else if (command.equals("l") == true)
       doList(sc);

     else if (command.equals("f") == true)
       doFile(sc);

     else if (command.equals("#") == true)
       ;
     
     else
       System.out.println ("Command is not known: " + command);
     
     if(sc.hasNextLine())//this was messing up with proj7data2.txt and 3. I added this to check if nextline exists
    	 sc.nextLine();

   }

 }
 
  /*this is to get things started because some text files dont start with r 
   * 	so the resize function will not be called forced to create one before just in case*/
  public void initialize()
  {
	  int startSize= 10; // random number specified by Prof.Troy
	  air = new Airport[startSize];
	  
	  int i =1;
	  while (i<startSize)
	  {
		  air[i] = new Airport(i);
		  i++;
	  }
	  
  }
  
 public void showCommands()//provided by Prof.Troy
 {
   System.out.println ("The commands for this project are:");
   System.out.println ("  q ");
   System.out.println ("  ? ");
   System.out.println ("  # ");
   System.out.println ("  t <int1> <int2> ");
   System.out.println ("  r <int> ");
   System.out.println ("  i <int1> <int2> ");
   System.out.println ("  d <int1> <int2> ");
   System.out.println ("  l ");
   System.out.println ("  f <filename> ");
 }
 
 public void doTravel(Scanner sc)//all this provided by Prof.Troy expect for the method call on bottom
 {
	 /*
	  * All this really does it grabs legal values for depthFirstSearchHelpe method
	  * depthFirstSearchHelpe does all the work*/
   int val1 = 0;
   int val2 = 0;
   
   if ( sc.hasNextInt() == true )
     val1 = sc.nextInt();
   else
   {
     System.out.println ("Integer value expected");
     return;
   }
   
   if ( sc.hasNextInt() == true )
     val2 = sc.nextInt();
   else
   {
     System.out.println ("Integer value expected");
     return;
   }
   
   System.out.println ("Performing the Travel Command from " + val1 +
                       " to " + val2);
   
   depthFirstSearchHelper(val1,val2);
   

 }
 
 public void doResize(Scanner sc)
 {
   int val1 = 0;
   int i =1;
  
   if ( sc.hasNextInt() == true )//this checks if int is available but does not take value 
   {
	   /*I added the 1 to val1 because in the text file it would refer to airport that was on the 
	    * 	border but would seg fault and we are ignoring index 0 */
     val1 = sc.nextInt()+ 1 ;//nextInt is a library that takes value from .txt and now is val1
     if(val1>0)
     {
    	 air = new Airport[val1];//we are creating an array but nothing is in the array 
    	 while(i<val1)
    	 {
    		 air[i] = new Airport(i);// we are putting object into the array and putting in i as airport #
    		 i++;
    	 }
     }
     else
     {
    	 System.out.println("Resize has to be greater than 0");
    	 return;
     }
   }
   else
   {
     System.out.println ("Integer value expected");
     return;
   }
   
 
    System.out.println ("Performing the Resize Command with " + (val1-1) );
 

 }
 
 public void doInsert(Scanner sc)
 {
	 int airport;
	 int connectAirport;
	 if(sc.hasNextInt()==true)
	 {
		 airport = sc.nextInt();
		 if(sc.hasNextInt()==true&& airport>0 && airport< air.length)//check within range of array
		 {
			 connectAirport = sc.nextInt();// grabs int from .txt 
			 if(connectAirport<1 || connectAirport>= air.length)//checks withing range
			 {
				 System.out.println ("connectAirport does not exist");
				 return;
			 }
			 
			 
			 /*Adding node here pending if null or not*/
			 if(air[airport].getHead()==1)//check if null 
				 air[airport].link(connectAirport);//if null just connect to the array by linking it 
			 else
			 {
				 air[airport].push(connectAirport);// not null we push in front of the link list 
			 }
		 }
		 else
		 {
			 System.out.println ("Integer value expected or airport does not exist");
			 return;
		 }
		 
		 
		 
		 
	 }
	 else
	 {
		 System.out.println ("Integer value expected");
		 return;
	 }
 }
 
 public void doDelete(Scanner sc)//Similiar notes to doInsert()
 {
	 int airport;
	 int connectAirport;
	 if(sc.hasNextInt()==true)
	 {
		 airport = sc.nextInt();
		 if(sc.hasNextInt()==true&& airport>0 && airport< air.length)
		 {
			 connectAirport = sc.nextInt();
			 if(connectAirport<1 || connectAirport>= air.length)
			 {
				 System.out.println ("connectAirport does not exist");
				 return;
			 }
			 
			 
			 
			 /*Adding node here pending if null or not*/
			
			 if(air[airport].getHead()==1)
				System.out.println("No outbound flight from " + airport );
			 else
			 {
				 air[airport].delTraverse(connectAirport);
			 }
		 }
		 else
		 {
			 System.out.println ("Integer value expected or airport does not exist");
			 return;
		 }
		 
		 
		 
		 
	 }
	 else
	 {
		 System.out.println ("Integer value expected");
		 return;
	 }
	 
	 
 }
 
 public void depthFirstSearchHelper(int x , int y)//provided by Prof.Troy
 {
	 airportMarkUnvisited();//goes through air[] and set everything to false
	 if(dfs(x,y)== true)// method is below for notes 
		 System.out.println("You can get from airport " + x + " to airport " + y + " in one or more flights");
	 else
		 System.out.println("You can NOT get from airport " + x + " to airport " + y + " in one or more flights");
 }

 public boolean dfs(int a , int b )//outline provided by Prof.Troy
 {
	 /*This is done recursivelly 
	  * in returnUnvisit is am sending the array just to reference if the airport has 
	  * been visited because in Airport method i cant refernce another index. so I sent
	  * the whole array in as paramater but only as a copy\
	  * 
	  * the -999 if traverse through all nodes and hits null it will return -999
	  * */
	 for(int c= air[a].returnUnvisit(air);c !=-999;c= air[a].returnUnvisit(air))
	 {
		 if(c==b)
			 return true;
			 
		 if(air[c].isVisited()== false)
		 {
			 air[c].markVisit();
			 if(dfs(c,b)==true)
				 return true;
		 }
	 }
	 return false;
 }
 
 public void airportMarkUnvisited()//setting everything to false by calling method Airport.java
 {
	 int i =1;
	 
	 while(i< air.length)
	 {
		 air[i].markUnvisit();
		 i++;
	 }
 }
 
 
 /*This print out the airport and airport it connects to by one flight for all airports*/
 public void doList(Scanner sc)
 {
  
	 int i =1;
	 
	 while (i< air.length)
	 {
		 
		 if(air[i].getHead()==0)
		 {
			 air[i].traverse();
		 }
		 else
		 {
			 System.out.println("No outbound flight from Airport " + i );
		 }
		 i++;
	 }
 }
 
 public void doFile(Scanner sc)
 {
   String fname = null;

   if ( sc.hasNext() == true )
     fname = sc.next();
   else
   {
     System.out.println ("Filename expected");
     return;
   }
   
   System.out.println ("Performing the File command with file: " + fname);
   
   
   //  1. open the file 
   		File ff = new File(fname);
   		
   //  2. verify the file name is not currently in use
   		if(linkfile[0].filePrevExist(fname)==true)
   		   return;
   		else
   			linkfile[0].push(fname);
   		
   //  3. create a new instance of Scanner 
   		Scanner Newsc = null;
   		
   		try
   		{
   			Newsc = new Scanner (ff);
   		}
   		catch(FileNotFoundException fnfe)
   		{
   		 System.out.println("File does not exist");
   		 return;
   		}
   //  4. recursively call processCommandLoop() with this new instance of Scanner as the parameter
   		processCommandLoop(Newsc);
   //  5. close the file when processCommandLoop() returns
   		Newsc.close();
 }
}