//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures

#ifndef UNORDERED_H
#define UNORDERED_H

#include "Parent.h"

/*Child of Parent and comments in Parent.h*/
class Unordered: public Parent
{
public:
    void setTag();
    int Get(int);
    void Insert(int);
    void Remove(int);
    
};


#endif


