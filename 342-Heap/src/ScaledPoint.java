// Programmer:  Team 16: Christian Valladares, Joe Kallarackel, Fayaz Khan, Jaydeep Patel
// Assignment:  Project 3 Heap Illustration 
// Date:        November 12, 2015
// Description: A class that resizes all the objects.This class also extends JApplet to draw. 


import javax.swing.*;

public class ScaledPoint extends JApplet
{
    int numElements;    // Counts the number of elements present in the heap
    int treeHeight;     // Counts the height of the tree, including the root.
    
    public ScaledPoint(int eltNumber)
    // PRE:  eltNumber is initialized, eltNumber > 0 
    // POST: Creates an instance of Scaled Point and initializes the member variable:
    //       numElements = eltNumber
    {
        double logElements; 								//For log_2 of the number of elements
        
        numElements = eltNumber;                            //number of elements are now updated 
        logElements = (Math.log(numElements)/ Math.log(2));	//formula for calc height of tree
        treeHeight = (int) (logElements) + 1;         		//Get the ceiling of the logarithm
    }
    
    public ScaledPoint()                                                
    // POST: Creates an instance of Scaled Point and initializes the member variable:
    //       numElements = 63
    {
        this(63);
    }
    
    public int getEdgeXStartPosition(JPanel target, int elementIndex, int nodeWidth)
    // PRE:  target is initialized 
    //       elementIndex is initialized and elementIndex > 1.
    //       nodeWidth is initialized and nodeWidth > 0. 
    // POST: will return the start value for a node's edge.  We intend to draw from
    //       child to parent.
    //       FACTVAL == start value for node's edge.
    {        
        int xStart = getNodeXPosition(target,elementIndex) + (nodeWidth/2);
        return xStart;
    }
    
    public int getEdgeXEndPosition(JPanel target, int elementIndex, int nodeWidth)
    // PRE:  target is initialized 
    //       elementIndex is initialized and elementIndex > 1.
    //       nodeWidth is initialized and nodeWidth > 0. 
    // POST: will return the start value for a node's edge.We intend to draw from
    //       child to parent.
    //       FCTVAL == will return x-cordinate for node position 
    //
    {        
        int parent;
        int xEnd;
        
        parent = (int)Math.floor((elementIndex-1)/2);
        xEnd = getNodeXPosition(target,parent) + (nodeWidth/2);
        return xEnd;
    }
    
    public int getEdgeYStartPosition(JPanel target, int elementIndex, int nodeWidth)
    // PRE:  target is initialized 
    //       elementIndex is initialized and elementIndex > 1.
    //       nodeWidth is initialized and nodeWidth > 0. 
    // POST: will return the start value for a node's edge.  We intend to draw from
    //       child to parent.
    //       FCTVAL ==  will return y-cordinate for node position 
    {        
        int yStart = getNodeYPosition(target,elementIndex);
        
        return yStart;
    }
    
    public int getEdgeYEndPosition(JPanel target, int elementIndex, int nodeWidth)
    // PRE:  target is initialized 
    //       elementIndex is initialized and elementIndex > 1.
    //       nodeWidth is initialized and nodeWidth > 0. 
    // POST: will return the end value for a node's edge.We intend to draw from
    //       child to parent.
    //       FCTVAL == will return x-cordinate for node position 
    //
    {        
        int parent;
        int xEnd;
        
        parent = (int)Math.floor((elementIndex-1)/2);
        xEnd = getNodeYPosition(target,parent) + (nodeWidth);
        
        return xEnd;
    }
    
    public int getNodeXPosition(JPanel target, int elementIndex)
    // PRE:  target is initialized 
    //       elementIndex is initialized and elementIndex > 1.
    // POST: Returns the Horizontal origin for a node in the heap. based on the 
    //       element number, and the total number of elements
    //       FCTVAL == Width *(elementIndex / (2^treeHeight)
    {
        int width;      // width holds the width of the panel
        int position;   // position holds the pixel position of a given node element.                
        int nodeLevel;  // nodeLevel holds the level in which the current element resides
        int iterator;   // iterator holds the index of the current element in terms of
                        //    its level.   element 5 is in level 3 and it is the
                        //    second element of its level.        
        int numerator;  // numerator holds the end value which the numerator will hold when it
                        //    comes to the horizontal positioning. Numerator is an
                        //    odd number
 
        width = target.getWidth();                                    // Fetch the pane Width
        nodeLevel = (int) (Math.log(elementIndex + 1)/ Math.log(2));  // level log_2(elementIndex) 
                                                                      // (to avoid zero values)
    
        iterator = ((elementIndex+1) % (int) Math.pow(2, nodeLevel)); // Compute the node's index for its level, 
                                                                      //    which is the element's index mod with
                                                                      //    the total number of elements for a 
                                                                      //    given level.
        
        numerator = (iterator)*2 + 1;                                 // The numerator is the node's level-index, 
                                                                      //    turned to an odd number
        position = (int) (width  * numerator / 
                   (Math.pow(2.0,(double) nodeLevel + 1)));           // Get the position as a percentage of the panel
                                                                      //    width. This will be the element number
                                                                      //    divided by 2 to the Tree Height.
        
       return position;                                               // return the position 
    }
    
    public int getNodeYPosition(JPanel target, int elementIndex)
    // PRE:  target is initialized 
    //       elementIndex is initialized and elementIndex > 1.
    // POST: Returns the Vertical origin for a node in the heap. based on the 
    //       element number, and the total number of elements
    //       FCTVAL == Width *(elementIndex / (2^treeHeight)
    {
        int height;     // Holds the height of the panel
        int position;   // Holds the pixel position of a given node element.                
        int nodeLevel;  // Holds the expected level of the node
        
        height = target.getHeight();                                 // Fetch the pane height
        nodeLevel = (int) (Math.log(elementIndex + 1)/ Math.log(2)); //Compute the node level log_2(elementIndex) 
        position = (int) (height * (nodeLevel)/ (treeHeight*2));     // Get the position as a percentage of the panel
                                                                     //    width. This will the element number divided
                                                                     //    by 2 to the Tree Height.
        return position;                                             // return the position
    }
}
