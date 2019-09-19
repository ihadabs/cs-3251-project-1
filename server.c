/*///////////////////////////////////////////////////////////
*
* FILE:		server.c
* AUTHOR:	Hadi Albinsaad
* PROJECT:	CS 3251 Project 1 - Professor Jun Xu
* DESCRIPTION:	Network Server Code
* CREDIT:	Adapted from Professor Traynor
*
*/
///////////////////////////////////////////////////////////

/*Included libraries*/

#include <stdio.h>  /* for printf() and fprintf() */
#include <stdlib.h> /* supports all sorts of functionality */

#include <sys/types.h>
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */

#include <netinet/in.h>
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */

#include <unistd.h> /* for close() */
#include <string.h> /* support any string ops */

#define RCVBUFSIZE 512 /* The receive buffer size */
#define SNDBUFSIZE 512 /* The send buffer size */
#define BUFSIZE 40     /* Your name can be as many as 40 chars*/
#define PORT 9003

/* The main function */
int main(int argc, char *argv[])
{

    int server_socket;                 /* Server Socket */
    int client_socket;                 /* Client Socket */
    struct sockaddr_in server_address; /* Local address */
    struct sockaddr_in client_address; /* Client address */
    unsigned short server_port;        /* Server port */
    unsigned int client_length;        /* Length of address data struct */

    char name_buff[BUFSIZE]; /* Buff to store account name from client */
    int balance;             /* Place to record account balance result */

    char server_message[256] = "You have reached the server!";

    /* Create new TCP Socket for incoming requests*/
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    /* Construct local address structure*/
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    /* Bind to local address structure */
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) != 0)
    {
        printf("Socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    /* Listen for incoming connections */
    if (listen(server_socket, 5) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");

    /* Loop server forever*/
    while (1)
    {
        /* Accept incoming connection */
        // client_socket = accept(server_socket, (struct sockaddr *)&client_address, sizeof(client_address));
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0)
        {
            printf("Server acccept failed...\n");
            exit(0);
        }
        else
            printf("Server acccept the client...\n");

        /* Extract the account name from the packet, store in nameBuf */
        read(client_socket, name_buff, sizeof(name_buff));
        printf("Account name: %s\n", name_buff);

        /* Look up account balance, store in balance */
        /*	FILL IN	    */

        /* Return account balance to client */
        /*	FILL IN	    */

        send(client_socket, server_message, sizeof(server_message), 0);
    }
}
