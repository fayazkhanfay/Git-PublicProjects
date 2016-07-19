//#include "csapp.h"
#define MAXARGS 128
#define MAXLINE 128

#include <sys/types.h>      //  for pid_t
#include <stdio.h>          //  for I/O
#include <stdlib.h>         //  for exit
#include <string.h>         //  for strcpy
#include <fcntl.h>	    //	for Read, Writing, Reading and Writing
#include <sys/stat.h>       //  above comment is with this library 		
#include <unistd.h>		
#include <signal.h>	    // this is for the signals SigINT SIGTSTP 

/*
 FAYAZ KHAN
 -Used shellex.c from book pg734-736 as skeleton code
 for this project
 
 */

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
pid_t Fork(void);
void unix_error(char *msg);
int redirect(char** filenameR);
int errno;//Global

char *displayG[MAXARGS];  //Global array for printing left of <.<<,>
void signalCheck(int signal);
void signalCheckB(int signal);

int main()
{
    char cmdline[MAXLINE]; /* Command line */
    
    while (1)
    {
        /* Read */
        printf("CS361 >");

	signal(SIGINT,signalCheck);/*From the book pg762*/
	signal(SIGTSTP,signalCheckB);

        fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
            exit(0);
        
        /* Evaluate */
        eval(cmdline);
    }
}

/*Checks for signals from the book pg762*/
void signalCheck(int signal)
{
	write(1, "catch sigint\nCS361 >", 50);
}

void signalCheckB(int signal)
{
	write(1, "catch sigtstp\nCS361 >", 50); 
}

int redirect(char** filenameR)
{

	int exitLoop =0;
	int trav = 0;
	while(filenameR[trav]!=NULL)
	{
		
//		displayG[trav]= filenameR[trav];
		//printf("test this:::: %s\n",displayG[trav]);			

		/*
			Portion of code below was taken from book pg863-864
		*/

		if(strcmp(filenameR[trav],"<")==0)
		{
			//printf("test Read");
			trav++;
			char* tempName = filenameR[trav]; 	
			int fd1 = open(tempName,O_RDWR,0644); //  
			dup2(fd1,STDIN_FILENO);

			return 1;
			exitLoop = 1;
		}

		if(strcmp(filenameR[trav],">")==0)
		{	
			//printf("\ntest open and writing\n");
			trav++;
			char* tempName = filenameR[trav];
			int fd1 = open(tempName,O_RDWR|O_CREAT|O_TRUNC,0644);//This is for reading and writing
			/*
				if file does not exist we create it and then we clear it.
				if file exists them we clear it. 
			*/
			dup2(fd1,STDOUT_FILENO);
			return 1;
			exitLoop =1;
		}

		if(strcmp(filenameR[trav],">>")==0)
		{	
			//printf("Test writing only");
			trav++;
			char* tempName = filenameR[trav];
			int fd1 = open(tempName,O_RDWR|O_CREAT|O_APPEND,0644); // this is for writing only 

			/*
				if file does not exist then we create it. 
				if file exists then it is added to the end of the file. 
			*/
			dup2(fd1,STDOUT_FILENO);
			exitLoop =1;
			return 1;
		}
/*
		if(filenameR[trav]== NULL)
			exitLoop=1;
*/
		
			displayG[trav]= filenameR[trav];
//			printf("inside inside loop::%s",displayG[trav]);


		trav++;
	}

//	int count = 0;
//	printf("before loop");
/*	while(displayG[count]!= NULL)
	{
		printf("outside loop::%s\n",displayG[count]);
		count++;
	}
*/		
	return 0;
}



/* eval - Evaluate a command line */
void eval(char *cmdline)
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE]; /* Holds modified command line */
    int bg; /* Should the job run in bg or fg? */
    pid_t pid; /* Process id */
    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)
        return; /* Ignore empty lines */
    
    
    if (!builtin_command(argv))
    {
	//        redirect(argv);
	if ((pid = Fork()) == 0)
        { /* Child runs user job */
           
	  redirect(argv);//1 idf succesfukl 	
	 if (execvp(displayG[0], displayG) < 0)
            {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
	
	
        }
	printf("pid%d ", pid); //this prints the pid 
        
        /* Parent waits for foreground job to terminate */
        if (!bg)
        {
            int status;
            if (waitpid(pid, &status, 0) < 0)
                unix_error("waitfg: waitpid error");
	
		printf("status:%d\n",status);// this prints the status 
        }
        else
            printf("%d %s", pid, cmdline);
    }
  

    return;
}



/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "exit")) /* quit command */// Changed this from quit to exit
        exit(0);
    if (!strcmp(argv[0], "&")) /* Ignore singleton & */
        return 1;
    
    
    return 0; /* Not a builtin command */
}

/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
{
    char *delim; /* Points to first space delimiter */
    int argc; /* Number of args */
    int bg; /* Background job? */
    
    buf[strlen(buf)-1] = ' '; /* Replace trailing ’\n’ with space */
    
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
        buf++;
    
    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    
    argv[argc] = NULL;
    
    if (argc == 0) /* Ignore blank line */
        return 1;
    
    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;
    
    return bg;
}

/*From the book pg718*/
pid_t Fork(void)
{
    pid_t pid;
    
    if ((pid = fork()) < 0)
        unix_error("Fork error");

    return pid;
}


/*From the book pg718*/
void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

