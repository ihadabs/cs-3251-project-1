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

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Constants */
#define RCVBUFSIZE 512
#define SNDBUFSIZE 512
#define REPLYLEN 32

int isAcountName(char acount_name[])
{
    char acounts_names[5][20] = {"myChecking",
                                 "mySavings",
                                 "myCD",
                                 "my401k",
                                 "my529"};
    int i;
    for (i = 0; i < 5; i++)
        if (strcmp(acounts_names[i], acount_name) == 0)
            return i;

    return -1;
}

/* The main function */
int main(int argc, char *argv[])
{

    unsigned short server_port = 9003; /* Server Port number */

    int client_socket;                 /* socket descriptor */
    struct sockaddr_in server_address; /* server address structure */

    // For storing arguments
    char *cmd;                 /* BAL, WITHDRAW, or TRANSFER */
    char *first_account_name;  /* myChecking, mySavings, myCD, my401k, or my529 */
    char *second_account_name; /* myChecking, mySavings, myCD, my401k, or my529 */
    int amount;

    // For comunicating with the server
    int cmd_id;                 /* BAL = 0, WITHDRAW = 1, TRANSFER = 2 */
    int first_account_id;       /* myChecking = 0, mySavings = 1, myCD = 2, my401k = 3, my529 = 4 */
    int second_account_id = -1; /* myChecking = 0, mySavings = 1, myCD = 2, my401k = 3, my529 = 4 */

    char send_buff[SNDBUFSIZE];    /* Send Buffer */
    char receive_buff[RCVBUFSIZE]; /* Receive Buffer */

    memset(&send_buff, 0, SNDBUFSIZE);
    memset(&receive_buff, 0, RCVBUFSIZE);

    /* Get the addditional parameters from the command line */
    if (argc < 3)
    {
        printf("Invaild number of arguments.\n");
        exit(0);
    }

    // Get the CMD
    cmd = argv[1];

    // Get the name for the first account
    first_account_name = argv[2];
    first_account_id = isAcountName(first_account_name);
    if (first_account_id < 0)
    {
        printf("Invaild account name. %d\n", isAcountName(first_account_name));
        exit(0);
    }

    if (strcmp(cmd, "BAL") == 0 && argc >= 3)
    {
        cmd_id = 0;
    }
    else if (strcmp(cmd, "WITHDRAW") == 0 && argc >= 4)
    {
        cmd_id = 1;
        amount = atoi(argv[3]);
    }
    else if (strcmp(cmd, "TRANSFER") == 0 && argc >= 5)
    {
        cmd_id = 2;
        second_account_name = argv[3];
        second_account_id = isAcountName(second_account_name);
        if (second_account_id < 0)
        {
            printf("Invaild CMD or invaild number of arguments.\n");
            exit(0);
        }
        else if (strcmp(first_account_name, second_account_name) == 0)
        {
            printf("You can not transfer money to the same account, please enter two different accounts names.\n");
            exit(0);
        }

        amount = atoi(argv[4]);
    }
    else
    {
        printf("Invaild CMD or invaild number of arguments.\n");
        exit(0);
    }

    if (strcmp(cmd, "WITHDRAW") == 0 || strcmp(cmd, "TRANSFER") == 0)
    {
        if (amount == 0)
        {
            printf("Invaild amount, please insert an integer that is greater than 0.\n\n");
            exit(0);
        }
    }

    printf("\n");

    if (cmd_id == 0)
    {
        printf("Retrieving balance for %s account... \n", first_account_name);
    }
    else if (cmd_id == 1)
    {
        printf("Withdrawing $%d from %s account... \n", amount, first_account_name);
    }
    else if (cmd_id == 2)
    {
        printf("Transfering $%d from %s account to %s account... \n", amount, first_account_name, second_account_name);
    }
    else
    {
        printf("Somthing went wrong!");
        exit(0);
    }

    // Storing the message to be sent to the server in send_buff
    snprintf(send_buff, sizeof(send_buff), "%d %d %d %d", cmd_id, first_account_id, second_account_id, amount);

    /* Create a new TCP socket */
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    /* Construct the server address structure */
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    /* Establish connecction to the server */
    int connection_status = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connection_status == -1)
    {
        printf("There was an errror making a connection to the remote socket! \n");
        exit(0);
    }

    /* Send the string to the server */
    send(client_socket, send_buff, sizeof(send_buff), 0);

    /* Receive and print response from the server */
    recv(client_socket, &receive_buff, sizeof(receive_buff), 0);
    printf("%s \n\n", receive_buff);

    return 0;
}
