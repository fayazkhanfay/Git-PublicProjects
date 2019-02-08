#include <fstream>   // needed for file operations
#include <stdlib.h>
#include <cassert>    // for assert
#include <cctype>
#include <math.h> //for pow specificially QuadMethod
#include <string.h>// for strcpy and strcmp
using namespace std;

/*---------------------------
 Author: Fayaz Khan
 UIN:655427236
 Date: 4/7/2015, UIC CS 251 Data StructuresProgram: #4, Hashing
 System: Xcode i7 Mac, 8GB RAM
 Lab: Thurs 11am TA: Paul Murray
 
 TO DO:
 Creat a program that will store all the distinct words using
 different method of Hash tables : Linear, Quadaratic and Chaining
 Print out the number of collision for each table size and method
 Determine what is the best method and print
 
 
 NOTE:
 This script may seem like it will hang after printing the initial display
 but give it about 30 secondes for each row of printing
 
 --------------------------------*/


# define TRUE 1//These two for the debugMode
# define FALSE 0

/*NameContent: same struct will be used for all methods Hashing*/
typedef struct nameContent
{
    char word[40];
    struct nameContent* next;
}content;

/*combination: is just for keeping track the best combination*/
typedef struct combination
{
    int method;
    long int crash;//collisions
    int sizeOfTable;//tableSize
}bestCombo;

/*dislayInfo: Prints out information about author and assignment per rubric*/
void displayInfo();

int debugMode;// Made this a  Global variable for for -d flag

int debugSwitch(char **argv);//These checks the command line and looks for dflag

/*validfile: hardcode will.txt check if valid and returns a pointer
 to the filename*/
FILE *validfile();


/***stringLengthCount*** this function is never called during the execution of
 program but this was used to determine the longest string in the .txt file
 the result was 39 after ingnoring punctuation and using isspace()
 to determine the start and end of a word*/
void stringLengthCount(FILE *input);

/*create_HashColumn : mallocs an x amoount of the struct. In for the individual 
    variables in the struct they are given dummy values *next =null
    and word='\0' this will be repeatedly called for all method of insertion*/
content* create_HashColumn(int size);

/*storeString: this function will majority of the work happens. Within this 
 functiin in will make function calls to insertChainMethod, insertLinerMethod
  and insertQuadMethod but not all at the same time. The method will be 
 specified before entering function by using a switch
 
 Also in this function determine when a string starts and ends by white space
    and ignores punctuation
 
 returns number of collisions
 
 also makes a function call to bestCombinations()
 */
long int storeString(FILE *input, content* baskets, int sizeContent,
                int switchCase, bestCombo *bestCom);

/* hashFunction: simple algorithem of adding up the ASCII values of individual
    char in the string and take the higest value ASCII value
    and the positions and muliply them together and add to ASCII
    value returning the sum
 */
int hashFunction(char *key, int sizeString);

/*insertChainMethod: check to see if the string is distinct in the location
    if space occupied will traverse through nodes to see if distinct till null
    it will create a node and store the relevent data and be pointed by
    the last node*/
void insertChainMethod(int hash,content* baskets, char *key, int *count,
                       int sizeString, long int *collisions);

/*freeAll_Chain: makes function call to pop and countnodes. Counts up the 
    nodes in specific index then calls the pop function that many times
 */
void freeAll_Chain(content* baskets, int sizeContent);

/*countNodes: counts up all the nodes by traversing through the nodes
    till null and returns number of nodes*/
int countNodes(content* traverse);

/*pop: this frees the node by traversing till node->next ==null that node
    is freed and the previous node is ->next is set to null*/
void pop(content* traverse);

/*insertLinearMethod: check initaial locaton to see if string is distinct 
    if not match at location will traverse thorugh array till either empty
    spot and then will be stored there or will look for a match 
    Also counts number of collisions
 */
void insertLinearMethod(int hash,content* baskets, char* key, int *count,
                        int sizeString, int sizeContent, long int *collisions);

/*insertQuadMethod: check initaial locaton to see if string is distinct
 if not match at location will traverse thorugh array using n^2 either empty
 spot and then will be stored there or will look for a match
 Also counts number of collisions
 */
void insertQuadMethod(int hash,content* baskets, char* key, int *count,
                      int sizeString, int sizeContent, long int *collisions);

/*displayText: this will print the top portion of the display ex: coloum info*/
void displayText();

/*bestCombination: this will compare the previous lowest collision to 
    the current collision and if the collisions are lower it will 
    update the struct */
void bestCombination(bestCombo *bestCom, int sizeContent,long int collisions,
                     int switchCase);

/*displayBest: will print the best combination of table size and method*/
void displayBest(bestCombo *bestCom);

int main(int argc, char **argv)
{
    /*
    Used for testing purposes
     
    FILE *input= validfile();;
    stringLengthCount(input);
    return 0;
    */
    
    displayInfo();
    
    bestCombo * bestCom = (bestCombo*)malloc(sizeof(bestCombo));
    bestCom->crash=0;
    
    displayText();
    
    int test = 0;
    int switchCase = 0;
    int tableSize[] = {35267,42557,52579,57223,65071};
    FILE *input;
    content *baskets;
    while(test<5)
    {
        printf("%d\t  ",tableSize[test]);

        while(switchCase<3)
        {
            input= validfile();
            baskets = create_HashColumn(tableSize[test]);
            printf(" %ld  ",storeString(input, baskets, tableSize[test],
                                        switchCase,bestCom));
            
            if(switchCase==2)
                freeAll_Chain(baskets, tableSize[test]);
            
            free(baskets);
            switchCase++;
        }
        
        printf("\n");
        switchCase=0;
        test++;
    }
    
    displayBest(bestCom);
    
    return 0;
    
}

/*
typedef struct combination
{
    int method;
    long int crash;//collisions
    int sizeOfTable;//tableSize
}bestCombo;*/

void displayBest(bestCombo *bestCom)
{
    
    printf("\nThe best combination is:\n");
    printf("\tTable Size %d\n",bestCom->sizeOfTable);
    
    switch (bestCom->method)
    {
        case 0:
            printf("\tCollision handling using: Linear \n");
            break;
        case 1:
            printf("\tCollision handling using: Quadaratic \n");
            break;
        case 2:
            printf("\tCollision handling using: Chaining \n");
            break;
        default:
            printf("ERROR: in main switch \n");
            break;
    }
    
    printf("Hashing function used was adding all char ASCII value in string\n");
    printf(" and taking the higest value ASCII and multiply by the position\n");
    printf(" and add them together\n");
    
    printf("\nExiting program...\n");

}

void bestCombination(bestCombo *bestCom, int sizeContent, long int collisions,
                     int switchCase)
{
  
    if(bestCom->crash==0||collisions < bestCom->crash)
    {
        bestCom->crash= collisions;
        bestCom->method = switchCase;
        bestCom->sizeOfTable = sizeContent;
    }
    
}

void displayText()
{
    printf("Reading from file will.txt\n\n");
    
    printf("Number of collisions for different table sizes are:\n");
    printf("Table Size    Linear   Quadratic   Chaining\n");
    printf("----------  ---------  ---------  ---------\n");
}

long int storeString(FILE *input, content* baskets, int sizeContent,
                int switchCase, bestCombo *bestCom)
{
    
    int sizeString = 0;
    int max =0;
    char cTest[1];
    int hash=0;
    char * key= NULL;
    int count =0;
    long int collisions=0;
    assert(input);
    
    while (fscanf(input,"%c",&cTest[0])!=EOF)
    {
        if(key==NULL)
            key = (char*)malloc(sizeof(char)*40);
        
        if(isalpha(cTest[0]))
        {
            
            key[sizeString]= tolower(cTest[0]);
            sizeString++;
        }
        else
        {
            
            if(isspace(cTest[0])&&sizeString>0)
            {
                
                key[sizeString]='\0';
                hash = hashFunction(key, sizeString);
                
                switch (switchCase)
                {
                    case 0:
                        insertLinearMethod(hash,baskets, key,&count,sizeString,
                                           sizeContent,&collisions);
                        break;
                    case 1:
                        insertQuadMethod(hash,baskets, key,&count,sizeString,
                                         sizeContent, &collisions);
                        break;
                    case 2:
                        insertChainMethod(hash,baskets, key, &count,
                                          sizeString, &collisions);
                        break;
                    default:
                        printf("ERROR in switch StoreString\n");
                        break;
                }
                
                sizeString=0;
                free(key);
                key=NULL;
            }
        }
        
        
    }
    
    bestCombination(bestCom, sizeContent, collisions,switchCase);
    
    //printf("unique word count::: %d\n",count);
    //printf("Number of collisoins :: %ld\n", collisions);
    fclose(input);
    return collisions;
}


void insertQuadMethod(int hash,content* baskets, char* key, int *count,
                        int sizeString, int sizeContent, long int *collisions)
{
    
    if(strcmp(baskets[hash].word,key)==0)
        return;
    
    if(baskets[hash].word[0]=='\0')
    {
        strcpy(baskets[hash].word,key);
        (*count)++;
        return;
    }
    
    long int i = 1;
    long int check= 1;
    int oriColToEdge= (sizeContent-hash)-1;
    long int testCheck;
    
    while(1)
    {
        (*collisions)++;
        
        if(check<=oriColToEdge)
        {
            if(strcmp(baskets[hash+check].word,key)==0)
                return;
            
            if(baskets[hash+check].word[0]=='\0')
            {
                strcpy(baskets[hash+check].word,key);
                (*count)++;
                return;
            }
            
        }
        else
        {
            check = (check - oriColToEdge);
            check = (check%sizeContent)-1;
            
            if(strcmp(baskets[check].word,key)==0)
                return;
            
            if(baskets[check].word[0]=='\0')
            {
                strcpy(baskets[check].word,key);
                (*count)++;
                return;
            }
        }
        
        i++;
        check = pow(i,2);
    }
    
}


void insertChainMethod(int hash,content* baskets, char* key, int *count,
                       int sizeString, long int *collisions)
{
    
    if(strcmp(baskets[hash].word,key)==0)
        return;
    
    if(baskets[hash].word[0]=='\0')
    {
        strcpy(baskets[hash].word,key);
        (*count)++;
        return;
    }
    content * traverse;
    
    (*collisions)++;
    
    if(baskets[hash].next != NULL)
    {

        traverse = baskets[hash].next;
        
        if(strcmp(traverse->word,key)==0)
            return;
        
        while (traverse->next!=NULL)
        {
            if(strcmp(traverse->word,key)==0)
                return;
            
            (*collisions)++;
            
            traverse=traverse->next;
        }
        
        if(strcmp(traverse->word,key)==0)
            return;
        
        (*collisions)++;
        
        content* node = (content*)malloc(sizeof(content));
        node->next=NULL;
        strcpy(node->word,key);
        traverse->next= node;
        (*count)++;
        return;
    }
    else
    {
        content* node = (content*)malloc(sizeof(content));
        node->next=NULL;
        strcpy(node->word,key);
        baskets[hash].next= node;
        (*count)++;
        return;
    }
    
    return;
 
}

void insertLinearMethod(int hash,content* baskets, char* key, int *count,
                        int sizeString, int sizeContent, long int *collisions)
{
    if(strcmp(baskets[hash].word,key)==0)
        return;
    
    if(baskets[hash].word[0]=='\0')
    {
        strcpy(baskets[hash].word,key);
        (*count)++;
        return;
    }
    
    int i = 1;
    
    while (hash+i<sizeContent)
    {
        (*collisions)++;
        if(strcmp(baskets[hash+i].word,key)==0)
            return;
        
        if(baskets[hash+i].word[0]=='\0')
        {
            strcpy(baskets[hash+i].word,key);
            (*count)++;
            return;
        }
        i++;
    }
    
    i=0;
    
    while (i<hash)
    {
        (*collisions)++;
        if(strcmp(baskets[i].word,key)==0)
            return;
        
        if(baskets[i].word[0]=='\0')
        {
            strcpy(baskets[i].word,key);
            (*count)++;
            return;
        }
        
        i++;
    }
    
    printf("\nLinear Method array not big enough to store content\n");
    exit(-1);
}

int countNodes(content* traverse)
{
    int count =0;
    
    while (traverse->next!=NULL)
    {
        traverse=traverse->next;
        count++;
    }
    
    return count;
}
void pop(content* traverse)
{
    
    while (traverse->next->next!=NULL)
        traverse=traverse->next;
    
    free(traverse->next);
    traverse->next=NULL;
}
void freeAll_Chain(content* baskets, int size)
{
    
    int i =0;
    int count=0;
    int j;
    
    while (i<size)
    {
        j=0;
        content *traverse = &baskets[i];
        count= countNodes(traverse);
        
        while (j<count)
        {
            pop(traverse);
            j++;
        }
        
        i++;
    }
}



int hashFunction(char * key,int sizeString)
{
    int i =0;
    int sum=0;
    int maxKey=0;
    int maxSpotKey;
    while (i<sizeString)
    {
        sum= sum + key[i];
        if(key[i]>=maxKey)
        {
            maxKey= key[i];
            maxSpotKey =i;
        }
        
        i++;
    }
    
    return sum+ (maxKey*maxSpotKey);
}


content* create_HashColumn(int size)
{
  
    content *baskets = (content*)malloc(sizeof(content)*size);
    
    int i=0;
    
    while(i<size)
    {
        baskets[i].word[0]='\0' ;
        baskets[i].next=NULL;
        i++;
    }
    return baskets;
}


void stringLengthCount(FILE *input)
{
    int i =0;
    char test[1];
    int max =0;
    
    assert(input);
    
    
    while (fscanf(input,"%c",&test[0])!=EOF)
    {
        if(isalpha(test[0]))
        {
  
            i++;
        }
        else
        {

            if(isspace(test[0]))
            {

                if(i>max)
                {
                    max=i;
                }
                i=0;
            }
        }
            
    }
    
    printf("your max lenght i::%d\n",max);
    fclose(input);
}

FILE *validfile()
{
    FILE *finput; // input file
    
    finput = fopen( "will.txt", "r");
    if( finput == NULL) {
        printf("File open failed.  Exiting program...\n");
        exit( -1);
    }

    return finput;
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

void displayInfo()
{
    printf("\nAuthor: FAYAZ KHAN\n");
    printf("Date: 4/07/2015, UIC CS 251 Data Structures\n");
    printf("Program #4, Hashing\n");
    printf("System: Xcode i7 Mac, 8GB RAM\n");
    printf("Lab: Thur 11am Paul Murray\n\n");
}