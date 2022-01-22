# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS =


all: Solver

OBJ = *.d

Solver: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) Sudoku.c main.c -o Solver 

clean:
	${RM} ${OBJ} *.result.txt Solver

# END
