# CS 3251 Project 1

## Goal

The goal of this project is to get familiar with sockets programming in C.

## Description

The project is about developing a networked application between a server (a bank) and a client (a bank customer). The client will cmunicate with the server to perform a set of oprations and the server will handle all unerlying transactions and cmunicate back to the client. The client will be able to ask the server for an account balance and withdrawing/transfering money.

## Test

To test the project follow the following steps:

- Clone this repo
- Compile server.c and client.c files
- Start the server by running it's executable file
- Run the client providing the arguments for your desierd opration

## Client Oprations

There are 3 oprations that can be preformd by the client.

### Checking Balance

For checking an account balance, you sould run the client provideing the following arguments.

    ./client BAL [accountName]
    ./client BAL myChecking

### Withdrawing Money

For withdrawing money from an account, you sould run the client provideing the following arguments (you are not allowed to withdraw more that 3 times a minute).

    ./client WITHDRAW [accountName] [amount]
    ./client WITHDRAW my401k 400

### Transfering Money

For transfering money from an account to another, you sould run the client provideing the following arguments.

    ./client TRANSFER [firstAccountName] [secondAccountName] [amount]
    ./client TRANSFER myChecking myCD 300

- An account name can be myChecking, mySavings, myCD, my401k, or my529.
- An amount to be withdrawd or transferd must be an intergar grater than 0.

## Requirements

- C
