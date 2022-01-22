CC =gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -O2 `pkg-config --cflags sdl` -fsanitize=address -g
LDFLAGS=-lm `pkg-config --libs sdl SDL_image` -fsanitize=address 
LDLIBS=
EXEC=main

All: $(EXEC) 

main : main.o Neural_Network.o SaveLoad.o ToolBox.o 
	$(CC) -o main Neural_Network.o SaveLoad.o ToolBox.o  main.o $(LDFLAGS)

ToolBox.o : ToolBox/ToolBox.c
	$(CC) -o ToolBox.o -c ToolBox/ToolBox.c $(CFLAGS)

Neural_Network.o : Neural_Network.c 
	$(CC) -o Neural_Network.o -c Neural_Network.c $(CFLAGS)

SaveLoad.o : SaveLoad/SaveLoad.c
	$(CC) -o SaveLoad.o -c SaveLoad/SaveLoad.c $(CFLAGS)

main.o : main.c Neural_Network.h SaveLoad/SaveLoad.h ToolBox/ToolBox.h 
	$(CC) -o main.o -c main.c $(CFLAGS)

clean:
	${RM} *.o
	${RM} *.d
	${RM} .save_nn
	${RM} main
