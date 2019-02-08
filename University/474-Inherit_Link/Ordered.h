//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures


#ifndef ORDERED_H
#define ORDERED_H

#include "Parent.h"

/*Child of Parent and comments in Parent.h*/
class Ordered: public Parent
{
public:
    int Get (int);
    void setTag();
    void Remove(int);
    void Insert(int);
};


#endif



