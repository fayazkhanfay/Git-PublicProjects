#include <stdlib.h>
#include <fstream>   // needed for file operations
#include <cassert>    // for assert
#include <string.h>// for strcpy and strcmp
#include <cctype>
using namespace std;

/*
 Author: FAYAZ KHAN
 Date: 4/20/2015, UIC CS 251 Data Structures
 Program #5, Trie Again
 System: Xcode i7 Mac, 8GB RAM
 Lab: Thur 11am Paul Murray
 
 TODO:
    Store all n words from Shakespeare in a Trie, allowing the user to 
    lookup words.  
 
    Using the same Shakespeare file provided from the previous assignment.
 */

#define ABC 26

typedef struct node
{
    int isWord;
    char letter;
    node *children[ABC];
}Node;


/*dislayInfo: Prints out information about author and assignment per rubric*/
void displayInfo();

/*validfile: hardcode will.txt check if valid and returns a pointer
 to the filename*/
FILE *validfile();

/*grabString: this function will majority of the work happens. In the function
 determine when a string starts and ends by white space and ignores punctuation.
    Then will make calls to findOrInsert to process word.*/
void grabString(FILE *input, Node* root, int *count);

/*createNode: creates a node puts in the letter and put 1(yes) or 0 for isWord
    for ex: joe vs joes and also their is a counter for every node being
    created. The array of pointer are all set to NULL*/
Node *createNode(int isWord, char letter, int *count);

/*findOrInsert: this is called from grabstring and will find the
    word in Trie and not do anything or insert a string of nodes handled in 
 newBranch or the nodes are all ready there but the isWord need to be set to 1*/
void findOrInsert(char * key, Node* root, int *count);

/*newBranch: creates nodes by calling to createNode function and return
    the addresss of the first node created to findOrInsert function 
    so it can be connected to previous node*/
Node *newBranch(char *restOfKey, int *count);

/*sum_UserString: this was created because of being frustarated with strcmp
    add the the sum of all char values in the string and return the sum
    the value be used to compare 'x' or 'X' for exiting the program
    also asks the user for input */
int sum_UserString(char *userString);

/*retrieve: this search through the Trie and determines whether it is found
    or not based on the user's input*/
int retrieve(char* userString, Node* root);

/*freeAll: Using recursion it free all the nodes in the Trie*/
void freeAll(Node* root);

/*findandRetrieve: asks the user for a new input by calling sum_UserString
 then calls retrieve the return from the retrieve will be for the switch
    then will display result*/
void findandRetrieve(Node* root);

int main()
{
    int count =0;
    
    displayInfo();
    FILE *input = validfile();
    
    Node *root = createNode(0,'\0',&count);//Handle with Dummy values
    grabString(input,root, &count);
    
    findandRetrieve(root);
    
    freeAll(root);
    
    return 0;
}

/*
 typedef struct node
 {
 int isWord;
 char letter;
 node *children[ABC];
 }Node;
 */

void findandRetrieve(Node* root)
{
    
    char userString[40];
    int test_x =sum_UserString(userString);
    
    while((test_x !='x') && (test_x!='X'))
    {
        switch (retrieve(userString,root))
        {
            case 1:
                printf("%s is found.\n\n",userString);
                break;
            case 0:
                printf("%s is NOT found.\n\n",userString);
                break;
            default:
                printf("Error Switch\n");
                exit(-1);
        }
    
        test_x =sum_UserString(userString);
    }
    
    printf("Exiting program...\n\n");
}


void freeAll(Node* root)
{
    int i=0;
    
    while (i<ABC)
    {
        if(root->children[i]!=NULL)
            freeAll(root->children[i]);//RECURSION!!!!
        i++;
    }
    
    free(root);
}

int retrieve(char* userString, Node* root)
{
    Node *traverse= root;
    
    int i=0;
    while (1)
    {
        if(traverse==NULL)
            return 0;
        
        if(isdigit(userString[i]))
        {
            printf("not found\n");
            return 0;
        }
        
        if(userString[i]=='\0'&&traverse->isWord==1)
            return 1;//found
        
        if(userString[i]=='\0'&&traverse->isWord==0)
            return 0;//Not found
        
        traverse=traverse->children[userString[i]-97];
        i++;
    }
    
    return -1;
}

int sum_UserString(char userString[])
{
    int i =0;
    int sum=0;
    
    printf("Enter a word to lookup or x to exit: ");
    scanf("%s",userString);
    
    while (userString[i]!='\0')
    {
        sum= sum + userString[i];
        i++;
    }
    return sum;
}

Node *newBranch(char *restOfKey, int *count)
{
    int i=0;
    Node *node;
    Node *handle;

    do
    {
        if(i==0)
        {
            node= createNode(0, restOfKey[i], count);
            handle = node;
        }
        else
        {
            node->children[restOfKey[i]-97]= createNode(0, restOfKey[i], count);
            node = node->children[restOfKey[i]-97];
        }
        
    }while(restOfKey[++i]!='\0');
    
    node->isWord = 1;
    
    return handle;
}

void findOrInsert(char * key,Node* root, int *count)
{
    int i =0;
    Node * traverse= root;
    
    while (1)
    {
        if(i==0)
        {
            if(traverse->children[key[i]-97]==NULL)
            {
                traverse->children[key[i]-97] = newBranch(key,count);
                return;
            }
            
            traverse= traverse->children[key[i]-97];
            i++;
        }
        
        if(key[i]=='\0')
        {
            traverse->isWord=1;
            return;
        }
        
        if(traverse->children[key[i]-97]==NULL)
        {
            traverse->children[key[i]-97] = newBranch(&key[i],count);
            return;
        }
        
        traverse = traverse->children[key[i]-97];//97 value of A in ASCII
        i++;
     
    }
    
    printf("ERROR IN FindOrInsert funtion\n");
    exit(-1);
}

Node *createNode(int isWord, char letter, int* count)
{
    Node *alphaBlock = (Node*)malloc(sizeof(Node));
    
    alphaBlock->isWord=isWord;
    alphaBlock->letter=letter;
    
    int i =0;
    while (i<ABC)
    {
        alphaBlock->children[i] = NULL;
        i++;
    }
    
    (*count)++;
    
    return alphaBlock;
}


FILE *validfile()
{
    FILE *finput; // input file
    
    finput = fopen( "will.txt", "r");
    if( finput == NULL) {
        printf("File open failed.  Exiting program...\n");
        exit( -1);
    }
    
    printf("Reading words from file will.txt into Trie...\n");
    return finput;
}

void grabString(FILE *input,Node* root, int* count)
{
    
    int sizeString = 0;
    int max =0;
    char cTest[1];
    char * key= NULL;
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
                findOrInsert(key,root,count);
                sizeString=0;
                free(key);
                key=NULL;
            }
        }
        
        
    }
    
    printf("Created %d Trie Nodes.\n\n",*count);
    
    fclose(input);
}

void displayInfo()
{
    printf("\nAuthor: FAYAZ KHAN\n");
    printf("Date: 4/20/2015, UIC CS 251 Data Structures\n");
    printf("Program #5, Trie Again\n");
    printf("System: Xcode i7 Mac, 8GB RAM\n");
    printf("Lab: Thur 11am Paul Murray\n\n");
}