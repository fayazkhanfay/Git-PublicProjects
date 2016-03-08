//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures

#include "Unordered.h"

#include <iostream>
#include <fstream> // for reading in file

using namespace std;

void Unordered::Remove(int spot)
{
    if(!isEmpty())
        pop(spot);
    else
        cout<<"\nUnordered list is empty\n";
}


void Unordered::Insert(int val)
{
    
    NODE *handle = new NODE();
    
    handle->value = val;
    handle->next = l->front;
    l->front = handle;
    
}


void Unordered::setTag()
{
    tag[0] = 'u';
}


int Unordered::Get(int spot)
{
    NODE* handle = l->front;
    int count = 1;
    
    if(isEmpty()||Size()< spot)
        return -999;
    else
    {
        while (count != spot )
        {
            handle = handle->next;
            count++;
        }
        return handle->value;
    }
}



