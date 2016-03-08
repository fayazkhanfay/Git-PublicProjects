//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures

#ifndef QUEUE_H
#define QUEUE_H

#include "Parent.h"

/*Child of Parent and comments in Parent.h*/
class Queue: public Parent
{
    public:
        int Get (int);
        void Insert(int);
        void setTag();
        void Remove(int);
};


#endif


