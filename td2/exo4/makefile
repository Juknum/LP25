CC=gcc
EXEC=main

CFLAGS=-Wall -O
LDFLAGS=

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

DIR_OBJ=./objects/
DIR_BIN=./bin/

all: $(EXEC)

main: $(OJB_DIR)$(OBJ)
	$(CC) -o $(DIR_BIN)$@ $(DIR_OBJ)*.o $(LDFLAGS)

%.o: %.c
	$(CC) -o $(DIR_OBJ)$@ -c $< $(CFLAGS)


clean:
	rm -f $(DIR_OBJ)*.o

mrproper: clean
	rm -f $(EXEC)