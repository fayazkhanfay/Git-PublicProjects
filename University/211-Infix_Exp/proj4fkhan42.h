#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

typedef enum {ERROR = 0, OPERATOR, VALUE, EOLN, QUIT, HELP} tokenType;

#define DUMMY -999

boolean debugMode;// Made this a  Global variable, the alternative is to put in every function

typedef struct tokenStruct
{
    tokenType type;
    char      op;
    int       val;
} token;

token getInputToken (FILE *in);

typedef struct Stack stack;

typedef struct node
{
    int value;
    struct node* next;
}NODE;

struct Stack
{
    NODE* top;
    NODE* bot;
};

stack* createStackDummy();

int isEmpty(stack *test);

void push(stack *add, int data);

void pop(stack *remove);

int top(stack *display);

void freeAll(stack* setFreeV,stack* setFreeOP);

void popAndEval(stack *stackV, stack* stackOP);

boolean debugSwitch(char **argv);

/*----Below functions are used for testing----*/

boolean lst_sanity1(stack* test);//makes sure the both top and bottom are not pointing at null when thier is a NODE present
//useful for when traversing through links

boolean lst_sanity2(stack* test);//check if back of link list is present and it the next is pointing to null

boolean lst_sanity3(stack* test);//makes sure the first node of list and last node is reachable by traversing

int lst_len(stack* test);//Returns number of nodes in the link list

