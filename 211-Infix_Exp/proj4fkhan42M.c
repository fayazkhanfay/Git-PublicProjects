/*  Code for the user interface for Lab 4 for CS 211 Spring 2015  
 *
 *  Author: Pat Troy
 *  Original Date: 10/13/2013
 */

/*
    FAYAZ KHAN
    655427236
 */

#include "proj4fkhan42.h"

void processExpression (token inputToken, FILE *in)
{
 /**********************************************/
 /* Declare both stack head pointers here      */
    stack* stackV= createStackDummy();
    stack* stackOP= createStackDummy();
    
 /* Loop until the expression reaches its End */
 while (inputToken.type != EOLN)
   {
    /* The expression contains an OPERATOR */
    if (inputToken.type == OPERATOR)
      {
    
          if(debugMode)
              printf ("OP:%c, " ,inputToken.op);
          
          if(inputToken.op=='(')
              push(stackOP,inputToken.op);
          
          if(inputToken.op=='+'||inputToken.op=='-')
          {
              while(!isEmpty(stackOP)&&(top(stackOP)=='+'||top(stackOP)=='-'||top(stackOP)=='*'||top(stackOP)=='/'))
              {
                  popAndEval(stackV,stackOP);
              }
              push(stackOP,inputToken.op);
          }
          
          if(inputToken.op=='*'||inputToken.op=='/')
          {
              while(!isEmpty(stackOP)&&(top(stackOP)=='*'||top(stackOP)=='/'))
                  popAndEval(stackV,stackOP);
              
              push(stackOP,inputToken.op);
          }
          
          if(inputToken.op==')')
          {
              while(!isEmpty(stackOP)&&top(stackOP)!='(')
                  popAndEval(stackV,stackOP);
              
              if(isEmpty(stackOP))
                  fprintf(stderr,"Error in processExpression stackOP is empty\n");
              else
                  pop(stackOP);
          }
      }

    /* The expression contain a VALUE */
    else if (inputToken.type == VALUE)
      {
          if(debugMode)
              printf ("Val: %d, ", inputToken.val);

          push(stackV,inputToken.val);
      }
   
    /* get next token from input */
    inputToken = getInputToken (in);
   } 

 /* The expression has reached its end */
    while(!isEmpty(stackOP))
        popAndEval(stackV,stackOP);
    
    printf("result:%d\n",top(stackV));
    
    pop(stackV);
    
    if(!isEmpty(stackV))
        fprintf(stderr,"Error StackV is not empty invalid expression\n");
    
    freeAll(stackV,stackOP);
    
 printf ("\n");
}


/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

token getInputToken (FILE *in)
{

 token retToken;
 retToken.type = QUIT;

 int ch;
 ch = getc(in);
 if (ch == EOF)
   return retToken;
 while (('\n' != ch) && isspace (ch))
   {
    ch = getc(in);
    if (ch == EOF)
      return retToken;
   }
 
 /* check for a q for quit */
 if ('q' == ch)
   {
    retToken.type = QUIT;
    return retToken;
   }

 /* check for a ? for quit */
 if ('?' == ch)
   {
    retToken.type = HELP;
    return retToken;
   }

 /* check for the newline */
 if ('\n' == ch)
   {
    retToken.type = EOLN;
    return retToken;
   }

 /* check for an operator: + - * / ( ) */
 if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
   {
    retToken.type = OPERATOR;
    retToken.op = ch;
    return retToken;
   }
   
 /* check for a number */
 if (isdigit(ch))
   {
    int value = ch - '0';
    ch = getc(in);
    while (isdigit(ch))
      {
       value = value * 10 + ch - '0';
       ch = getc(in);
      }
    ungetc (ch, in);  /* put the last read character back in input stream */
    retToken.type = VALUE;
    retToken.val = value;
    return retToken;
   }
      
 /* else token is invalid */
 retToken.type = ERROR;
 return retToken;
}

/* Clear input until next End of Line Character - \n */
void clearToEoln(FILE *in)
{
 int ch;
 
 do {
     ch = getc(in);
    }
 while ((ch != '\n') && (ch != EOF));
}

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

int main (int argc, char **argv)
{
   debugMode= debugSwitch(argv);//only modification

 char *input;
 token inputToken;
 printf ("Starting Expression Evaluation Program\n\n");
 printf ("Enter Expression: ");

 inputToken = getInputToken (stdin);
 while (inputToken.type != QUIT)
   {
    /* check first Token on Line of input */
    if(inputToken.type == HELP)
      {
       printCommands();
       clearToEoln(stdin);
      }
    else if(inputToken.type == ERROR)
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       clearToEoln(stdin);
      }
    else if(inputToken.type == EOLN)
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
    else 
      {
       processExpression(inputToken, stdin);
      } 

    printf ("\nEnter Expression: ");
    inputToken = getInputToken (stdin);
   }

 printf ("Quitting Program\n");
 return 1;
}
