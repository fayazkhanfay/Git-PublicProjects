#include <stdio.h>
#include <iostream>   // for cin and cout in C++
#include <cassert>    // for assert
#include <climits>	  // to print out max sizes of different types
#include <cstring>    // for C string functions, like strcat
#include <ctype.h>     //tolower() so question and Question will be the same
#include <string.h>
#include <stdlib.h>
using namespace std;


/*
    Our algorithem elimanates data the useful and if there are duplicates it merges 
    with previous index. original entries 4,105,005 reduces down to 2,071,125 aroximatly half
 */


//const char inFileName[] = "very_short.csv";	 // input file name, at top for convenience
//const char inFileName[] = "words_that_start_with_q.csv";//all_words.csv
const char inFileName[] = "all_words.csv";
/*
 Handles all the .csv files
 */


/*
    the word length is added to struct, the length is put while the file is being read in using the 
    return from Uncapitalize function. The Uncap fucntion goes through whole string and makes lower case
    when hits sentinal will return the counter
 */

typedef struct DATA_set
{
    char word[30];	  		// The word
    int year;		  		// The year word was used
    int wordCount;	  		// How many times word was used
    int uniqueTextsCount;	// How many unique texts that word was used in
    int wordLength;         //How many character are in that word
}Data_set;

/*---------------------------------------*/
//FUNCTIONS:

Data_set* Create(int Space);//This the initial malloc

Data_set** Create_P(int Space);//This is the inital malloc for the pointers these point at the distinct words
                                //as the file is being read in

int Distint_Word(Data_set Data_Array[],Data_set **Data_Array_P,int size,int NumberOfDistinceW );


int UnCapitalize(Data_set Data_Array[],int i);//this uncapitalize the whole string and return length// more info above

void Display(Data_set Data_Array[],int size_P);//This prints out every thing in the array


Data_set *Inc_Cap(Data_set Data_Array[],int Space_size);//we used realloc to accomplish the and send back a pointer
Data_set **Inc_Cap_P(Data_set **Data_Array,int Space_size);//same as above but we sent back a **

long double avgWordLength(Data_set Data_Array[],int size);//more detail all the below by the function

long double* avgWordLength_ALL(Data_set Data_Array[],int size );

void freqAvg5_word(Data_set **Data_Array_P,int NumberOfDistinceW);

/*--------------------------------------------*/

int main()
{
    //This block prepares and inform user file weiil be read in
    FILE *inFile;
    printf("Opening input file %s \n", inFileName);
    printf("Contents of this file is Reading please be patient \n");
    inFile = fopen( inFileName, "r");	// Open for reading, hence the "r"
    assert( inFile);  					// make sure file open was OK
    
    
    
    //initial mallocs
    int Size_DataStruct=20000;
    Data_set *DataStruct= Create(Size_DataStruct);
    int Size_DistinctWord=1000;
    Data_set **Data_DistinctWord=Create_P(Size_DistinctWord);
    int Size_YearSearch= 1000;
    Data_set **Data_YearSearch=Create_P(Size_YearSearch);
    
    int i=0;//This will be also a counter for size of Array struct
    int NumberOfDistinceW=0;//counting the amount of distinct word
    
    
    /*
        since our range is only between 1801 -2000 we are not including them into the array
        but they are being read in temporarly if not with the range the counter or i does not increment
        potentially the same spot can be rewritten several time till the apporapraite data 
     
        benefits we reduced by half the entries 
     
     */
    //this part is the to get things started we do comparison we withn bounds//prevent seg faults
    while (i!=1)
    {
        fscanf( inFile, "%s %d %d %d", DataStruct[i].word, &DataStruct[i].year, &DataStruct[i].wordCount, &DataStruct[i].uniqueTextsCount);
        if (DataStruct[i].year>=1801&&DataStruct[i].year<=2000)
        {
            DataStruct[i].wordLength = UnCapitalize(DataStruct,i);//Uncap function returns leght and saved in struct
            
            NumberOfDistinceW=1;
            Data_DistinctWord[NumberOfDistinceW-1]=&DataStruct[i];
            

            int yearCounter= 0;
            
            i++;
        }
    }
    
    //---------------------------------------
    while( fscanf( inFile, "%s %d %d %d", DataStruct[i].word, &DataStruct[i].year, &DataStruct[i].wordCount, &DataStruct[i].uniqueTextsCount) != EOF)
    {
        //this portion is the same as above but not the whole entirity
        if(DataStruct[i].year>=1801&&DataStruct[i].year<=2000)
        {
            DataStruct[i].wordLength=UnCapitalize(DataStruct,i);
            
            if (i==Size_DataStruct-2)//if removed the -2 it will segfault because tolerance are tight for huge data
            {
                //this increase capacity by going into function realloc's and returns a potentially new address
                Size_DataStruct=Size_DataStruct*2;
                DataStruct=Inc_Cap(DataStruct,Size_DataStruct);
            }
            
            /*
                to lower the string comparison the years are compared because it is not a function call
                and the spot the year is older then qualifies for strcom
             */
            if (DataStruct[i].year<=DataStruct[i-1].year)
            {
                /*goes into function for stringcomparisons but it sends back
                    back an int if it is -1 that means it is distinct but if send back any number
                    that referenceing a **pointer array pointing at the start of our distinct words
                    so we know where the distinct word is and goes their 
                 
                    then it goes into the else portion of the below if statement 
                    and then tries to match up ther year by incrementing the pointer address
                    and comparing the new data coming to the previous data
                    
                    if the word and year matches and merges the two set of data
                    into previous spot and the new is not stored in a seperate index
                    
                 as  a resulte saving approximatly 300,000 of duplicates
                 
                */
                int temp=Distint_Word(DataStruct,Data_DistinctWord,i,NumberOfDistinceW);
                if (temp==-1)//this does string comparison with array of distinct words
                {
                    //printf("Other test\n");
                    NumberOfDistinceW++;
                    if (NumberOfDistinceW==Size_DistinctWord-5)
                    {
                        Size_DistinctWord=Size_DistinctWord*2;
                        Data_DistinctWord=Inc_Cap_P(Data_DistinctWord,Size_DistinctWord);
                    }
                    
                    Data_DistinctWord[NumberOfDistinceW-1]=&DataStruct[i];

                    //for example ::Data_DistinctWord[j]=&DataStruct[i];
                }
                else
                {
                    Data_set *tempAdd =Data_DistinctWord[temp];
                    
                    int getOut= 0;
                    while (strcmp(DataStruct[i].word,tempAdd->word)==0&&getOut==0)
                    {
                        //Data_set *tempAdd =&Data_DistinctWord[temp];
                        if (DataStruct[i].year==tempAdd->year)
                        {
                            tempAdd->wordCount=tempAdd->wordCount+DataStruct[i].wordCount;
                            tempAdd->uniqueTextsCount=tempAdd->uniqueTextsCount+DataStruct[i].uniqueTextsCount;
                            getOut=1;
                        }
                        //Data_DistinctWord[temp]->wordCount=Data_DistinctWord[temp]->wordCount+(DataStruct[i].wordCount);
                        tempAdd++;
                    }
                    getOut=0;
                    i--;
                }
            }
        
            i++;
        }
    }
    
 //------------------------------------------------------------------------
    
    
    fclose( inFile);
    printf("Author: Fayaz Khan \n");
    printf("Lab: Thur 11 am\n");
    printf("Program #1,Google NGram word count\n");
    printf("\nTotal number of distinct words:%d\n",NumberOfDistinceW);
    printf("The average word length is %.3Lf\n",avgWordLength(DataStruct,i));
    freqAvg5_word(Data_DistinctWord,NumberOfDistinceW);
    
   

    int DisplayYorN=0;
    printf("\nDisplay the full content of .csv file warning potentially very long list. 1 for yes\n");
    if (scanf("%d",&DisplayYorN)) {
        Display(DataStruct,i);
    }
    
    free(DataStruct);
    free(Data_DistinctWord);
    free(graphAvgWordAll);
    
}

void DisplayAvgWord_All(long double graphAvgWordAll[])/* Did not have enought time to complete graph*/
{
    int i =0;
    long double min=graphAvgWordAll[i];
    long double max=graphAvgWordAll[i];
    i++;
    while (i<40)
    {
        if (graphAvgWordAll[i]>max)
        {
            max=graphAvgWordAll[i];
        }
        
        if (graphAvgWordAll[i]<min)
        {
            min=graphAvgWordAll[i];
        }
        i++;
    }
    
}

long double *avgWordLength_ALL(Data_set Data_Array[],int size )/**/
{
    long double numerator[40];
    long double denominator[40];
    int i=0;
    int j=0;
    long double* freqAvg=(long double*)malloc(sizeof(long double)*40);
    while (j<40)
    {
        freqAvg[j]=0;
        numerator[j]=0;
        denominator[j]=0;
        j++;
    }
    int spot=0;
    while (i<size)
    {
        spot=(Data_Array[i].year-1801)/5;
        numerator[spot]=(long double)((Data_Array[i].wordCount)*(Data_Array[i].wordLength))+numerator[spot];
        denominator[spot]=(long double)Data_Array[i].wordCount+denominator[spot];
        i++;
    }
    i=0;
    
    int rangeLowYear=1801;
    int rangeHighYear=1805;
    
    while (i<40)
    {
        freqAvg[i]=numerator[i]/denominator[i];
        printf("The avg word length for all words and years from %d to %d is %Lf\n",rangeLowYear,rangeHighYear,freqAvg[i]);
        i++;
        rangeLowYear=rangeLowYear+5;
        rangeHighYear=rangeHighYear+5;
    }
    return freqAvg;
    //long double total=numerator/denominator;
}

void freqAvg5_word(Data_set **Data_Array_P,int NumberOfDistinceW)//Number 2
{
    char Word_search[30];
    printf("\nPlease enter a word you like frequency avg of: ");
    scanf("%s",Word_search);
    printf("\n");
    //printf("we enter %s\n",Word_search);
    int i =0;
    int freqAvg[40];
    while (i<40)
    {
        freqAvg[i]=0;
        i++;
    }
    
    i=0;
    while (strcmp(Data_Array_P[i]->word,Word_search)!=0)
    {
        
        i++;
        if (i==NumberOfDistinceW)
        {
            printf("Error:Not a word in our library\n");
            return;
        }
    }
    
    Data_set *temp=Data_Array_P[i];
    i =0;
    int rangeLowYear=1801;
    int rangeHighYear=1805;
    double sumWord=0.00;
    int rangeCounter=1;
    while (strcmp(temp->word,Word_search)==0&&rangeCounter!=40)
    {
        
        while (temp->year>=rangeLowYear&&temp->year<=rangeHighYear)
        {
            sumWord=temp->wordCount+sumWord;
            temp++;
        }
        freqAvg[i]= sumWord/(5);
        printf("The frequencey, avg for '%s' between years %d-%d is %d\n",Word_search,rangeLowYear,rangeHighYear,freqAvg[i]);
        i++;
        sumWord=0;
        rangeLowYear=rangeLowYear+5;
        rangeHighYear=rangeHighYear+5;
        rangeCounter++;
    }
    printf("\n");
}


/*
    avgWordLenght
    this function takes in the whole and ask user for the year and reprompts if out of range 
    this is a linear search of the whole array looking at the struct specifically the year 
    
    we handle the numerator and denominator seperatly after the whole thing is completed and 
    then those two are divided
 
    we are using long double because we hand large data and wanted to prevent overflow
 */

 long double avgWordLength(Data_set Data_Array[],int size )//for the year//COMPLETE this is #3
{
    int year_search=-1;

    while(year_search<1801||year_search>2000)
    {
        printf("Please enter a year between 1801-2000 you would like the avg word legth of: ");
        scanf("%d",&year_search);
    }
    
    long double numerator=0;
    long double denominator=0;
    int i=0;
    while (i<=size)
    {
        if(Data_Array[i].year==year_search)
        {
            numerator=((Data_Array[i].wordCount)*(Data_Array[i].wordLength))+numerator;
            denominator=Data_Array[i].wordCount+denominator;
        }
        i++;
    }
    
    
    long double total=numerator/denominator;
    
    return (long double)total;
}

int Distint_Word(Data_set Data_Array[],Data_set **Data_Array_P,int Wtest, int NumberOfDistinceW)
{
    //printf("I am in function\n");
    int i=0;
    char* Test_Word=Data_Array[Wtest].word;
    
    while (i<NumberOfDistinceW)
    {
        if (strcmp(Test_Word,Data_Array_P[i]->word)==0)
            return i;//NOT DISTINCT
    
        i++;
    }
 
    return -1;//this means it is distinct
    
}

Data_set **Inc_Cap_P(Data_set **Data_Array,int Space_size)
{
    Data_Array=(Data_set**)realloc(Data_Array,sizeof(Data_set*)*(Space_size));
    
    return Data_Array;
}

Data_set** Create_P(int Space)
{
    Data_set **space=(Data_set**)malloc(sizeof(Data_set*)*(Space));
    
    return space;
}

Data_set *Inc_Cap(Data_set Data_Array[],int Space_size)
{
    
    Data_Array=(Data_set*)realloc(Data_Array,sizeof(Data_set)*(Space_size));
    
    return Data_Array;
}

Data_set* Create(int Space)
{
    Data_set *space= (Data_set*)malloc(sizeof(Data_set)*(Space));
    return space;
}

int UnCapitalize(Data_set Data_Array[],int i)//return the length of the string or j to main we can store that
{
    int j=0;
    
    while (Data_Array[i].word[j]!='\0')
    {
        Data_Array[i].word[j]=tolower(Data_Array[i].word[j]);//the reason for the j is because word is an array
        j++;                                                //and check every work of the char array
    }
    return j;
}


void Display(Data_set Data_Array[],int size_P)
{
    int j=0;
    
    while(j<size_P)
    {
        printf( "%s %d %d %d %d\n",Data_Array[j].word, Data_Array[j].year,Data_Array[j].wordCount, Data_Array[j].uniqueTextsCount, Data_Array[j].wordLength);
        j++;
    }
}



