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

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <string.h>
#include <time.h>

#define RCVBUFSIZE 512
#define SNDBUFSIZE 512
#define BUFSIZE 40

int getNumberOfTransactionsInLastMinute(int *transactions_history)
{
    time_t now = time(NULL);
    int len = 3;
    int i, j, temp;

    for (i = 0; i < len; i++)
    {
        int transaction_time = transactions_history[i];
        if (now - transaction_time > 60)
        {
            transactions_history[i] = 0;
        }
    }

    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (transactions_history[i] > transactions_history[j])
            {
                temp = transactions_history[i];
                transactions_history[i] = transactions_history[j];
                transactions_history[j] = temp;
            }
        }
    }

    for (i = 0; i < len; i++)
    {
        int transaction_time = transactions_history[i];
        if (transaction_time != 0)
        {
            break;
        }
    }

    return len - i;
}

/* The main function */
int main(int argc, char *argv[])
{

    int server_socket;                 /* Server Socket */
    int client_socket;                 /* Client Socket */
    struct sockaddr_in server_address; /* Local address */
    unsigned short server_port = 9003; /* Server port */

    char server_message[SNDBUFSIZE]; /* Buff to store message that will be sent to client */
    char client_message[RCVBUFSIZE]; /* Buff to store message from client */

    // For comunicating with the client
    int cmd_id;                 /* BAL = 0, WITHDRAW = 1, TRANSFER = 2 */
    int first_account_id;       /* myChecking = 0, mySavings = 1, myCD = 2, my401k = 3, my529 = 4 */
    int second_account_id = -1; /* myChecking = 0, mySavings = 1, myCD = 2, my401k = 3, my529 = 4 */

    char *first_account_name;  /* myChecking, mySavings, myCD, my401k, or my529 */
    char *second_account_name; /* myChecking, mySavings, myCD, my401k, or my529 */

    int first_account_balance;  /* Place to record account balance result */
    int second_account_balance; /* Place to record account balance result */

    int amount;

    char cmds[3][10] = {"BAL",
                        "WITHDRAW",
                        "TRANSFER"};

    char accounts_names[5][20] = {"myChecking",
                                  "mySavings",
                                  "myCD",
                                  "my401k",
                                  "my529"};

    int accounts_balances[5] = {1000,
                                500,
                                2000,
                                401000,
                                529};

    int number_of_transactions;
    int transactions[5][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    /* Create new TCP Socket for incoming requests*/
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    /* Construct local address structure*/
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
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
        printf("Server listening..\n\n");

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

        printf("------------------------------------\n");

        read(client_socket, client_message, sizeof(client_message));

        int i;
        int args[4];
        char delimiter[] = " ";
        char *ptr = strtok(client_message, delimiter);

        for (i = 0; i < 4; i++)
        {
            args[i] = atoi(ptr);
            ptr = strtok(NULL, delimiter);
        }

        cmd_id = args[0];
        first_account_id = args[1];
        second_account_id = args[2];
        amount = args[3];
        first_account_name = accounts_names[first_account_id];
        first_account_balance = accounts_balances[first_account_id];

        // Check balance
        if (cmd_id == 0)
        {
            printf("Client wants to retrieve balance for %s account... \n", first_account_name);
            snprintf(server_message, sizeof(server_message), "The balance for %s account is $%d.", first_account_name, first_account_balance);
        }

        // Withdraw money
        else if (cmd_id == 1)
        {

            printf("Client wants withdraw $%d from %s account... \n", amount, first_account_name);

            int number_of_transactions = getNumberOfTransactionsInLastMinute(transactions[first_account_id]);
            if (number_of_transactions >= 3)
            {
                time_t now = time(NULL);
                int waiting_time = 61 - (now - transactions[first_account_id][0]);
                snprintf(server_message, sizeof(server_message), "Withdraw failed! Too many withdrawals in a minute!\nPlease, wait %d seconds and then try again.", waiting_time);
            }
            else
            {

                if (amount > first_account_balance)
                {
                    snprintf(server_message, sizeof(server_message), "Withdraw failed! The available balance is $%d.", first_account_balance);
                }
                else
                {
                    // Add transaction
                    time_t now = time(NULL);
                    int i;
                    for (i = 0; i < 3; i++)
                    {
                        if (transactions[first_account_id][i] == 0)
                        {
                            transactions[first_account_id][i] = now;
                            break;
                        }
                    }

                    // Change account balance
                    accounts_balances[first_account_id] = first_account_balance - amount;
                    first_account_balance = accounts_balances[first_account_id];

                    snprintf(server_message, sizeof(server_message), "Withdrawing $%d succeeded! The new balance is $%d.", amount, first_account_balance);
                }
            }
        }

        // Transfer money
        else if (cmd_id == 2)
        {
            printf("Client wants to transfer $%d from %s account to %s account... \n", amount, first_account_name, second_account_name);
            second_account_name = accounts_names[second_account_id];
            second_account_balance = accounts_balances[second_account_id];

            if (amount > first_account_balance)
            {
                snprintf(server_message, sizeof(server_message), "Transfering $%d to %s account failed! The available balance for %s account is $%d.", amount, second_account_name, first_account_name, first_account_balance);
            }
            else
            {
                // Change accounts balances
                accounts_balances[first_account_id] = first_account_balance - amount;
                accounts_balances[second_account_id] = second_account_balance + amount;

                // Reassign variables
                first_account_balance = accounts_balances[first_account_id];
                second_account_balance = accounts_balances[second_account_id];

                snprintf(server_message, sizeof(server_message), "Transfering $%d to %s account succeeded!\nThe new balance for %s account is $%d and for %s account is $%d.", amount, second_account_name, second_account_name, second_account_balance, first_account_name, first_account_balance);
            }
        }
        else
        {
            printf("Bad formated request!");
            exit(0);
        }

        /* Return response to client */
        printf("I will tell it \"%s\".\n\n", server_message);
        send(client_socket, server_message, sizeof(server_message), 0);
    }
}
