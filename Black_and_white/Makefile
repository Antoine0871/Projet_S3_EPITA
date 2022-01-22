# Simple SDL mini Makefile

CC=gcc

PKGCONFIG=$(shell which pkg-config)

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -fsanitize=address -Werror -std=c99 -O3 $(shell pkg-config --cflags gtk+-3.0)
LDLIBS= $(shell pkg-config --libs gtk+-3.0) `pkg-config --libs sdl` -lSDL_image -lSDL_gfx -lm

BandW = BlackAndWhite/BlackandWhite.c
pixeloperation = BlackAndWhite/PixelOperation/pixel_operations.c
display = BlackAndWhite/Display/display.c
traitment = traitment.c

main = main.c

all: main

main: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(BandW) $(pixeloperation) $(display) $(traitment) $(main) -o main $(LDLIBS)

 

clean:
	${RM} *.o
	${RM} *.d
	${RM} display
	${RM} grayscale
	${RM} main
	$(RM) *.bmp

# END
