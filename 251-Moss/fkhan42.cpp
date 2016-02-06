//FAYAZ KHAN
//655427236
//Proj 2 Like what


#include <dirent.h>  //this library assits in the opening of dir and .txt files
#include <stdio.h>
#include <cassert>    // for assert
#include <string.h> //for strcmp
#include <cctype> //for isalnum library function
#include <stdlib.h>

/*-----------------------------------------
 Author: Fayaz Khan 
 UIN:655427236
 Date: 2/23/2015, UIC CS 251 Data StructuresProgram: #2, Like What
 System: Xcode i7 Mac, 8GB RAM
 Lab: Thurs 11am
 
 DID NOT RUN WITH LARGE DATA SET
 Running with the medium data set with string length of 20 takes 0m12.067s.
 Running with the small data set with string length of 20 takes 0m31.790s.
 
 
 --------------------------------------------------*/


/*--------------------------------------
    The OBJECTIVE:
    The objective to this program is to ask the user the string length, directory and number of pairs to
    display. This program takes several .txt files and compares them to each other to find the most
    similair. An example would be Moss
 ----------------------------------------*/

/*-----------------------
    The Process:
    The process for this program is to create a struct that has .txt file name, array of char, number of char,
    and the name of .txt combined with directory. The struct is malloced to how ever many .txt files are present.
    The files in directory with "." as first char are ignored. The program reads the .txt file twice 
    once for counting the legal char(No space, no punctuation), then mallocs size of legal char. After mallocing 
    the .txt file is read into the array. 
 
    Several functions to handle the inbetween steps to process the objective
 
 -------------------------------------*/


# define TRUE 1//These two for the debugMode, not necessary easeir to read true and false
# define FALSE 0


typedef struct nameContent
{
    char nameF[20];//Name of the txt file
    char *location;//array of char that will be malloced to the size of NumbofChar
    int NumbOfChar;//Number of legal char no space and no punctuation
    char NameFull[50];//this is the directory and txt file together ex: small/abc.txt
    int numbofBlocks;
    char **blocksOfChar;
}content;

typedef struct mossKeeper
{
    int txtNumA;
    int txtNumB;
    int hit;
}moss;
/* struct moss this is to keep track the similarites between two file.txt. This struct will be malloced
    based on how ever many text files*/



int debugMode;// Made this a  Global variable, the alternative is to put in every function

int debugSwitch(char **argv);//These checks the command line and looks for d flag

DIR *specifyDirLengthPairs(char sml[], int *stringLength, int* displayPairs);//This function ask the user to specify the directory small medium or large.this function also asks for string length and pairs. Returns pointer

int ListFileNames(DIR * theDirectory);//Displays all .txt file in directory and return how many there are

content* allocateSpaceStruct(int count);//take in size of how many structs we want based on how many txt files we
//have and then returns a pointer

void readInFileNames(content *tableofContents,DIR * theDirectory, char sml[]);
/*  readInFileNames this function stores the names of .txt file into the array of struct*/

void ListFileNameStruct(content *tableofContents, int fileCount);
/*ListFileNamesStruct this function is to make sure all file names are properly stored in the struct*/

void combineDIRandTxtName(content *tableofContents, char sml[], int fileCount);
/*combineDIRandTxtname this uses sprintf and takes directory file name and .txt name and 
    combines the two into one string ex:%s/%s and this is stored in the struct(NameFull) */

void numbValidChar(content *tableofContents,int fileCount);
/*numbValidChar this counts legal char(NO white space and puntuation) by using a counter and alnum library function
  and takes the number of legal charand puts them in the array of struct(NumbofChar) */

void mallocSpaceChar(content *tableofContents, int fileCount);
/*mallocSpaceChar takes numbValidChar founded earlier from the funtion numbValidChar and mallocs 
 for each individule .txt file plus 1 for EOF*/

void readInChar(content *tableofContents, int fileCount);
/*readInChar at this point the .txt will read in .txt file into the array that was malloced in 
 a function and will only read in the legal char. This is done by only incrementing if the char is 
 legal. If char is not legal the counter for the array does not increase thus will be rewritten 
over till a legal char is found. Also makes everything lowercase using "tolower" library functiom */

void freeAll(content *tableofContents, int fileCount,moss* mossKeeper);
/* freeAll this free all the arrays for the individule .txt files and will also free the array
    of struct. Thus will prevent memory leakage. We are also freeing in mallocBlocksofChar read
    function description for more info*/

void numberofBlocks(content *tableofContents,int stringLength,int fileCount);
/* numberofBlocks this function we determine the size of the array for each .txt file. 
 The new array memory will be allocated in the future but not in this function. 
 The result will be stored in the struct "numbOfBlocks "*/

void mallocBlocksofChar(content *tableofContents, int fileCount, int stringLength);
/* mallocBlocksofChar: this function will consist of several other funtions
    all this in a seperate funtion:
        int this function it statically malloc an array of char* and then again for char
    another function will read in char from previous array in blocks into designated place
    
    at the end of this function the previous array of char will be freed.
 */

void readInBlocksofChar(content *tableofContents, int stringLength, int txtFile);
/*readInBlocksofChar this will be called from function mallocBlocksofChar reasioning is in above
  description for mallocBlocksofChar*/

void sortBlocksChar(content *tableofContents,int fileCount);
/*sortBlocksChar this will sort the block of string not the contents inside but
    the array for the individule text files using qsort*/

int cstring_cmp(const void *a, const void *b);
/*cstring_cmp borrowed from Prof.Reed this is used for q-sort function*/


void searchBlocks(content* tableofContents, int fileCount);
/*searchBlocks this function take the array blocks and sorts it by alphabetical
    order and does it for all the seperate array files */

int mossCounter(int fileCount);
/* mossCounter this function will count the number of comparison that will be need to 
 compare all text file but not doing dublicates. Then malloc the struct "moss" based on comparisons*/

moss* mossMalloc(int fileCount,int *mossSpace);
/* mossMalloc  Then malloc the struct "moss" based on the return value of mossCounter.
 in this one function it makes other function call to mossCounter and readMossTxt*/

void readMossTxt(int* mossSpace,int fileCount, moss* mossKeeper);
/* readMossTxt this function reads in the possible combinations of txt files into struct use for further comparison*/

void Bsearch(moss* mossKeeper,content* tableofContents, int mKindex, int stringLength);
/*Bsearch function uses binary search utilizing the strcmp function it takes txtA and compare to txtB,C,D...
    if their is a match it will increase the counter in mosskeeper*/

int BsearchSeek(char target[],moss* mossKeeper,content* tableofContents, int mKindex, int stringLength);
/*BsearchSeek this funtion is with in Bsearch this takes one string from txtA and bsearch all
 of txtB and returns a 1(if found ) or 0 not found  */

void diplayTop(int displayPairs,moss* mossKeeper, int mossSpace,content* tableofContents);
/*diplayTop display based on user preference on top matches wants to see max 5
    prints */

void intro();
/*intro prints out name, assigment relevant course stuff*/

int main(int argc, char **argv)
{
    debugMode= debugSwitch(argv);//either TRUE or FALSE
    DIR           *theDirectory;
    struct dirent *aFile;
    char inFileName[12];
    FILE *inFile;
    content *tableofContents;//point to the structs
    int fileCount;//number of .txt files
    char sml[7]; //the user will specify small,medium or large
    int stringLength;
    int displayPairs;
    int mossSpace;
    

    intro();
    
    theDirectory=specifyDirLengthPairs(sml,&stringLength,&displayPairs);
    
    tableofContents= allocateSpaceStruct(fileCount=ListFileNames(theDirectory));
    
    readInFileNames(tableofContents, theDirectory, sml);
    
    combineDIRandTxtName(tableofContents, sml, fileCount);
    
    numbValidChar(tableofContents,fileCount);
    
    mallocSpaceChar (tableofContents, fileCount);
    
    readInChar(tableofContents,fileCount);
    
    numberofBlocks(tableofContents,stringLength,fileCount);
    
    mallocBlocksofChar(tableofContents,fileCount, stringLength);
    
    sortBlocksChar(tableofContents,fileCount);
    
    moss* mossKeeper=mossMalloc(fileCount,&mossSpace);

    int mKindex=0;
    while(mKindex<mossSpace)
    {
        //printf("mkindex::%d,,txtA:%d,,txtB::%d\n",mKindex ,mossKeeper[mKindex].txtNumA,mossKeeper[mKindex].txtNumB);
        
        Bsearch(mossKeeper,tableofContents,mKindex,stringLength);
        mKindex++;
    }
    
    diplayTop(displayPairs,mossKeeper,mossSpace,tableofContents);
    
    freeAll(tableofContents,fileCount,mossKeeper);
    
    return 0;
 
}

/*
 typedef struct nameContent
 {
 char nameF[20];
 char *location;
 int NumbOfChar;
 char NameFull[50];//this is the directory and txt file together ex: small/abc.txt
 int numbofBlocks;
 char **blocksOfChar;
 }content;
 
 */

/*typedef struct mossKeeper
{
    int txtNumA;
    int txtNumB;
    int hit;
}moss;*/

void intro()
{
    printf("\nAuthor: Fayaz Khan\n");
    printf("System: Xcode on Mac i7 8gb ram\n");
    printf("Lab Thur 11am\n\n");
    
    printf("Running with the Large data set with string length of 20 takes Very long time.On local Machine\n\n");
    printf("Running with the medium data set with string length of 20 takes 0m12.067s.On local Machine\n\n");
    printf("Running with the small data set with string length of 20 takes 0m31.790s.On local Machine\n\n");

}


void diplayTop(int displayPairs,moss* mossKeeper, int mossSpace,content* tableofContents)
{
    int i=0;
    int j=0;
    int max=0;
    int temp=0;
    //printf("Most similar %d pairs and number of matching strings are: \n",displayPairs);
    while (i<displayPairs)
    {
        //printf("toop\n");
        while (j<mossSpace)
        {
            //printf("bottom\n");
            if(mossKeeper[j].hit>max)
            {
                max=mossKeeper[j].hit;
                temp=j;
            }
            j++;
        }
        //printf("after while loop\n");
        printf("%s & %s %d\n",tableofContents[mossKeeper[temp].txtNumA].nameF,tableofContents[mossKeeper[temp].txtNumB].nameF,mossKeeper[temp].hit);
        //printf("after print statement\n");
        mossKeeper[temp].hit=0;
        temp=0;
        max=0;
        j=0;
        i++;
    }

    printf("\nDone with program, exiting...\n\n");
}

int BsearchSeek(char target[],moss* mossKeeper,content* tableofContents, int mKindex, int stringLength)
{
    int top=tableofContents[mossKeeper[mKindex].txtNumB].numbofBlocks-1;//we did this because size does not account for index 0 that why we subtract 1

    int bot=0;//starts at index 0
    char test[20];
    int value;
    int i=0;
    int j=0;
    while (top>=bot)
    {
        while (j<=stringLength)
        {
            test[j]=tableofContents[mossKeeper[mKindex].txtNumB].blocksOfChar[(((top-bot)/2)+bot)][j];
            j++;
        }
        
        //printf("BsearchSeek after j<stringLength:: %s\n",test);
        
        j=0;
        //strcpy(test,tableofContents[mossKeeper[mKindex].txtNumB].blocksOfChar[(((top-bot)/2)+bot)]);
        
        value=strcmp(target,test);
        
        if(debugMode)
            printf("in BsearchSeek::loop:::top>=bot and value::%d, top::%d, bot::%d\n",value,top,bot);
        
        if (value==0)
        {
            if(debugMode)
              printf("DebugMode in BsearchSeek:: %s vs %s\n",target,test);
            
            return 1;
        }
        
        if (value>0)
        {
            if(debugMode)
                printf("in top top BsearchSeek::loop:::top>=bot and value::%d, top::%d, bot::%d\n",value,top,bot);
        
            bot=(((top-bot)/2)+bot)+1;
            
            if(debugMode)
                printf(" Top bottom BsearchSeek::loop:::top>=bot and value::%d, top::%d, bot::%d\n",value,top,bot);
        }
        else
        {
 
            if(debugMode)
                printf("in bot top BsearchSeek::loop:::top>=bot and value::%d, top::%d, bot::%d\n",value,top,bot);
            
            
            top=(((top-bot)/2)+bot)-1;
            
            if(debugMode)
                printf("bot bot BsearchSeek::loop:::top>=bot and value::%d, top::%d, bot::%d\n",value,top,bot);
        }
        
    }
    /*if(debugMode)
        printf("in function BsearchSeek::target:%s\n",target);*/
    return 0;
}

void Bsearch(moss* mossKeeper,content* tableofContents, int mKindex, int stringLength)
{
   //printf("\nSearching Sorted Array with Binary method\n");
    int i=0;
    int j=0;
    int txtlimitA=tableofContents[mossKeeper[mKindex].txtNumA].numbofBlocks;
    char target[20];
    int match=0;
    
    while (i<txtlimitA)
    {
        if(debugMode)
            printf("in function Bsearch in loop i<txtlimitA:::%d,,i::%d\n",txtlimitA,i);
        
        while (j<=stringLength)
        {
            target[j]=tableofContents[mossKeeper[mKindex].txtNumA].blocksOfChar[i][j];
            j++;
        }
        //printf("Bsearch after j<stringLength:: %s\n",target);
        //strcpy(target,tableofContents[mossKeeper[mKindex].txtNumA].blocksOfChar[i]);
        
        if(debugMode)
            printf("in function Bsearch in loop i<txtlimitA after function\n");
        
        if(BsearchSeek(target,mossKeeper,tableofContents,mKindex,stringLength))
            match++;
        
        j=0;
        i++;
    }

    mossKeeper[mKindex].hit=match;
    

    //printf("in Bsearch::struct MossKeeper.hit::%d\n",mossKeeper[mKindex].hit);
    
}

void readMossTxt(int* mossSpace,int fileCount, moss* mossKeeper)
{
    int i =0;
    int j=1;
    int count=0;
    while (i<fileCount)
    {
        while (j<fileCount)
        {
            mossKeeper[count].txtNumA=i;
            mossKeeper[count].txtNumB=j;
            if(debugMode)
                printf("IN readMossTxt txtA:%d, txtB:%d\n",mossKeeper[count].txtNumA,mossKeeper[count].txtNumB);
            j++;
            count++;
        }
        i++;
        j=1+i;
    }
    if(debugMode)
        printf("In readMossTxt:: after while loop\n");
}

moss* mossMalloc(int fileCount, int* mossSpace)
{
    moss* temp= (moss*)malloc(sizeof(moss)*(*mossSpace=mossCounter(fileCount)));
    readMossTxt(mossSpace,fileCount,temp);
    return temp;
}

int mossCounter(int fileCount)
{
    int i =0;
    int j=1;
    int count=0;
    while (i<fileCount)
    {
        while (j<fileCount)
        {
            j++;
            count++;
        }
        i++;
        j=1+i;
    }
    return count;
}

void searchBlocks(content* tableofContents, int fileCount)
{
    int i=0;
    int j=0;
    while(i<fileCount)
    {
        while(j<tableofContents[i].numbofBlocks)
        {
            if(strstr(tableofContents[i].blocksOfChar[i],*tableofContents[j].blocksOfChar)!=NULL)
                i++;
            j++;
        }
        i++;
    }
    printf("%s",tableofContents[i].blocksOfChar[i]);
}

int cstring_cmp(const void *a, const void *b)
{
    // cast from void * to char **
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    // strcmp functions works exactly as expected from comparison function
    return strcmp(*ia, *ib);
}

void sortBlocksChar(content *tableofContents,int fileCount)
{
    /*to use qsort the for element to this 
     base:Pointer to the first object of the array to be sorted;
     num:Number of elements in the array pointed by base;
     size:Size in bytes of each element in the array;
     compar:Pointer to a function that compares two elements.
     */
    
    int i=0;

    while (i<fileCount)
    {
        qsort(tableofContents[i].blocksOfChar,tableofContents[i].numbofBlocks,sizeof(char**),cstring_cmp);
        i++;
    }
    
}
void readInBlocksofChar(content *tableofContents, int stringLength, int txtFile)
{
    int index=0;
    int oriTxt=0;
    int j=1;
    while (oriTxt<stringLength)
    {
        tableofContents[txtFile].blocksOfChar[index][oriTxt]=tableofContents[txtFile].location[oriTxt];

        /*if(debugMode&&txtFile==1)
            printf("In readInBlocksofChar: first while loop:%c\n",tableofContents[txtFile].blocksOfChar[index][oriTxt]);
        */
        oriTxt++;
        
    }
    
    index++;

    if(debugMode)
        printf("\n");
    
    while (index<tableofContents[txtFile].numbofBlocks)
    {
        while(j<stringLength)
        {
            tableofContents[txtFile].blocksOfChar[index][j-1]=tableofContents[txtFile].blocksOfChar[index-1][j];
            
            /*if(debugMode&&txtFile==1)
                printf("In readInBlocksofChar: second while loop:%c,j::%d,stringL::%d\n",tableofContents[txtFile].blocksOfChar[index][j-1],j,stringLength);
            */
            j++;
        }
        tableofContents[txtFile].blocksOfChar[index][j-1]=tableofContents[txtFile].location[oriTxt];
        
        /*if(debugMode&&txtFile==1)
            printf("In readInBlocksofChar: After while loop:%c\n",tableofContents[txtFile].blocksOfChar[index][j-1]);
        */
        
        oriTxt++;
        j=1;
        index++;

    }
}

void freeAll(content *tableofContents, int fileCount,moss* mossKeeper)
{
    int i=0;
    int j=0;
    
    while (i<fileCount)
     {
         while(j<tableofContents[i].numbofBlocks)
         {
             free(tableofContents[i].blocksOfChar[j]);
             j++;
         }
         j=0;
         i++;
     }
    i=0;
    
    while(i<fileCount)
    {
        free(tableofContents[i].blocksOfChar);
        i++;
    }
    
    free(tableofContents);
    free(mossKeeper);
}

void mallocBlocksofChar(content *tableofContents, int fileCount, int stringLength)
{
    int i=0;
    int j=0;
    while (i<fileCount)
    {
        tableofContents[i].blocksOfChar=(char**)malloc(sizeof(char*)*(tableofContents[i].numbofBlocks));
        while (j<tableofContents[i].numbofBlocks)
        {
            tableofContents[i].blocksOfChar[j]=(char*)malloc(sizeof(char)*(stringLength));
            j++;
        }
        
        readInBlocksofChar(tableofContents,stringLength, i);

        j=0;
        free(tableofContents[i].location);
        i++;
    }
}

void numberofBlocks(content *tableofContents,int stringLength,int fileCount)
{
    int i=0;
    int temp=0;
    while (i<fileCount)
    {
        /*I made this a 3 step process because it is easier to read and understand and did not
            want to use a library function*/
        
        temp=(tableofContents[i].NumbOfChar)/(stringLength);//this just get rid of char that is smaller than stringLength
        if(debugMode)
            printf("\nIn numberofBlocks function: NumbofChar:%d, stringlength:%d, temp:%d\n",tableofContents[i].NumbOfChar,stringLength,temp);
            
        temp=temp*(stringLength);//takes the whole number temp and multiplies by stringlength.
        tableofContents[i].numbofBlocks=temp-(stringLength)+1;
        
        if(debugMode)
            printf("\nIn numberofBlocks function: After calc numbofblocks::%d\n",tableofContents[i].numbofBlocks);
        
        i++;
    }
}


void readInChar(content *tableofContents, int fileCount)
{
    FILE *inFile;
    int i=0;
    int j=0;
    //char temp[1];
    if(debugMode)
        printf("I am in readInChar Funtion before while loop\n");
        
    while (i<fileCount)
    {
        if(debugMode)
            printf("I am in readInChar Funtion int 1st while loop\n");
        
        inFile = fopen( tableofContents[i].NameFull, "r");
        assert(inFile);
        while(fscanf(inFile,"%c",&tableofContents[i].location[j])!=EOF)
        {//    isalnum
            if(isalnum(tableofContents[i].location[j]))
            {
                tableofContents[i].location[j]=tolower(tableofContents[i].location[j]);//Lowercase everything
                
                /*if(debugMode)
                    printf("%c",tableofContents[i].location[j]);*/
                
                j++;
            }
            
        }
    
        if(debugMode)
            printf("\nIn readinChar func file name:%s, read in amount of char:%d\n",tableofContents[i].nameF,j);
        fclose(inFile);
        j=0;
        i++;
    }

}

void mallocSpaceChar (content *tableofContents, int fileCount)
{
    int i =0;
    if(debugMode)
        printf("I am mallocSpaceChar function\n");
    while (i<fileCount)
    {
        tableofContents[i].location=(char*)malloc(sizeof(char)*(tableofContents[i].NumbOfChar)+1);//plus 1 is for EOF
        i++;
    }
}

void numbValidChar(content *tableofContents,int fileCount)//DONE TESTING
{
    FILE *inFile;
    int i=0;
    int j=0;
    char temp[1];
    
    while (i<fileCount)
    {
        inFile = fopen( tableofContents[i].NameFull, "r");
        assert(inFile);
        while(fscanf(inFile,"%c",&temp[0])!=EOF)
        {
            if(isalnum(temp[0]))
            {
                /*if(debugMode)
                    printf("%c",temp[0]);*/
                j++;
            }
           
        }

        tableofContents[i].NumbOfChar=j;
        if(debugMode)
            printf("\nIn numbValidChar func file name:%s, Numb of valid char:%d\n",tableofContents[i].nameF,tableofContents[i].NumbOfChar);
        fclose(inFile);
        j=0;
        i++;
    }
    
}



void combineDIRandTxtName(content *tableofContents, char sml[], int fileCount)
{
    int i=0;
 
    while (i<fileCount)
    {
        sprintf(tableofContents[i].NameFull,"%s/%s",sml,tableofContents[i].nameF);
        if (debugMode)
            printf("\nIn combineDIRandTxtName function:: %s\n",tableofContents[i].NameFull);
        i++;
    }
}

void ListFileNameStruct(content *tableofContents, int fileCount)
{
    int i =0;
    while (i<fileCount)
    {
        printf("%s\n", tableofContents[i].nameF);
        i++;
    }
    printf("\n");
}

void readInFileNames(content *tableofContents, DIR * theDirectory, char sml[])
{
    if(debugMode)
        printf("IN read in filename function\n");
    theDirectory =opendir(sml);//we closed this in listnames function, this returns a pointer
                                //if you dont do it this way it may work but it like getting a new address
    struct dirent *aFile;
    int i =0;
    if (theDirectory != NULL)
    {
        //printf("In f loop\n");
        while ((aFile = readdir( theDirectory)) != NULL)
        {
            //printf("IN 2nd loop\n");
            if(aFile->d_name[0]!='.')
            {
                if(debugMode)
                    printf("%s\n", aFile->d_name);  // This is the file name
                strcpy(tableofContents[i].nameF, aFile->d_name);
                i++;
            }
            
        }
        
        closedir( theDirectory);
        return;
    }
    
    fprintf(stderr,"Directory is pointing to NULL, in readInFileNames function\n");
}


DIR *specifyDirLengthPairs(char sml[], int *stringLength, int* displayPairs )
{
    printf("Which directory would you like small, medium or large:");
    //char sml [7];
    int i=0;
    do
    {
        if(i>0)
            printf("Please specify directory with correct spelling\n");
        scanf("%s",sml);
        i++;
    }while(strcmp(sml,"small")&&strcmp(sml,"medium")&&strcmp(sml,"large"));
    
    
    do
    {
        printf("Please enter a string length between 1-20:\n");
        scanf("%d",stringLength);
        
        if(debugMode)
            printf("\nIn specifyDIRLengthPairs function, string lenght is:%d\n",*stringLength);
        
    }while(*stringLength<=0||*stringLength>20);
    
    do
    {
        printf("Please enter number(1-5) of pairs to display:");
        scanf("%d",displayPairs);
        
        if(debugMode)
            printf("\nIn specifyDIRLengthPairs function, displayPairs is:%d\n",*displayPairs);
        
    }while(*displayPairs<=0||*displayPairs>5);
    
    return opendir(sml);

}


int ListFileNames(DIR * theDirectory)
{
    
    struct dirent *aFile;
    int i =0;
    if (theDirectory != NULL)
    {
        //printf("\nContents of Directory:\n");
        while ((aFile = readdir( theDirectory)) != NULL)
        {
            if(aFile->d_name[0]!='.')
            {
                //printf("%s\n", aFile->d_name);  // This is the file name
                i++; //this counts how many valid files there are
            }
            
        }
        closedir( theDirectory);
        printf("\n");
        //*fileCount=i;
        printf("Their are %d txt file in this directory.Processing...\n\n",i);
        return i;
        
    }
    fprintf(stderr,"Directory is pointing to NULL, in ListfileNames function\n");
    exit(-1);
    
}

content* allocateSpaceStruct(int count)
{
    content *temp= (content*)malloc(sizeof(content)*(count));
    return temp;

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



