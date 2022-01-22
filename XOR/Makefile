CC =gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c99 -O2 
LDFLAGS=-lm
LDLIBS=
EXEC=Xor

All: $(EXEC) 

Xor : XOR_Neural_Network.o main.o ToolBox.o SaveLoad.o
	$(CC) -o Xor XOR_Neural_Network.o ToolBox.o SaveLoad.o main.o $(LDFLAGS)

XOR_Neural_Network.o : XOR_Neural_Network.c
	$(CC) -o XOR_Neural_Network.o -c XOR_Neural_Network.c $(CFLAGS)

ToolBox.o : ToolBox/ToolBox.c
	$(CC) -o ToolBox.o -c ToolBox/ToolBox.c $(CFLAGS)

SaveLoad.o : SaveLoad/SaveLoad.c
	$(CC) -o SaveLoad.o -c SaveLoad/SaveLoad.c $(CFLAGS)

main.o : main.c XOR_Neural_Network.h ToolBox/ToolBox.h
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	${RM} *.o
	${RM} *.d
	${RM} .save_xor
	${RM} Xor
