# CS 3251 Project 1

##### Table of Contents  
[Goal](#goal)  
[Description](#description) 
[Usage](#usage) 
[Client Oprations](#clientoprations) 

## Goal

The goal of this project is to get familiar with sockets programming in C.

## Description

The project is about developing a networked application between a server (a bank) and a client (a bank customer). The client will communicate with the server to perform a set of operations and the server will handle all underlying transactions and communicate back to the client. The client will be able to ask the server for an account balance and withdrawing/transferring money.

## Usage

To use the project follow the following steps:

- Clone this repo
- Compile server.c and client.c files
- Start the server by running its executable file
- Run the client providing the arguments for your desired operation

## Client Oprations

Three operations can be performed by the client.

### Checking Balance

For checking an account balance, you should run the client providing the following arguments.

    ./client BAL [accountName]
    ./client BAL myChecking

### Withdrawing Money

For withdrawing money from an account, you should run the client providing the following arguments (you are not allowed to withdraw more than 3 times a minute).

    ./client WITHDRAW [accountName] [amount]
    ./client WITHDRAW my401k 400

### Transfering Money

For transferring money from an account to another, you should run the client providing the following arguments.

    ./client TRANSFER [firstAccountName] [secondAccountName] [amount]
    ./client TRANSFER myChecking myCD 300

- An account name can be myChecking, mySavings, myCD, my401k, or my529.
- An amount to be withdrawn or transferred must be an integer greater than 0.

