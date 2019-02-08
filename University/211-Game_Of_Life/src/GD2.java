import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import javax.swing.*;
/*
 * FAYAZ KHAN
 * 655427236
 * */

public class GD2
{
	//public 
    //private static Object[][] grid_A;

	public static int checkAdj(int x, int y,int grid_A[][])
	{
		int alive = 0;
		
		if(grid_A[x-1][y-1]==1)
			alive++;
		if(grid_A[x-1][y]==1)
			alive++;
		if(grid_A[x-1][y+1]==1)
			alive++;
		if(grid_A[x][y-1]==1)
			alive++;
		if(grid_A[x][y+1]==1)
			alive++;
		if(grid_A[x+1][y-1]==1)
			alive++;
		if(grid_A[x+1][y]==1)
			alive++;
		if(grid_A[x+1][y+1]==1)
			alive++;
		
		return alive;
	}
	
	public static void status(int alive, int grid_B[][], int x ,int y)
	{
		if((alive<2)&&grid_B[x][y]==1)
		{
			grid_B[x][y]=0;
			return;
		}
		
		if((alive==2||alive==3)&&grid_B[x][y]==1)
		{
			grid_B[x][y]=1;
			return;
		}
		
		if(alive>3&&grid_B[x][y]==1)
		{
			grid_B[x][y]=0;
			return;
		}
		if(alive==3&&grid_B[x][y]==0)
		{
			grid_B[x][y]=1;
			return;
		}
	}
	
	public static void copyGrid_BtoGrid_A(int[][]grid_B,int [][]grid_A,int x,int y)
	{
		int i=1,j=1;
		while(i<=x)
		{
			while(j<=y)
			{
				grid_A[i][j]=grid_B[i][j];
				j++;
			}
			i++;
			j=1;
		}
			
	}
	
	
	public static void main( String args[] )
   {
   	
    	//System.out.println ("This program was given " + args.length + " command line arguments");
    	Scanner sc = null;
    	
    	   if(args.length>0)
    	   {
    		   File f = new File (args[0]);
        	   sc = null;
        	   try
        	   {
        	     sc = new Scanner (f);
        	   }
        	   catch (FileNotFoundException fnfe)
        	   {
        		   System.err.print("File did not exist");
        	     return;
        	   } 
    	   }
    	   else
    	   {
    		   System.err.print("No commmand line arguements\n");
    		   return;
    	   }
    	   
    	  int x =0;
    	  int y= 0;
    	  
    	   while (sc.hasNextInt()&& (x==0||y==0))
    	   {
    	     int val = sc.nextInt();
    	     int val2= sc.nextInt();
    	     
    	     if(val>=1&&val2>=1)
    	     {
    	    	 x=val;
    	    	 y=val2; 
    	     }
    	     else
    	     {
    	    	 System.err.print("Invalid cordinate size will use next input line\n");
    	     }
    	   }
    	   
    	   GridDisplay disp = new GridDisplay(x, y);
    	  
    	   int [][] grid_A;
    	   int [][] grid_B;

    	   
    	   grid_A = new int [x+2][y+2]; 
    	   grid_B = new int [x+2][y+2];
    	   
    	   
    	   while (sc.hasNextInt())
    	   {
    	     int val = sc.nextInt();
    	     int val2= sc.nextInt();
    	     
    	     if((val>=1&&val2>=1)&&(val<=x&&val2<=y))
    	     {
    	    	 grid_A[val][val2]=1;
    	    	 grid_B[val][val2]=1;
    	     }
    	     else
    	     {
    	    	 System.err.print("Out of range will use next input line\n");
    	     }
    	    
    	   }
    	   

    	  sc.close();
    	  
    	  int i,j; 
    	  int alive;
    	   
    	   while(true)
    	   {
    		   /*FOR DISPLAY*/
    		   i=0;
    		   j=0;
    		   while(i<=x)
        	   {
        		   while(j<=x)
        		   {
        			   if(grid_A[i][j]==1)
        				   disp.setColor(i,j,Color.BLUE);//ALIVE
        			   else
        				   disp.setColor(i,j,Color.WHITE);//DEAD
        			   GridDisplay.mySleep (5);
        			  j++; 
        		   }
        		   i++;
        		   j=0;
        	   }
    		   
    		   
    		   i=1;
    		   j=1;
    		   while(i<=x)
    		   {
    			   while(j<=x)
    			   {
    				   alive = checkAdj(i, j,grid_A);
    				   status(alive, grid_B,i ,j);
    				   j++;
    			   }
    			   j=1;
    			   i++;
    		   }
    		   copyGrid_BtoGrid_A(grid_B,grid_A,x,y);
    	
    	   }
    	   
    	   
   }	   
    	   
  

}  // end of GD2 class


class GridDisplay extends JFrame
{
   private JLabel labels[];

   private Container container;
   private GridLayout grid1;
   int rowCount;
   int colCount;

   // set up GUI
   public GridDisplay(int rows, int cols)
   {
      super( "GridDisplay for CS211" );
      setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

      // set up grid layout struture of the display
      rowCount = rows;
      colCount = cols;
      grid1 = new GridLayout( rows, cols );
      container = getContentPane();
      container.setLayout( grid1 );

      // create and add buttons
      labels = new JLabel[ rows * cols ];

      for ( int count = 0; count < labels.length; count++ ) {
         labels[ count ] = new JLabel( " " );
         labels[count].setOpaque(true);
         container.add( labels[ count ] );
      }

      // set up the size of the window and show it
      setSize( cols * 15 , rows * 15 );
      setVisible( true );

   } // end constructor GridLayoutDemo

   // display the given char in the (row,col) position of the display
   public void setChar (int row, int col, char c)
   {
     if ((row >= 0 && row < rowCount) && (col >= 0 && col < colCount) )
     {
       int pos = row * colCount + col;
       labels [pos].setText("" + c);  
     }
   }
   
   // display the given color in the (row,col) position of the display
   public void setColor (int row, int col, Color c)
   {
     if ((row >= 0 && row < rowCount) && (col >= 0 && col < colCount) )
     {
       int pos = row * colCount + col;
       labels [pos].setBackground(c);  
     }
   }
   
    // puts the current thread to sleep for some number of milliseconds to allow for "animation"
    public static void mySleep( int milliseconds)
    {
      try
      {
        Thread.sleep(milliseconds);
      }
      catch (InterruptedException ie)
      {
      }
    }
} // end class GridDisplay
