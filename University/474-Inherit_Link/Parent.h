//Fayaz Khan
//CS474-Proj 2
//2/29/16 Spring 2016
//Inheritance of Linear Linked Data Structures

#ifndef PARENT_H
#define PARENT_H

/*Struct for the link list*/
typedef struct list_struct LIST;
typedef struct node
{
    int value;
    struct node *next;
}NODE;

/*Handle to head of list*/
struct list_struct
{
    NODE *front;
};


/*Top of Inheritance*/
class Parent
{
    protected:
        LIST *l;                    //Point to head of link list
        char tag[1];                //to keep track of object type
    public:
        Parent();                   //constructor
        virtual int Get(int)=0;     //retrieve value from node
        virtual void Insert(int)=0; //insert node
        virtual void Remove(int)=0; //remove node
        virtual void setTag()=0;    //set type of object
        void ListInfo();            //Dispaly value of each nodes and display number of links
        void pop_front();           //removes head link
        void pop(int);              //removes chosen link
        int Size();                 //Return of links
        char getTag();              //returns 'char' of type tag
        bool isEmpty();             //check if l->front is pointing to NULL
        ~Parent();                  //Destructor: pops links till empty, delete LIST and delete object
};


#endif


