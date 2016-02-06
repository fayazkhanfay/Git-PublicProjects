#include <stdio.h>
#include <stdlib.h>
#include <string.h>//?????Allowed to use this

                   

# define TRUE 1//These two for the debugMode, not necessary to this way but i like using true and false
# define FALSE 0
/*
 FAYAZ NOTES:
    -Does not do error checking we have to include error
    checking
    
   - DEBUG flag is not included in this file, so we have to add that
    
    -Refer to notes online and book notes for some additional code, Troy was being auto corrected
 
    - Head of linked list must be a local variable in main() or some other funtion
    
    -resetting the stack in not necessary but still wants us to do it
 
    -just a thought a stack could also be created in an array
 
    - if the stack emptys out, that means we dont have a solution
 
    -Depth search is a stupid algroithem because it gives you a stupid path- Prof.Troy
 
    -Push and pop and top is sort of given in the lab
 
 */
 
 /*--------------------
 *  ./a.out mazeData1.txt // dont do redirection becaue the commondline is using argv and argc to read it in
 
 
 --------------------------*/
 
/*
 
    ****The .txt files given to us creates the table for us but we have to make sure if they are legal to begin with
 
    mazeData1.txt// Seems to be the normal plot with no errors
 
    mazeData2.txt //This is illegal because to way to get to end because no path from s to e
 
    mazeData3.txt //This is also illegal becasuse the coloum is 0 essentialy nothing 
 
    mazaData4.txt //This is also illegal because e is completely blocked
 
 */

typedef struct top_struct topS;
typedef struct mazeStruct//Provided by Prof. Troy
{
 char **arr;  
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

typedef struct node//FAYAZ we are storing the cordinates in this struct and the address of the next link
{                  //this is in preparation for link list
    int row;
    int coloum;
    struct node *next;
}NODE;

struct top_struct
{
    NODE *top;
    NODE *bottom;
};

int debugMode;// Made this a  Global variable, the alternative is to put in every function

int debugSwitch(char **argv);//These checks the command line and looks for d flag

char **createMazeP(FILE *src, maze* m1, int *legalSize);//this malloc the x-size after first verifying x and y inputs from text file
// are valid. if not valid goes to next line in file. the condition being >0 then will malloc using x-size
// and we return pointer address

void freeMaze(maze *m1);//look in function for comments

void InitializeMazeWithBorder(maze* m1);//Fills the maze with '.' and fills in the outside border
//Previously provided by Prof.Troy it was in main() slight modification and
//put it in this function for the struct need to convert to -> notation

int startPosition(FILE* src,maze *m1);//This put in the valid start postion.If not valid it will use next line of
//data Look in function for more notes

int endPosition(FILE* src,maze *m1);//This put in the valid end postion.If not valid it will use next line of
//data Look in function for more notes

void blockedPos(FILE* src, maze *m1); //This puts in the blocked positions but also verifes to stay with in range
                                    //also does not overide start and end.

void display(maze *m1);//This displays the whole the grid and also print the start,end and size
                    //originally in main copied into this function

FILE* openFile(int argc, char** argv);/* These checks if the file opened properly, also test valid argc  
                                       returns the address of the file */

/*----Below Function are for link list ---------------------------*/
topS *link_create();//creates the initial node with top and bottom pointing right at it

void lst_push_front(topS *l, int *R , int *C);//this adds on to the stack and makes new node top

int lst_len(topS *l);//Returns number of nodes in the link list

int lst_sanity1(topS *l);//makes sure the both top and bottom are not pointing at null when thier is a NODE present
            //useful for when traversing through links

int lst_sanity2(topS *l);//check if back of link list is present and it the next is pointing to null

int lst_sanity3(topS *l);//makes sure the first node of list and last node is reachable by traversing

int lst_is_empty(topS *l);//checks if stack is empty by l->top is pointing to null and return boolean

int lst_pop_front(topS *l);//pops the top and moves the top to the next in list

void readTop(topS *l, maze *m1);//this read what is on top of the stack and take (R,C) and looks in array to see what is
                                //contained in that spot of the array//This is primerally used for debugMode 

void printStackRevOrder(topS *l);//Counts the nodes in the list using lst_len function and then by using two loops
                                //it will up to n node show the value then n-- and counter is reset and then
                                // second last node is read . This process is repeated till n=0.

void resetStack(topS *l);//essentially uses lst_pop_front function which is contained in a loop till p->top==NULL

void freeStack(topS *l);//this free the entire existance of a stack by making a function call to resetStack and
        //after it returns it free(l)

int nextMove(maze *m1, topS *l, int *R,int *C);//This find the next available '.' but does not go  to previous visited
                    //unless after no unvisited spots available then will go to the top of the stack and then pop;

/*------------Above funtions are for link list------------------------------*/


int main (int argc, char **argv)
{
    maze m1;
    int i,j;
    FILE *src;

    debugMode= debugSwitch(argv);//either TRUE or FALSE
    src=openFile(argc,argv);
    
    /* read in the size, starting and ending positions in the maze with in functions*/
    int legalSize= TRUE;
    m1.arr=createMazeP(src, &m1, &legalSize);//The legalSize is for if reading in values and no valid input are
    // available and the legalsize is changed to false. Last minute addition
    if(!legalSize)
        return 0;
    
    
    InitializeMazeWithBorder(&m1);//Look above for function notes
    
    if (!startPosition(src,&m1)||!endPosition(src,&m1))
    {
        freeMaze(&m1);//This goes into function first frees coloumns then the row of pointer
        return 0;
    }

        
    blockedPos(src,&m1);
    
    display(&m1);

    fclose(src);
    
  /*----------------------------------------------------------------------------------------------------*/
    //This below portion is for the link list
    
    
    int R=m1.xstart,C=m1.ystart;//these will be treated as pointer and be updated within functions
    topS *list=link_create();
    lst_push_front(list, &R , &C);
    lst_sanity1(list);
    lst_sanity2(list);
    lst_sanity3(list);
    
    while (1)//This is an infinit loop because inside their are return conditions
    {
        /*if(debugMode)
            printf("in While loop in main for links\n");*/
        
        if (m1.arr[R][C]=='e')
        {
            if(debugMode)
                printf("in While loop in main for links in if statment for 'e'\n");
            printStackRevOrder(list);
            freeStack(list);
            freeMaze(&m1);
            return 0;
        }
        else
        {
            nextMove(&m1,list, &R,&C);
            if(lst_is_empty(list))
            {
                fprintf(stderr, "\nNo possible path to 'e'\n");
                freeStack(list);
                freeMaze(&m1);
                return 0;
            }
        }
        
        lst_sanity1(list);
        lst_sanity2(list);
        lst_sanity3(list);
    }
    

}

FILE* openFile(int argc, char** argv)
{
    /* verify the proper number of command line arguments were given */
    FILE *src;
    int i=1;
    
    if(argc < 2||argc >3)//modification previously argc != 2 if left as prev we were not able to use d flag
    {
        printf("Usage: %s <input file name>\n", argv[0]);
        exit(-1);
    }
    
    while (i<argc)
    {
        if(debugMode)
            printf("IN openFIle\n");
        
        if ( ( src = fopen( argv[i], "r" )) != NULL )
            return src;
        i++;
    }
    
    printf ( "Can't open input file\n");
    exit(-1);

}

int nextMove(maze *m1, topS *l, int *R,int *C)
{
    int tempR=*R;
    int tempC=*C;
    
    if (m1->arr[tempR+1][tempC]=='.'||m1->arr[tempR+1][tempC]=='e')//above
    {
        *R=tempR+1;
        *C=tempC;
        lst_push_front(l,R,C);
        if(debugMode)
            readTop(l,m1);
        if (m1->arr[tempR+1][tempC]=='.')
            m1->arr[tempR+1][tempC]='v';
            
        return 1;
    }
    if (m1->arr[tempR][tempC+1]=='.'||m1->arr[tempR][tempC+1]=='e')//right
    {
        *R=tempR;
        *C=tempC+1;
        lst_push_front(l,R,C);
        if(debugMode)
            readTop(l,m1);
        if (m1->arr[tempR][tempC+1]=='.')
            m1->arr[tempR][tempC+1]='v';
        
        return 1;
    }
    if (m1->arr[tempR-1][tempC]=='.'||m1->arr[tempR-1][tempC]=='e')//down
    {
        *R=tempR-1;
        *C=tempC;
        lst_push_front(l,R,C);
        if(debugMode)
            readTop(l,m1);
        if(m1->arr[tempR-1][tempC]=='.')
            m1->arr[tempR-1][tempC]='v';
        
        return 1;
    }
    if (m1->arr[tempR][tempC-1]=='.'||m1->arr[tempR][tempC-1]=='e')//left
    {
        *R=tempR;
        *C=tempC-1;
        lst_push_front(l,R,C);
        if(debugMode)
            readTop(l,m1);
        if(m1->arr[tempR][tempC-1]=='.')
            m1->arr[tempR][tempC-1]='v';
        
        return 1;
    }
    /*---if no available space above then by defaul goes to previous spot in maze the pop node---*/
    *R=l->top->row;
    *C=l->top->coloum;
    if(debugMode)
        printf("POP off of stack (%d,%d)\n",*R,*C);
    lst_pop_front(l);
    return 0;
}

void freeStack(topS *l)
{
    resetStack(l);
    free(l);
}

void resetStack(topS *l)
{
    while (l->top!=NULL&&l->bottom!=NULL)
    {
        lst_pop_front(l);
    }

}

void printStackRevOrder(topS *l)
{
    int n = lst_len(l);
    int i = 1;
    NODE* p= l->top;
    NODE* tempP = p;
    
    while (n>0)
    {
        while (i!=n)
        {
            p=p->next;
            i++;
        }
        printf("(%d,%d)\n",p->row,p->coloum);
        p=tempP;
        i=1;
        n--;
    }
    
}


void readTop(topS *l, maze *m1)
{
    NODE* p=l->top;
    
 
    if (l->top!=NULL)
    {
        printf("The top of stack stored location is (%d,%d) and contains %c\n",p->row,p->coloum,m1->arr[p->row][p->coloum]);
    }
    else
        fprintf(stderr, "Attempting to Read while stack empty\n");

}

int lst_pop_front(topS *l) {
    
    NODE *p;
    
    
    if(lst_is_empty(l))
        return FALSE;   // List is empty
    
    //ret = l->front->val;
    
    if(l->top == l->bottom) {  // one element
        free(l->top);
        l->top = NULL;
        l->bottom = NULL;
    }
    else {
        p = l->top;  // don't lose node being deleted
        l->top = l->top->next;  // hop over
        free(p);
    }
    return TRUE;//Succesfully poppped
}

int lst_is_empty(topS *l)
{
    return l->top == NULL;
}

int lst_len(topS *l)
{
    NODE *p = l->top;
    int n=0;
    
    while(p != NULL)
    {
        n++;
        p = p->next;
    }
    return n;
}

/* These are "sanity checker" functions that check to see
 *     list invariants hold or not.
 */
int lst_sanity1(topS *l) {
    if(l->top == NULL && l->bottom != NULL){
        fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
        return 0;
    }
    if(l->top == NULL && l->bottom != NULL){
        fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
        return 0;
    }
    return 1;
}

int lst_sanity2(topS *l) {
    if(l->bottom != NULL && l->bottom->next != NULL) {
        fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
        return 0;
    }
    return 1;
}

/*
 *   makes sure that the back pointer is also the last reachable
 *    node when you start walking from front.
 *    HINT:  use pointer comparison
 */
int lst_sanity3(topS *l)
{
    NODE *p=l->top;
    NODE *q=l->bottom;
    //NODE *q=l->front;
    int n= lst_len(l);
    int i=1;
    while (i<=n)
    {
        if (i==n&&p==q)
        {
            //printf("\nwalked succesfully..i::%i,,,n::%i\n",i,n);
            return 1;//Success
        }
        p=p->next;
        i++;
    }
    //printf("\nwalk UNsuccesfully\n");
    fprintf(stderr,"lst_sanity3 error: back pointer is not the last reachable node\n");
    return 0;//UNsuccess
}


void lst_push_front(topS *l, int *R , int *C)
{
    NODE *p = malloc(sizeof(NODE));
    p->row=*R;
    p->coloum=*C;
    p->next=NULL;
    
        if (l->top==NULL)
        {
            l->top=p;
            l->bottom=p;
        }
        else
        {
            p->next=l->top;
            l->top=p;
        }
    
}

topS *link_create()
{
    topS *l = malloc(sizeof(topS));
    l->top= NULL;
    l->bottom=NULL;
    return l;
}

void display(maze *m1)
{
    int i,j;
    
    /* print them out to verify the input */
    printf ("size: %d, %d\n", m1->xsize, m1->ysize);
    printf ("start: %d, %d\n", m1->xstart, m1->ystart);
    printf ("end: %d, %d\n", m1->xend, m1->yend);
    
    
    /* Prints out the maze*/
    for (i = 0; i < m1->xsize+2; i++)
    {
        for (j = 0; j < m1->ysize+2; j++)
            printf ("%c", m1->arr[i][j]);
        printf("\n");
    }
}


void blockedPos(FILE* src, maze *m1)
{
    int xpos, ypos;
    
    while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
        if (xpos>=0&&ypos>=0&&xpos<=m1->xsize&&ypos<=m1->ysize)
        {
            if (m1->arr[xpos][ypos]=='.')
            {
                m1->arr[xpos][ypos] = '*';
            }
        }
    }
}


int endPosition(FILE* src,maze *m1)
{
    do
    {
        if(fscanf (src, "%d %d", &m1->xend, &m1->yend)==EOF)//To get things started
        {
            fprintf(stderr, "Reached E0F no valid inputs for end Position\n");
            return FALSE;
        }
        
        while(m1->xend<0||m1->yend<0||m1->xend>m1->xsize||m1->yend>m1->ysize)
        {//This loop just checks if with in range of the array in order to prevent a seg fault
            fprintf(stderr, "Invalid (%d,%d)input for End must be within border  \n",m1->xend,m1->yend);
            fscanf (src, "%d %d", &m1->xend, &m1->yend);
        }
        
        if(m1->arr[m1->xend][m1->yend]=='.'||m1->arr[m1->xend][m1->yend]=='s')//once within range check if '.' because it is legal
            m1->arr[m1->xend][m1->yend]='e';
        else
        {//if not '.' display error and start loop over again.
            fprintf(stderr, "Invalid (%d,%d)input for End, End cannot be on border \n",m1->xend,m1->yend);
        }
        
    }while(m1->arr[m1->xend][m1->yend]!='e');
    
    if(debugMode)
        printf("debugMode::endPosition::END position is %dx%d\n",m1->xend,m1->yend);
    
    return TRUE;
}

int startPosition(FILE* src, maze *m1)
{
    do
    {
        if(fscanf (src, "%d %d", &m1->xstart, &m1->ystart)==EOF)//To get things started
        {
            fprintf(stderr, "Reached E0F no valid inputs for Start\n");
            return FALSE;
        }
        
        while(m1->xstart<0||m1->ystart<0||m1->xstart>m1->xsize||m1->ystart>m1->ysize)
        {//This loop just checks if with in range of the array in order to prevent a seg fault
            fprintf(stderr, "Invalid (%d,%d)input for Start must be within border  \n",m1->xstart,m1->ystart);
            fscanf (src, "%d %d", &m1->xstart, &m1->ystart);
        }
        
        if(m1->arr[m1->xstart][m1->ystart]=='.')//once within range check if '.' because it is legal
            m1->arr[m1->xstart][m1->ystart]='s';//Marks it with Start position
        else
        {//if not '.' display error and start loop over again.
            fprintf(stderr, "Invalid (%d,%d)input for start, Start cannot be on border \n",m1->xstart,m1->ystart);
        }
        
    }while(m1->arr[m1->xstart][m1->ystart]!='s');
  
    
    if(debugMode)
        printf("debugMode::startPosition::Start position is %dx%d\n",m1->xstart,m1->ystart);
    
    return TRUE;
}
void InitializeMazeWithBorder(maze* m1)
{
    int i,j;
    
    /* initialize the maze to empty */
    for (i = 0; i < m1->xsize+2; i++)
        for (j = 0; j < m1->ysize+2; j++)
            m1->arr[i][j] = '.';
    /* mark the borders of the maze with *'s */
    for (i=0; i < m1->xsize+2; i++)
    {
        m1->arr[i][0] = '*';
        m1->arr[i][m1->ysize+1] = '*';
    }
    for (i=0; i < m1->ysize+2; i++)
    {
        m1->arr[0][i] = '*';
        m1->arr[m1->xsize+1][i] = '*';
    }
    
}


void freeMaze(maze *m1)//when freeing it always 1 to 1 when mallocing and freeing
{
    int i=0;
    
    while (i<m1->xsize+2)//start with index 0 of ** the array/coloum pointing at gets freed
    {           // the plus 2 is to account for the borders on the coloums 
        free(m1->arr[i]);
        i++;
    }
    free(m1->arr);//after all the coloumn/char is freed now the row of ** is freed
    
}

char **createMazeP(FILE* src, maze *m1, int *legalSize)
{
    int initializeSize;
    int i =0;
    if(debugMode)
        printf("debugMode::IN FUNCTION:createMaze\n");
    
    do
    {
        initializeSize=FALSE;
        
        if(debugMode)
            printf("debugMode::IN FUNCTION::createMazeP::Right before fscanf \n");
        
        if(fscanf (src, "%d %d", &m1->xsize, &m1->ysize)==EOF)
        {
            fprintf(stderr, "Reached E0F no valid inputs for size\n");
            legalSize=FALSE;
            return 0;
        }
        
        if (debugMode)
            printf("debugMode::In funtion createMazeP with m1->xsize:%d, m1->ysize:%d\n",m1->xsize,m1->ysize);
    
        if (m1->xsize==0||m1->ysize==0)
        {
            fprintf(stderr, "Invalid (%d,%d)input for size must be greater than 0 \n",m1->xsize,m1->ysize);
            initializeSize=TRUE;
        }
    }while(initializeSize);
    
    printf("Size of maze %dx%d\n",m1->xsize,m1->ysize);
    
    //The plus 2 in mallocs is for the borders
    char **maze=(char**)malloc(sizeof(char*)*(m1->xsize+2));//this makes a row of pointers, now we must create our coloumns
    
    do
    {
        maze[i]=(char*)malloc(sizeof(char)*(m1->ysize+2));//this makes our coloumns now this array can be used as maze[i][j]
        i++;//the logic behind this **maze the row point to the coloumn of char[] which is also pointer hence **
    }while(i<m1->xsize+2);
    
    return maze;
}


int debugSwitch(char **argv)
{
    int i=1;//Starting with one because argv[0] will ./a.out no point in checking
    while (argv[i]!=NULL)//looking at the address to see if it is a null because in command line **argv pointer to array
    {
        if (strcmp(argv[i],"-d")==0)
        {
            printf("debugMode is ON\n");
            return TRUE;
        }
        i++;
    }

    return FALSE;
}
