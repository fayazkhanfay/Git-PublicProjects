//Fayaz Khan
#include <fnmatch.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#define BACKLOG (10)


void usage(){
  fprintf(stderr,"Usage: ./homework5 [port number] [directory to serve]\n");
  exit(1);
}

/* char* parseRequest(char* request)
 * Args: HTTP request of the form "GET /path/to/resource HTTP/1.X" 
 *
 * Return: the resource requested "/path/to/resource"
 *         0 if the request is not a valid HTTP request 
 * 
 * Does not modify the given request string. 
 * The returned resource should be free'd by the caller function. 
 */
char* parseRequest(char* request) {
  //assume file paths are no more than 256 bytes + 1 for null. 
  char *buffer = malloc(sizeof(char)*257);
  memset(buffer, 0, 257);
  
  if(fnmatch("GET * HTTP/1.*",  request, 0)) return 0; 

  sscanf(request, "GET %s HTTP/1.", buffer);
  return buffer; 
}




char * getString = "HTTP/1.0 200 OK\r\n"
"Content-type: %s; charset=UTF-8\r\n\r\n";

char * indexHeader = "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"><html>"
"<title>Directory listing for %s</title>"
"<body>"
"<h2>Directory listing for %s</h2><hr><ul>";

char * errorDisp =  "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"><html>"
"<title>404: Webpage not Found</title>"
"<body>"
"<h2>404: Webpage not Found</h2><hr><ul>";

char * indexBody = "<li><a href=\"%s\">%s</a>";

char * indexFooter = "</ul><hr></body></html>";

void serve_request(int sock);


int readFile;
int readBytes;
int sockOffset = 0;
int status;


char sockBuffer[4096];
char sendFileBuffer[4096];
char filename[4096];
char * getFile;


struct stat s;
struct  dirent *dp;


void hallway(void);
void statusCond(int sock);


/* Your program should take two arguments:
 * 1) The port number on which to bind and listen for connections, and
 * 2) The directory out of which to serve files.
 */
int main(int argc, char** argv) {
    /* For checking return values. */
    int retval;

    /* Read the port number from the first command line argument. */
    if (argc != 3){
      usage();
    }
    int port = atoi(argv[1]);

    chdir(argv[2]);
    
    /* Create a socket to which clients will connect. */
    int server_sock = socket(AF_INET6, SOCK_STREAM, 0);
    if(server_sock < 0) {
        perror("Creating socket failed");
        exit(1);
    }

    /* A server socket is bound to a port, which it will listen on for incoming
     * connections.  By default, when a bound socket is closed, the OS waits a
     * couple of minutes before allowing the port to be re-used.  This is
     * inconvenient when you're developing an application, since it means that
     * you have to wait a minute or two after you run to try things again, so
     * we can disable the wait time by setting a socket option called
     * SO_REUSEADDR, which tells the OS that we want to be able to immediately
     * re-bind to that same port. See the socket(7) man page ("man 7 socket")
     * and setsockopt(2) pages for more details about socket options. */
    int reuse_true = 1;
    retval = setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &reuse_true,
                        sizeof(reuse_true));
    if (retval < 0) {
        perror("Setting socket option failed");
        exit(1);
    }

    /* Create an address structure.  This is very similar to what we saw on the
     * client side, only this time, we're not telling the OS where to connect,
     * we're telling it to bind to a particular address and port to receive
     * incoming connections.  Like the client side, we must use htons() to put
     * the port number in network byte order.  When specifying the IP address,
     * we use a special constant, INADDR_ANY, which tells the OS to bind to all
     * of the system's addresses.  If your machine has multiple network
     * interfaces, and you only wanted to accept connections from one of them,
     * you could supply the address of the interface you wanted to use here. */
    
   
    struct sockaddr_in6 addr;   // internet socket address data structure
    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(port); // byte order is significant
    addr.sin6_addr = in6addr_any; // listen to all interfaces

    
    /* As its name implies, this system call asks the OS to bind the socket to
     * address and port specified above. */
    retval = bind(server_sock, (struct sockaddr*)&addr, sizeof(addr));
    if(retval < 0) {
        perror("Error binding to port");
        exit(1);
    }

    /* Now that we've bound to an address and port, we tell the OS that we're
     * ready to start listening for client connections.  This effectively
     * activates the server socket.  BACKLOG (#defined above) tells the OS how
     * much space to reserve for incoming connections that have not yet been
     * accepted. */
    retval = listen(server_sock, BACKLOG);
    if(retval < 0) {
        perror("Error listening for connections");
        exit(1);
    }

    while(1) {
        /* Declare a socket for the client connection. */
        int sock;
        char buffer[256];
        const char * response = "HTTP/1.0 200 OK\r\n\r\nhello client!\n";

        /* Another address structure.  This time, the system will automatically
         * fill it in, when we accept a connection, to tell us where the
         * connection came from. */
        struct sockaddr_in remote_addr;
        unsigned int socklen = sizeof(remote_addr); 

        /* Accept the first waiting connection from the server socket and
         * populate the address information.  The result (sock) is a socket
         * descriptor for the conversation with the newly connected client.  If
         * there are no pending connections in the back log, this function will
         * block indefinitely while waiting for a client connection to be made.
         * */
        sock = accept(server_sock, (struct sockaddr*) &remote_addr, &socklen);
        if(sock < 0) {
            perror("Error accepting connection");
            exit(1);
        }

        if (fork() == 0)
        {
            close(server_sock);
            serve_request(sock);
            close(sock);
            exit(0);
        }
        
        /* At this point, you have a connected socket (named sock) that you can
         * use to send() and recv(). */

        /* ALWAYS check the return value of send() and recv(). This is example
         * code that you must replace. */

        /* TODO: collect the request, and keep collecting until you see the
         * request separator (a blank line). This is placeholder code. */
        //recv(sock,buffer,255,0);

        /* TODO: once you've received a request, use parseRequest to pull out
         * the file that was asked for. */

        /* TODO: construct a valid response to that request, and send THE 
         * ENTIRE THING to the client. This is placeholder code. */
        //send(sock, response,strlen(response), 0);

        /* Tell the OS to clean up the resources associated with that client
         * connection, now that we're done with it. */
        close(sock);
    }

    //close(server_sock);
}




void serve_request(int sock)
{
   
    
    
    memset(sockBuffer,0,4096);
    memset(filename,0,4096);
    
    while(1)
    {
        
        sockOffset += recv(sock,&sockBuffer[sockOffset],4096,0);
        
        if(strstr(sockBuffer,"\r\n\r\n"))
        {
            break;
        }
    }
    
    getFile = parseRequest(sockBuffer);
    
    
    //Bunch of If statments to handle every situation.
    hallway();
    

    send(sock,getString,strlen(getString),0);
    

    filename[0] = '.';
    
    strncpy(&filename[1],getFile,4095);
    
 
    status = stat(filename, &s);
    
    
    statusCond(sock);
    
    
    readFile = open(filename,0,0);
    
    while(1)
    {
        readBytes = read(readFile,sendFileBuffer,4096);
        
        if(readBytes == 0)
        {
            break;
        }
        
        send(sock,sendFileBuffer,readBytes,0);
    }
    
    
    close(readFile);
    close(sock);
    return;
}


void statusCond(int sock)
{

    if(status!=0)
    {
        
        send(sock,errorDisp, strlen(errorDisp),0);
        
        send(sock, indexFooter, strlen(indexFooter),0);
    }
    else if(status==0)
    {
        
        if( S_ISDIR(s.st_mode) )
        {
            
            char * charTemp;
            
            int sendNumb =  asprintf(&charTemp, indexHeader,filename, filename);
            
            DIR * currentDirectory;
            
            
            if( (currentDirectory = opendir(filename)) == NULL)
            {
                send(sock,status, strlen(status),0);
            }
            else
            {
                
                free(charTemp);
                
                char * insideBody;
                
                while((dp = readdir(currentDirectory)) != NULL)
                {
                    char * tempFile;
                    
                    if(strstr(dp->d_name, ".jpg") != NULL || strstr(dp->d_name, ".jpeg") != NULL || strstr(dp->d_name, ".png") != NULL || strstr(dp->d_name, ".gif") != NULL
                       || strstr(dp->d_name, ".pdf") != NULL || strstr(dp->d_name, ".html") != NULL || strstr(dp->d_name, ".ico")!= NULL)
                    {
                        asprintf(&tempFile,"%s%s", getFile, dp->d_name);
                    }
                    else
                    {
                        asprintf(&tempFile,"%s%s/", getFile, dp->d_name);
                    }
                    
                    sendNumb = asprintf(&insideBody,indexBody,tempFile,dp->d_name);
                    
                    send(sock, insideBody, sendNumb,0);
                    
                    if(insideBody!= NULL)
                    {
                        free(insideBody);
                    }
                    
                    free(tempFile);
                }
                
            }
            
            
            send(sock, indexFooter, strlen(indexFooter),0);
            
            close(readFile);
            close(sock);
            return;
            
        }
        
    }
}


void hallway()
{
    if(strstr(getFile, ".jpg") != NULL || strstr(getFile, ".jpeg") != NULL)
    {
        asprintf(&getString,getString,"image/jpeg",0);
    }
    
    else if(strstr(getFile, ".png") != NULL)
    {
        asprintf(&getString,
                 getString,
                 "image/png",0);
    }
    
    else if(strstr(getFile, ".gif") != NULL)
    {
        asprintf(&getString,
                 getString,
                 "image/gif",0);
    }
    
    else if(strstr(getFile, ".pdf") != NULL)
    {
        asprintf(&getString,
                 getString,
                 "application/pdf",0);
    }
    
    else if(strstr(getFile, ".html") != NULL)
    {
        asprintf(&getString,
                 getString,
                 "text/html",0);
    }
    
    else if(strstr(getFile, ".ico") != NULL)
    {
        asprintf(&getString,
                 getString,
                 "image/vnd.microsoft.icon",0);
    }
    
    else
    {
        asprintf(&getString,
                 getString,
                 "text/html",0);
    }
    

}
