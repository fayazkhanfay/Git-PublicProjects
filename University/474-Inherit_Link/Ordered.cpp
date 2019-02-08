//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures

#include "Ordered.h"

#include <iostream>
#include <fstream> // for reading in file

using namespace std;

void Ordered::Insert(int val)
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
    
    if(handle->next == NULL || handle->value >= val)
    {
        if(handle->value <= val )
            handle->next = child;
        else
        {
            child->next = handle;
            l->front = child;
        }
        
        return;
    }
    
    while (handle != NULL)
    {
        if( val >= handle->value )
        {
            if(handle->next == NULL)
            {
                handle->next = child;
                return;
            }
            
            if(val <= handle->next->value )
            {
                child->next = handle->next;
                handle->next = child;
            }
        }
        handle = handle->next;
    }
    
}


void Ordered::Remove(int spot)
{
    if(!isEmpty())
        pop(spot);
    else
        cout<<"\nOrdered list is empty\n";
    
}


void Ordered::setTag()
{
    tag[0] = 'o';
}


int Ordered::Get(int spot)
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


