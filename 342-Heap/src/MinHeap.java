// Programmer:  Team 16: Christian Valladares, Joe Kallarackel, Fayaz Khan, Jaydeep Patel
// Assignment:  Project 3 Heap Illustration 
// Date:        November 12, 2015
// Description: A class that works with Min Heap. This class extends the parent class Heap. heapifyDown balances
//              the tree during node deletion. removeValue removes the value. heapifyUp balances the tree during 
//              node addition. 

import java.util.Arrays;

public class MinHeap extends Heap
{    
    public MinHeap()
    //Post: Calling super to set up default constructor
    {
        super();                                            //default constructor
    }
    
    @Override
    public void heapifyDown(int index)
    //Pre:  Index must be between 0 and currentLength
    //Post: Sorts the elements in the array for removing
    {
        int i;                                              //current index
        i = index;                                          //cetting index
        
        while(i != -1)                                      //while not invalid index
        {            
            int parentVal;                                  //value of parent
            int leftIndex;                                  //index of left child
            int rightIndex;                                 //index of right child
            
            parentVal = array[i];                           //get parent value
            rightIndex = getChildRightIndex(i);             //get right index
            leftIndex = getChildLeftIndex(i);               //get left index
            
            if(rightIndex >= currentLength)                 //if rightIndex over currentLength
                rightIndex = -1;                            //set rightIndex to invalid
            if(leftIndex >= currentLength)                  //if leftIndex over currentLength
                leftIndex = -1;                             //set leftIndex to invalid
            
            if( rightIndex != -1 &&  leftIndex != -1)       //current has 2 children
            {
                int rightVal;                               //value of right child
                int leftVal;                                //value of left child
                
                rightVal= array[rightIndex];                //get right value
                leftVal = array[leftIndex];                 //get left value
                
                if(rightVal <= leftVal)                     //if right child less then left
                {
                    if(rightVal <= parentVal)               //if right value less then parent
                    {
                        actionLog.feedSwap(rightIndex,rightVal,i,parentVal);
                        array[i] = rightVal;                //swap parent and child
                        array[rightIndex] = parentVal;
                        
                        state[stateIndex] =                 //copying board into state
                                Arrays.copyOf(array, currentLength);
                        stateIndex++;                       //increase index
                        
                        i = rightIndex;                     //right child new parent
                    }
                }
                else                                        //left greater then right value
                {
                    if(leftVal <= parentVal)                //left value less then parent
                    {
                        actionLog.feedSwap(leftIndex,leftVal,i,parentVal);
                        array[i] = leftVal;                 //swap left child and parent
                        array[leftIndex] = parentVal;

                        state[stateIndex] =                 //copying board into state
                                Arrays.copyOf(array, currentLength);
                        stateIndex++;                       //increase index
                        
                        i = leftIndex;                      //left child new parent
                    }
                }
            }            
            else if(leftIndex != -1)                        //no right child
            {
                int leftVal;                                //left child value
                leftVal= array[leftIndex];                  //get value of left child
                
                if(leftVal <= parentVal)                    //left child less then parent
                {
                    actionLog.feedSwap(leftIndex,leftVal,i,parentVal);                    
                    array[i] = leftVal;                     //swap parent and child                   
                    array[leftIndex] = parentVal;
                    
                    state[stateIndex] =                     //copying board into state
                            Arrays.copyOf(array, currentLength);
                    stateIndex++;                           //increase index
                    i = leftIndex;                          //index is left child
                }
                else                                        //parent greater then left child
                    i = -1;                                 //break loop index
            }
            else                                            //no children and other cases  
            {
                i = -1;                                     //break loop index
            }
        }
    }
    
    @Override
    public void removeValue(int value)
    //Pre:  value must be between 0 and currentLength
    //Post: Removes value from array and heapify accordingly 
    {
        int valIndex;                                       //index location
        valIndex = search(value);                           //get index from search
                
        if(valIndex != -1)                                  //index valid
        {
            int pIndex;                                     //parent Index
            stateIndex = 0;                                 //reset stateIndex
            state[stateIndex] =                             //copying board into state
                    Arrays.copyOf(array, currentLength);
            stateIndex++;                                   //increase index
            actionLog.feedDelete(array[valIndex]);
            array[valIndex] =                               //swap removed value and last leaf
                    array[currentLength-1];
            pIndex = getParentIndex(valIndex);              //get parent index of new spot
            currentLength--;                                //decrement counter
            state[stateIndex] =                             //copying board into state
                    Arrays.copyOf(array, currentLength);
            stateIndex++;                                   //increase index
            
            if(array[valIndex] >= array[pIndex])            //current value is greater
            {
                heapifyDown(valIndex);                      //heapify downward
            }
            else                                            //parent greater
            {
                heapifyUp(valIndex);                        //heapify value upward
            }
        }
        
        if(currentLength < MAX_LENGTH)                      //if current is less max length
        {
            isFull = false;                                 //if full is false
        }
    }
    
    @Override
    public void heapifyUp(int index)//DONT NEED THIS ANYMORE 
    //Pre:  index must be between 0 and currentLength
    //Post: Sorts the elements in array
    {
        int i;                                              //index variable
        i = index;                                          //index of where added
                
        while(i != 0)                                       //loop up to root
        {
            int val;                                        //value of last element
            int pIndex;                                     //parent index
            
            val = array[i];                                 //set value   
            pIndex = getParentIndex(i);                     //get parent index  

            if( array[pIndex] > val)                        //if child value is less than parent
            {
                actionLog.feedSwap(i,val,pIndex,pIndex); 
                array[i] = array[pIndex];                   //swap parent and child          
                array[pIndex] = val;

                state[stateIndex] =                         //copying board into state
                        Arrays.copyOf(array, currentLength);
                stateIndex++;                               //increase index
            }          
            i = pIndex;                                     //parent is new child
        }
    } //end of method
}
