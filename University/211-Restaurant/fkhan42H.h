/*  Code for the user interface for Lab 3 for CS 211 Spring 2015
 *
 *  Author: FAYAZ KHAN
 *  Date: 2/26/15
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>// this is for isspace and isdigit


typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;// TRUE=1 and YES = 1
/*if (s==FALSE){print "0"}*/


boolean debugMode;// Made this a  Global variable, the alternative is to put in every function

boolean debugSwitch(char **argv);//These checks the command line and looks for d flag

typedef struct waitList wL;

typedef struct node
{
    char nameGroup[50];
    int numInGroup;
    boolean resStatusIn;//whether the group has called ahead or is waiting in the restaurant
    struct node *next;
}NODE;

struct waitList
{
    NODE *head;
    NODE *tail;
};

/*FUNCTION DESCRIPTIONS: are in fkhan42B.c*/

/*Borrowed code written from CS141 and CS211 Proj2 */

boolean lst_sanity1(wL* waitL);//makes sure the both top and bottom are not pointing at null when thier is a NODE present
//useful for when traversing through links

boolean lst_sanity2(wL* waitL);//check if back of link list is present and it the next is pointing to null

boolean lst_sanity3(wL* waitL);//makes sure the first node of list and last node is reachable by traversing

int lst_len(wL* waitL);//Returns number of nodes in the link list
/*---------------------------------*/

/* forward definition of functions */
void clearToEoln();

int getNextNWSChar ();

int getPosInt ();

char *getName();

void doAdd (wL* waitL);

void doCallAhead (wL* waitL);

void doWaiting (wL* waitL);

void doRetrieve (wL* waitL);//NOT DONE!!!

void doList (wL* waitL);

void doDisplay (wL* waitL);

void printCommands();

void addToList (wL* waitL, int size,char* name, boolean inRest);

boolean doesNameExist (wL* waitL, char *name);

boolean updateStatus (wL* waitL, char *name);

char *retrieveAndRemove(wL* waitL, int size);//NOT DONE!!!

int countGroupsAhead (wL* waitL, char* name);

void displayGroupSizeAhead (wL* waitL, char* name);

void displayListInformation (wL* waitL);

wL *createHeadTail();

void freeAll(wL* waitL);

