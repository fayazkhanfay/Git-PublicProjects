//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures

#ifndef MAIN_H
#define MAIN_H

#include <string>
using namespace std;

/*Comments in main_functions.cpp*/
bool quitProg(char options);
void helpProg();
void aboutProg();
bool verify_listNum(int listNum);
bool verify_type(char type);
int stringLength(string optionString);
Parent *CreateChild(char type);
void freeMem(Parent *children);


#endif

