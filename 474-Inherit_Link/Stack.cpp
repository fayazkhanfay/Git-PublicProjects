//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures

#include "Stack.h"

#include <iostream>
#include <fstream> // for reading in file

using namespace std;


void Stack::Remove(int spot)
{
    if(!isEmpty())
    {
        pop_front();
        cout <<" Value removed from Stack\n";
    }
    else
        cout <<"\nStack is empty\n";
}


void Stack::Insert(int val)
{
    NODE *handle = new NODE();
    
    handle->value = val;
    handle->next = l->front;
    l->front = handle;
}


void Stack::setTag()
{
    tag[0] = 's';
}


int Stack::Get(int spot)
{
    if(!isEmpty())
    {
        return l->front->value;
    }
    
    return -999;
}


