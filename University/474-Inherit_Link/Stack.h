//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures

#ifndef STACK_H
#define STACK_H

#include "Parent.h"

/*Child of Parent and comments in Parent.h*/
class Stack: public Parent
{
public:
    int Get(int);
    void setTag();
    void Insert(int);
    void Remove(int);
    
};

#endif


