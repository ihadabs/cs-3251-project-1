/*///////////////////////////////////////////////////////////
*
* FILE:		client.c
* AUTHOR:	Hadi Albinsaad
* PROJECT:	CS 3251 Project 1 - Professor Jun Xu 
* DESCRIPTION:	Network Client Code
* CREDIT:	Adapted from Professor Traynor
*
*/
///////////////////////////////////////////////////////////

/* Included libraries */

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Constants */
#define RCVBUFSIZE 512 /* The receive buffer size */
#define SNDBUFSIZE 512 /* The send buffer size */
#define REPLYLEN 32

#define PORT 9003

/* The main function */
int main(int argc, char *argv[])
{

    int client_socket;                 /* socket descriptor */
    struct sockaddr_in server_address; /* server address structure */

    char *account_name;         /* Account Name  */
    char *server_ip;            /* Server IP address  */
    unsigned short server_port; /* Server Port number */

    char send_buff[SNDBUFSIZE];    /* Send Buffer */
    char receive_buff[RCVBUFSIZE]; /* Receive Buffer */

    int balance; /* Account balance */

    /* Get the Account Name from the command line */
    if (argc != 4)
    {
        printf("Incorrect number of arguments. The correct format is:\n\taccountName serverIP serverPort");
        exit(1);
    }
    account_name = argv[1];
    memset(&send_buff, 0, SNDBUFSIZE);
    memset(&receive_buff, 0, RCVBUFSIZE);

    /* Get the addditional parameters from the command line */
    /*	    FILL IN	*/

    /* Create a new TCP socket*/
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    /* Construct the server address structure */
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    /* Establish connecction to the server */
    int connection_status = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connection_status == -1)
    {
        printf("There was an errror making a connection to the remote socket! \n");
        exit(0);
    }

    /* Send the string to the server */
    /*	    FILL IN	 */

    /* Receive and print response from the server */
    recv(client_socket, &receive_buff, sizeof(receive_buff), 0);
    printf("The server says: %s \n\n", receive_buff);

    printf("%s\n", account_name);
    printf("Balance is: %i\n", balance);

    return 0;
}
