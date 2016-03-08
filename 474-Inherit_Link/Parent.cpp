//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures


#include "Parent.h"

#include <iostream>
#include <fstream> // for reading in file

using namespace std;


bool Parent::isEmpty()
{
    if(l->front == NULL)
        return true;
    else
        return false;
}


void Parent::pop(int spot)
{
    int count = 1;
    NODE *handle = l->front;
    NODE *temp_handle = NULL;
    
    if(isEmpty()||Size()< spot)
        cout << "The list does not contain the needed position\n";
    else
    {
        if(spot == 1)
        {
            pop_front();
            return;
        }
        
        while (count < spot-1)
        {
            handle = handle->next;
            count++;
        }
        
        temp_handle = handle->next;
        handle->next = temp_handle->next;
        delete(temp_handle);
    }
}


void Parent::pop_front()
{
    NODE *handle = l->front;
    
    if(l->front == NULL)//Nothing to pop
        return;
    else
    {
        l->front= handle->next;
        cout <<"Pop "<< handle->value<< endl;
        delete(handle);
    }
}


char Parent::getTag()
{
    return tag[0];
}


Parent::~Parent()
{
    while(!isEmpty())
        pop_front();
    
    delete l;
    cout <<"Completely destructed\n";
}


Parent::Parent()
{
    l= new LIST;
    l->front = NULL;
}


int Parent::Size()
{
    NODE *handle =  l->front;
    int count = 0;
    
    while(handle !=NULL)
    {
        handle = handle->next;
        count++;
    }
    
    return count;
}


void Parent::ListInfo()
{
    NODE *handle =  l->front;
    
    cout<<"\n";
    while(handle !=NULL)
    {
        cout << handle->value<<" ";
        handle = handle->next;
    }
    
    cout<<"\nThe total number of items: "<< this->Size()<<"\n";
    
}


