CC=gcc
EXEC=main

CFLAGS=-Wall -O
LDFLAGS=

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

DIR_OBJ=./obj/
DIR_BIN=./

all: $(EXEC)

main: $(DIR_OBJ)$(OBJ)
	$(CC) -o $(DIR_BIN)$@ $(DIR_OBJ)*.o $(LDFLAGS)

%.o: %.c
	$(CC) -o $(DIR_OBJ)$@ -c $< $(CFLAGS)


clean:
	rm -f $(DIR_OBJ)*.o

mrproper: clean
	rm -f $(EXEC)