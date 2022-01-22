CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lSDL_gfx

pixeloperation = PixelOperations/pixel_operations.c
cutimage = CutImage/cut_image.c
queue = Watershed/queue.c
watershed = Watershed/watershed.c
printnumbers = PrintNumbers/print_numbers.c
resize = Resize/resize.c

main = main.c

all: main

main: main.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(queue) $(watershed) $(pixeloperation) $(cutimage) $(printnumbers) $(resize) $(main) -o extract $(LDLIBS)

clean:
	${RM} *.o
	${RM} *.d
	${RM} extract
	${RM} TreatedImages/*.bmp
	${RM} Tiles/*.bmp
	${RM} -r extract.dSYM

# END
