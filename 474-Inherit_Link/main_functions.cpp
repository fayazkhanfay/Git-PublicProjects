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


/*Creates Child and sets a tag for object. Returns a pointer to object */
Parent *CreateChild(char type)
{
    Parent* handle = NULL;
    
    if(type == 'u')
        handle = new Unordered();
    
    if(type == 'o')
        handle = new Ordered();
    
    if(type == 'q')
        handle = new Queue();
    
    if(type == 's')
        handle = new Stack();
    
    handle->setTag();
    
    return handle;
}

/*To check if user enters type correctly*/
bool verify_type(char type)
{
    if(type == 'u'|| type =='o'||type =='q'|| type == 's')
        return true;
    else
        return false;
}

/* returns string length */
int stringLength(string optionString)
{
    int count = 0;
    
    while(optionString[count] != '\0')
    {
        count++;
    }
    return count--;
}

/*checks if user specified correct index in Parent array*/
bool verify_listNum(int listNum)
{
    
    if(listNum>=1 && listNum<=8)
        return true;
    else
        return false;
    
    
}

/*Fayaz Khan information*/
void aboutProg()
{
    cout << "\nFayaz Khan\nfkhan42\n655427236\nCS474 \nProj 2 C++ Linked List\n2/27/16 \n\n";
}

/*Helps user by displaying option menu*/
void helpProg()
{
    cout << "\nq – Quit the program\n\n";
    cout << "h – Help\n\n";
    cout << "a – About\n\n";
    cout << "s <listNum> <type> – Set list number <listNum> to be of type <type>\n\n";
    cout << "i <listNum> <val> - Insert value <val> into list numbered <listNum>\n\n";
    cout << "r <listNum> - Remove a value from list numbered <listNum>\n\n";
    cout << "g <listNum> - Get a value from list numbered <listNum>\n\n";
    cout << "l <listNum> - List information about list numbered <listNum>\n\n";
    cout << "f <filename> - Read commands from the file in <filename>\n\n";
    cout << "# comment - Ignore the information contained on this line\n\n";
    
}

/*User wants to quit program*/
bool quitProg(char options)
{
    if(options == 'q')
        return false;
    else
        return true;
}


