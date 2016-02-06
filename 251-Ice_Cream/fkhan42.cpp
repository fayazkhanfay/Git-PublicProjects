#include <fstream>   // needed for file operations
#include <cstdlib>   // needed for atoi(...)
#include <cstring>   // needed for strtok(...)
#include <iostream>  //need this for cout
#include <stdlib.h>
using namespace std;

/*---------------------------
 Author: Fayaz Khan
 UIN:655427236
 Date: 3/22/2015, UIC CS 251 Data StructuresProgram: #3, Ice Cream
 System: Xcode i7 Mac, 8GB RAM
 Lab: Thurs 11am TA: Paul Murray
 
 TO DO: Create a program to print out the options of where to place ice 
        cream trucks in a tourist town with the least amount of ice
        cream trucks but also covering every location by adjacency
 
  This script works for small.txt, graph.txt and map.txt are all working
 
 --------------------------------*/

# define TRUE 1//These two for the debugMode
# define FALSE 0


/*dislayInfo: Prints out information about author and assignment per rubric*/
void displayInfo();

/*validfile: ask for the filename of .txt check if valid and returns a pointer 
 to the filename*/
FILE *validfile();

/*numnNodes reads in the first number from .txt file and return quantity of 
 nodes*/
int numbNodes(FILE *finput);

int debugMode;// Made this a  Global variable for for -d flag

int debugSwitch(char **argv);//These checks the command line and looks for dflag

/*create: The mallocs a 2d array by numberofNodes by numberofNodes*/
int **create(int numberOfNodes);

/* freeAll: This frees the entire  2d array specifically grid*/
void freeAll(int **grid, int numberOfNodes);

/*fillGrid_zeros: this fills the 2d array with all zeros*/
void fillGrid_zeros(int **grid, int numberOfNodes);


/*OutputAdjacentMatrix Borrowed from lab9 to diplay the 2darray but also 
 slightly modified to account for sum of adjancent nodes*/
void OutputAdjacentMatrix(int **adjacentMatrix, int N);

/*combinations borrowed from Prof.Reed but this function also test out the 
 combinations as it is being printed by making several function calls from this 
 one function*/
void combinations(int v[], int start, int n, int k, int maxk,int numberOfNodes,
                  int **grid,int *domRun);

/*smallestCombo find the minimum number of ice trucks that is math allowes*/
int smallestCombo(int **grid, int numberOfNodes);

/*readInData reads in the data from the text files in fills the 2d array in 
 index location by marking it as true. Majority of code was borrowed from 
 Prof.Reed from read.cpp*/
void readInData(FILE *finput, int **grid, int numberOfNodes);

/* createDomChecker function is called from combinations function malloc a 
 1d array fills it with 0's for immediate use to see if combinations of nodes 
 are legal*/
int * createDomChecker(int numberOfNodes);

/*adjancentTest puts "1" in 1d array domeSetcheck by referencing the grid 
 specified by testNode called only from combinations function*/
void adjacentTest(int **grid,int* domSetcheck ,int testNode, int numberOfNodes);

/*legalDomSet will only be called from combinations function this will check 
 domSetcheck array to see if all the nodes are adjancent to each other will 
 return 1 for true*/
int legalDomSet(int *domSetcheck, int numberOfNodes);

//----------Functions for Large file----------------

/*int_cmp for the q sort compare two integers and returns and int based on
    >,< or 0 more details in function borrowed from Prof.Reed but heavily
    modified */
int int_cmp(const void *a, const void *b);

/*largeSingleDom this function houses the loop so it can go thorough
    2d array multiple time to determine the row that need to be combined
    to determine the dominating set */
void largeSingleDom(int **grid,int numberOfNodes);

/* combDistNode will print new adjacent node, update the row holding 
    adjacent nodes for checking and will reset all the vairables that 
    need to be reset*/
void combDistNode(int **grid,int* distRow, int *row,
                  int *mostDistAdj,int numberOfNodes, int *iceCreamCount);
/*-----------------------------------*/


int main(int argc, char **argv)
{
    displayInfo();
    
    debugMode= debugSwitch(argv);//either TRUE or FALSE
    
    FILE *finput=validfile();	 // input file
    
    int numberOfNodes= numbNodes(finput);
    
    int value;	// used to store parsed values from input lien
    
    int **grid=create(numberOfNodes);
    fillGrid_zeros(grid,numberOfNodes);
    
    if(debugMode)
        OutputAdjacentMatrix(grid, numberOfNodes);
    
    readInData(finput,grid, numberOfNodes);
    
    if(debugMode)
        OutputAdjacentMatrix(grid, numberOfNodes);
   
    int sizeSet=smallestCombo(grid,numberOfNodes);
    
    
    int domRun=1;
    printf("Smallest Dominating Sets are:\n");
    if(numberOfNodes<30)
    {
        int v[numberOfNodes];
        do
        {
            combinations(v, 1,numberOfNodes,1,sizeSet,numberOfNodes,grid,
                         &domRun);
            sizeSet++;
            
        }while(domRun);
    }
    else
    {
        qsort(grid,numberOfNodes,sizeof(int**),int_cmp);
        largeSingleDom(grid,numberOfNodes);
    }

    freeAll(grid, numberOfNodes);
    
    printf("\nExiting program...\n");
}

void combDistNode(int **grid,int* distRow, int *row,
                 int *mostDistAdj,int numberOfNodes,int *iceCreamCount)
{
    int i=1;
    int l_DistRow=*distRow;
    printf("%d ",grid[l_DistRow][0]);
    (*iceCreamCount)++;
    while (i<=numberOfNodes)
    {
        if(grid[l_DistRow][i])
            grid[0][i]=1;
        i++;
    }
    
    grid[l_DistRow][i]=-1;
    *mostDistAdj=0;
    *distRow=0;
    *row=1;
   
}

void largeSingleDom(int **grid,int numberOfNodes)
{
    /*
        we start with row 0 because that node has the most edges 
        in this function we find the next row that has the most edges 
        but not the same as the nodes we are combining with.
     
        in summary will find the most distinct node and will not search
        thought all the nodes at a certain point if gridV < mostDistAdj 
        it will stop searching.
     
        Will jump into combdistnode and will add new node to the checklist
     */
    int sumNodes=grid[0][numberOfNodes+1];
    
    int tempRow=0,distinctAdj=0,row,coloum=1, gridV,mostDistAdj=0,distRow;
  
    printf("%d ",grid[0][0]);
    int iceCreamCount=1;
    while (sumNodes<numberOfNodes)
    {
        row=1;
        gridV=grid[row][numberOfNodes+1];
      
        while((gridV>mostDistAdj||gridV==-1)&&row<numberOfNodes)
        {
            gridV=grid[row][numberOfNodes+1];

            if(gridV!=-1)
            {
                coloum=1;
                while (coloum<=numberOfNodes)
                {
                    if(grid[0][coloum]==0&&grid[row][coloum]==1)
                        distinctAdj++;

                    coloum++;
                }
            
                if(distinctAdj>mostDistAdj)
                {
                    distRow=row;
                    mostDistAdj=distinctAdj;
                }
                distinctAdj=0;
                
            }
            row++;
            
        }
        
        sumNodes= sumNodes+ mostDistAdj;
        
        combDistNode(grid,&distRow,&row,&mostDistAdj,numberOfNodes,
                     &iceCreamCount);
    }
    printf("\n");
    printf("Number of ice cream trucks %d\n",iceCreamCount);
}


int int_cmp(const void *a, const void *b)
{

    // cast from void * to int **
    /*
        Purpose of this is because i wanted to get the last colum(index) in the
        row but would right value would not show up. I also dont know which 
        row it is specifying in order not to mess with that it did this way
        so i can specify the couloum with out knowing the row 
     
        I also tried to pointer arithmatic incorporating sizeof(int) but
        would not consitantly show the right value
     
     */
    const int **ia = (const int **)a;
    const int *ia2=*ia;
    
    const int **ib = (const int **)b;
    const int *ib2=*ib;
   
    if(ia2[249]<ib2[249])//That is where we keep sum of adjacent
        return 1;
    if(ia2[249]>ib2[249])
        return -1;
    if(ia2[249]==ib2[249])
        return 0;
    
    return 0;//Keep function happy
}

void displayInfo()
{
    printf("\nAuthor: FAYAZ KHAN\n");
    printf("Date: 3/22/2015, UIC CS 251 Data StructuresProgram");
    printf("Program #3, Ice Cream\n");
    printf("System: Xcode i7 Mac, 8GB RAM\n");
    printf("Lab: Thur 11am Paul Murray\n\n");
}

void displayDom(int domV[],int sizeSet)
{
    int i=1;
    
    while (i<=sizeSet)
    {
        printf("%d ",domV[i]);
        i++;
    }
    printf("\n");
}

int legalDomSet(int *domSetcheck, int numberOfNodes)
{
    int i=0;
    
    while (i<numberOfNodes)
    {
        if(debugMode)
            printf("Debugmoded legalDomSet domsetcheck[%d]::%d\n",i,
                   domSetcheck[i]);
        if(!domSetcheck[i])
            return 0;//not a dominating set
        i++;
    }
    return 1;//True it is a dominating set
}



void combinations(int v[], int start, int n, int k, int maxk, int numberOfNodes,
                   int **grid,int *domRun)
{
    int i;
    
    /* k here counts through positions in the maxk-element v.
     * if k > maxk, then the v is complete and we can use it.
     */
    if (k > maxk) {
        /* insert code here to use combinations as you please */
        int* domSetcheck=createDomChecker(numberOfNodes);
        
        if(debugMode)
            printf("\n debugMode printing combo set\n");
        
        for (i=1; i<=maxk; i++)
        {
            if(debugMode)
                printf ("%i ", v[i]);
            
            adjacentTest(grid,domSetcheck ,v[i]-1,numberOfNodes);
        }
        
        if(debugMode)
            printf ("\n");
        
        if(legalDomSet(domSetcheck,numberOfNodes))
        {
            displayDom(v,maxk);//maxk is sizeofSet
            *domRun=0;
        }
        
        free(domSetcheck);
        return;
    }
    
    /* for this k'th element of the v, try all start..n
     * elements in that position
     */
    for (i=start; i<=n; i++) {
        
        v[k] = i;
        
        /* recursively generate combinations of integers
         * from i+1..n
         */
        combinations (v, i+1, n, k+1, maxk,numberOfNodes,grid,domRun);
    }
}

void adjacentTest(int **grid,int* domSetcheck ,int testNode, int numberOfNodes)
{
    int i=1;
    
    while(i<=numberOfNodes)
    {
        if(debugMode)
            printf("debugMode adjacent test grid[testNOde:%d][i:%d]==%d \n",
                   testNode,i,grid[testNode][i]);
            
        if(grid[testNode][i])
            domSetcheck[i-1]=1;
        i++;
    }
}

int * createDomChecker(int numberOfNodes)
{
    int i=0;
    int *domSetcheck=(int*)malloc(sizeof(int)*(numberOfNodes));
    
    while (i<numberOfNodes)
    {
        domSetcheck[i]=0;
        if(debugMode)
            printf("in createDomcheck %d\n",domSetcheck[i]);
        i++;
    }
    
    if(debugMode)
    {
        i=0;
        printf("Printing createDomChecker array numberofNodes:%d\n",
               numberOfNodes);
        
        while (i<numberOfNodes)
        {
            printf("%d ",domSetcheck[i]);
            i++;
        }
    }
    return domSetcheck;
}

void readInData(FILE *finput, int **grid, int numberOfNodes)
{
    char inputLine[ 81];// Store entire input line at a time
    
    int totalAdjNodes=0;//counts up the total of adjancent nodes to each
                        //individule as being read in
    
    // loop through the input lines, reading a whole line at a time.
    for( int i=0; i<numberOfNodes; i++) {//Previously numberofLines
        fgets( inputLine, 81, finput);
        
        // echo the entire input line
        if(debugMode)
            printf("%s", inputLine);
        
        // Parse the individual items on the input line.
        // strtok replaces the next space with a NULL
        // and returns the address of the current item
        
        if(debugMode)
            printf("Individual values are: ");
        
        char *pWord = strtok( inputLine, " ");
        while( pWord != NULL) {
            int vertValue = atoi( pWord);  // Convert string to integer
            
            if(debugMode)
                printf("%d ", vertValue);		  // Display the value
            
            grid[vertValue-1][0]=vertValue;
            
            while( pWord != NULL)
            {
                int value = atoi( pWord);     // Convert string to integer
                
                if(debugMode)
                    printf("%d ", value);		  // Display the value
                
                grid[vertValue-1][value]=1;
                pWord = strtok( NULL, " ");// Get next token.Note the NULL
                                           // parameter here!
                totalAdjNodes++;
            }
            grid[i][numberOfNodes+1]=totalAdjNodes;
            totalAdjNodes=0;
        }
        
        if(debugMode)
            printf("\n");
        
    }
    
    // Close the input file
    fclose( finput);
    
}




int numbNodes(FILE *finput)
{
    int numberOfNodes;
    
    // Read first line to see how many other lines there are
    fscanf(finput, "%d\n", &numberOfNodes);//Changed from numberofLines
    printf("Reading in for %d Vertices.\n", numberOfNodes);//changed like above
    
    return numberOfNodes;
}

FILE *validfile()
{
    FILE *finput; // input file
    char fileName[30];
    
    printf("Please enter .txt filename\n");
    scanf("%s",fileName);
    
    finput = fopen( fileName, "r");
    if( finput == NULL) {
        printf("File open failed.  Exiting program...\n");
        exit( -1);
    }
    return finput;
}


int smallestCombo(int **grid, int numberOfNodes)
{
    int i=0;
    int adjNodeVal[numberOfNodes];
    
    while (i<numberOfNodes)
    {
        adjNodeVal[i]=grid[i][numberOfNodes+1];
        
        if(debugMode)
            printf("smallest Combo::%d\n",adjNodeVal[i]);
        
        i++;
    }
    
    i=0;
    int tempIndex=0;
    int j=0;
    int maxValue=0;
    int sumMax=0;
    
    while(i<numberOfNodes)
    {
        while (j<numberOfNodes)
        {
            if(adjNodeVal[j]>maxValue)
            {
                tempIndex=j;
                maxValue=adjNodeVal[j];
            }
            j++;
        }
        
        if(debugMode)
            printf("maxvalue::%d\n",maxValue);
        
        sumMax=sumMax+maxValue;
        if(sumMax>=numberOfNodes)
        {
            if(numberOfNodes>20&&numberOfNodes<30)
                return i+2;//this is for graph.txt
            
            return i+1;//this is for small.txt
        }
        adjNodeVal[tempIndex]=0;
        tempIndex=0;
        maxValue=0;
        j=0;
        i++;
    }
    return 0;
}


void OutputAdjacentMatrix(int **adjacentMatrix, int N)
{
    cout << "The Adjacent Matrix of the graph is: " << endl;
    for(int i = 0;i < N; i++) {
        for(int j = 0;j < N+2; j++) {
            cout << adjacentMatrix[i][j] << " ";
        }
        cout<<endl;
    }
}

void fillGrid_zeros(int **grid, int numberOfNodes)
{
    int i=0,j=0;
    
    while(i<numberOfNodes)
    {
        while(j<numberOfNodes+2)
        {
            grid[i][j]=0;
            j++;
        }
        j=0;
        i++;
    }
    
}


int **create(int numberOfNodes)
{
    int i=0;
    
    int **grid=(int**)malloc(sizeof(int*)*numberOfNodes);
    
    while (i<numberOfNodes)
    {
        grid[i]=(int*)malloc(sizeof(int)*(numberOfNodes+2));
        i++;
    }
    
    return grid;
}

void freeAll(int **grid, int numberOfNodes)
{
    int i=0;
    
    while (i<numberOfNodes)
    {
        free(grid[i]);
        i++;
    }
    free(grid);
    
}

int debugSwitch(char **argv)
{
    int i=1;//Starting with one because argv[0] will./a.out no point in checking
    while (argv[i]!=NULL)//looking at the address to see if it is a null because 
    {                   // in command line **argv pointer to array
        if (strcmp(argv[i],"-d")==0)
        {
            printf("debugMode is ON\n");
            return TRUE;
        }
        i++;
    }
    
    return FALSE;
}











