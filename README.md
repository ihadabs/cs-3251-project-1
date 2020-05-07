# Hangman V1  

##### Table of Contents

1. [Goal](#goal)
2. [Description](#description)
3. [Usage](#usage)
4. [Client Oprations](#client-oprations)

## Goal

The goal of this project is to get familiar with sockets programming in C.

## Description

The project is about developing a networked application between a server (a bank) and a client (a bank customer). The client will communicate with the server to perform a set of operations and the server will handle all underlying transactions and communicate back to the client. The client will be able to ask the server for an account balance and withdrawing/transferring money.

## Usage

To use the project follow the following steps:

- Clone this repo
- Make sure to set the port number to an available one on both `client.c` & `server.c`
- Run `make all`
- Start the server by running `./changeServer`
- Start the client by running `./nameChanger` providing the arguments for
  your desired operation. e.g. `./nameChanger WITHDRAW myCD 10`

## Client Oprations

There are three operations that can be performed by the client.

### Checking Balance

For checking an account balance, you should run the client providing the following arguments.

    ./nameChanger BAL [accountName]
    ./nameChanger BAL myChecking

### Withdrawing Money

For withdrawing money from an account, you should run the client providing the following arguments (you are not allowed to withdraw more than 3 times a minute).

    ./nameChanger WITHDRAW [accountName] [amount]
    ./nameChanger WITHDRAW my401k 400

### Transfering Money

For transferring money from an account to another, you should run the client providing the following arguments.

    ./nameChanger TRANSFER [firstAccountName] [secondAccountName] [amount]
    ./nameChanger TRANSFER myChecking myCD 300

### Notes

- An account name can be myChecking, mySavings, myCD, my401k, or my529.
- An amount to be withdrawn or transferred must be an integer greater than 0.
- Only three withdrawals are allowed per account within a minute duration.
