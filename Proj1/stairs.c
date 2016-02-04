#include <stdio.h>

//Fayaz Khan
//HW1

/*
 
 HW1:
 - User enters an int (height), no error handling.
 - Display stairs going up height.
 - Display stairs going down height.
 - Display stairs in traingle pattern height.
 
 */

/*
    I am using nested for loops to print stairs with function calls
 */

int getHeight();            // asks user to enter in for the height of stairs

void goingUp(int height);   // print the stairs going up.

void goingDown(int height); // print the stairs going down.

void goingTri(int height);  // print Triangle pattern.

int main()
{
    int height = getHeight();

    goingUp(height);
    goingDown(height);
    goingTri(height);
    
    return 0;
}

int getHeight()
{
    int height;
    
    printf("\nPlease enter Integer: ");
    
    scanf("%d",&height);
    
    return height;
}


void goingUp(int height)
{
    
    printf("\nGoing Up\n");
    
    int turn = 0;
    
    for (int level=1; level <= height; level++)
    {
        for(int printX=0; printX < level; printX++)
        {
            for(int Space=0; Space < height-level && turn==0; Space++)
            {
                printf(" ");
            }
            
            turn = 1;
            printf("X");
        }   
        
        turn = 0;
        printf("\n");   
    }
    
    printf("\n"); // not part of stairs

}


void goingDown(int height)
{
    
    printf("\nGoing Down\n");
    
    for(int level = 0; level < height; level++)
    {
        for(int printX = 0; printX <= level; printX++)
        {
            printf("X");
        }
        
        printf("\n");
    }
    
    printf("\n"); // not part of stairs

}


void goingTri(int height)
{
    printf("\nGoing TRIANGLE\n");
    
    int turn = 0;
    
    for(int level = 0; level < height; level++)
    {
        for(int printX = height; printX <= height + level + level; printX++)
        {
            for(int Space = 1; Space < height - level && turn == 0; Space++)
            {
                printf(" ");
            }
            
            turn = 1;
            printf("X");
        }
        
        turn = 0;
        printf("\n");
    }
    
    printf("\nGood Bye\n\n");

}

