//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures


#include "Queue.h"

#include <iostream>
#include <fstream> // for reading in file

using namespace std;

void Queue::Remove(int spot)
{
    if(!isEmpty())
    {
        pop_front();
        cout <<" Value removed from Queue\n";
    }
    else
        cout <<"\nQueue is empty\n";
}


void Queue::setTag()
{
    tag[0] = 'q';
}


void Queue::Insert(int val)
{
    NODE* handle = l->front;
    
    NODE *child = new NODE();
    child->value = val;
    child->next = NULL;
    
    if(handle == NULL)
    {
        l->front = child;
        return;
    }
    
    while (handle->next != NULL)
        handle = handle->next;
    
    handle->next = child;
}


int Queue::Get (int spot)
{
    if(!isEmpty())
    {
        return l->front->value;
    }
    
    return -999;
}



