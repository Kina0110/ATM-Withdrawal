# Makefile
# Yakina Azza
# 11/18/2024
# Purpose: Assignment 6 for CS3377
# Makefile for compiling the atm_withdraw program
	
CC = gcc
CFLAGS = -std=c99 -lpthread

TARGET1 = atm_unsync_withdraw
TARGET2 = atm_withdraw

OBJ1 = atm_unsync_withdraw.o
OBJ2 = atm_withdraw.o

all: $(TARGET1) $(TARGET2)

$(OBJ1): atm_unsync_withdraw.c
	$(CC) $(CFLAGS) -c atm_unsync_withdraw.c -o $(OBJ1)

$(TARGET1): $(OBJ1)
	$(CC) $(CFLAGS) -o $(TARGET1) $(OBJ1)

$(OBJ2): atm_withdraw.c
	$(CC) $(CFLAGS) -c atm_withdraw.c -o $(OBJ2)

$(TARGET2): $(OBJ2)
	$(CC) $(CFLAGS) -o $(TARGET2) $(OBJ2)

clean:
	rm -f $(TARGET1) $(TARGET2) $(OBJ1) $(OBJ2)


