//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures


#include "Parent.h"
#include "main.h"
#include "Queue.h"
#include "Ordered.h"
#include "Stack.h"
#include "Unordered.h"
#include <iostream>
#include <string>
#include <fstream> // for reading in file

using namespace std;


int main()
{
    int listNum;            //specify location in children array
    string optionString;    //getline will insert into string
    char options[1];        //parse only first char of optionString
    ifstream myfile;        //For reading in file
    int length;             //string Length of optionString
    char type[1];           //parse string of object type
    bool diplayError = true;//if user incorrectly enter in string
    int val;                //the value for inserting into link
    

    Parent *children[8];    //hold all of class objects
    
    
    while(quitProg(options[0])) //Does not segfault even thought their is no value attached to var options
    {
        /*Reset values*/
        options[0]= '\0';
        listNum = -999;
        type[0] = '\0';
        val = -999;
        diplayError = true;
        
        if(myfile.eof())// Reached end of file
            myfile.close();
        
        //if file is not open
        if(!myfile.is_open())
        {
            cout << "Please enter option: ";
            getline(cin, optionString);
        }
        else
            getline(myfile, optionString);//when file is open
        
        //account for when user enters uppercase
        options[0] = tolower(optionString[0]);
        length = stringLength(optionString);
        
        //To prevent parsing empty space
        if(length>=3)
            listNum = atoi(&optionString[2]);
        
        if(length>=5)
        {
            if(isdigit(optionString[4]))
                val = atoi(&optionString[4]);
            else
                type[0] = tolower(optionString[4]);
        }
        
        /****Menu of Options*****/
        
        //Quit
        if(options[0] == 'q')
            diplayError = false;
        
        //Help
        if (options[0] == 'h')
        {
            helpProg();
            diplayError = false;
        }
        
        //About
        if (options[0] == 'a')
        {
            aboutProg();
            diplayError = false;
        }
        
        //Comment
        if (options[0] == '#')
        {
            //cout <<"\nComment line\n";
            diplayError = false;
        }
        
        //Reading of file, extra condition to make sure doesn't recurse back into itself
        if(options[0] == 'f' && !myfile.is_open())
        {
            
            char filename[50];
            int count = 2;
            
            while (count < optionString.length())
            {
                filename[count-2] =optionString[count];
                count++;
            }
            
            string str(filename);
            
            //myfile.open(str);
            myfile.open(str.c_str());
            if(!myfile.is_open())
                cout << "File open NOT succesful\n";
            
            diplayError = false;
        }
        
        /*s <listNum> <type>*/// Creates an object in placed into array.
                              // Also will remove object and links when user requests to replace
        if(options[0] == 's' && verify_listNum(listNum) && verify_type(type[0]))
        {
            //cout <<"\nSet is properly workiing\n";
            
            if(children[listNum-1]== NULL)
                children[listNum-1] = CreateChild(type[0]);
            else
            {
                children[listNum-1]->~Parent();             //Will remove object and links
                children[listNum-1] = CreateChild(type[0]); //replaced with new object in same location
            }
            
            diplayError = false;
        }
        
        /*i <listNum> <val>*///Insert links
        if(options[0] == 'i' && val != -999 && verify_listNum(listNum))
        {
            //cout <<"\nInsert value is properly workiing\n";
            
            //The child object has to be created first then insert links
            if(children[listNum-1]== NULL)
                cout<< "\nError Please set first\n";
            else
                children[listNum-1]->Insert(val);
            
            
            diplayError = false;
        }
        
        /*r <listNum>*///remove links
        if(options[0] == 'r' && verify_listNum(listNum))
        {
            //cout <<"\nRemove is properly workiing\n";
            
            int spot = 0;
            string test;
            
            if(children[listNum-1]== NULL)
                cout<< "\nError Please set first\n";
            else
            {
                //cout <<"my letter is printing ::"<<children[listNum-1]->getTag();
               
                //User enters value for Ordered and Unorderd class
                if(children[listNum-1]->getTag()=='o'|| children[listNum-1]->getTag()=='u')
                {
                    cout <<"\nPosition in the list to be removed ";
                    
                    if(!myfile.is_open())
                        getline(cin, test);
                    else
                        getline(myfile, test);
                    
                    spot = atoi(&test[0]);
                    cout <<endl;
                    
                }
                
                children[listNum-1]->Remove(spot);
            }
            
            diplayError = false;
        }
        
        /*g <listNum>*/// retrieve value from a specific link or first pending on object
        if(options[0] == 'g' && verify_listNum(listNum))
        {
            //cout <<"\nget value is properly workiing\n";
            
            int display_get;
            int spot = 0;
            string test;
            
            if(children[listNum-1]== NULL)
                cout<< "\nError Please set first\n";
            else
            {
                
                //User enters value for Ordered and Unorderd class
                if(children[listNum-1]->getTag()=='o'|| children[listNum-1]->getTag()=='u')
                {
                    cout <<"\nPosition in the list to be retrieved ";
                    if(!myfile.is_open())
                        getline(cin, test);
                    else
                        getline(myfile, test);
                    
                    spot = atoi(&test[0]);
                    cout <<endl;
                }
                
                
                display_get = children[listNum-1]->Get(spot);
                
                if(display_get == -999)
                    cout <<"list does not contain the needed position\n";
                else
                    cout << "Retrieved value: " << display_get << endl;
                
            }
            
            diplayError = false;
        }
        
        /*l <listNum>*///displays the whole link list
        if(options[0] == 'l' && verify_listNum(listNum))
        {
            //cout <<"\nlist info is properly workiing\n";
            
            if(children[listNum-1]== NULL)
                cout<< "\nError Please set first\n";
            else
                children[listNum-1]->ListInfo();
            
            
            diplayError = false;
        }
        
        
        if(diplayError && isalnum(options[0]))
            cout <<"\nInvalid entry\n" ;
        
    }
    
    
    cout << "\nYou have succesfully quit program. Good bye \n\n" ;
    
    
    int count =0;
    
    /*Goes through parent array and pops link till empty. Then destruct object*/
    while (count < 8)
    {
        if(children[count]!= NULL)
            children[count]->~Parent();
        
        count++;
    }
 
    
    
    myfile.close();
    
    
    return 0;
}



