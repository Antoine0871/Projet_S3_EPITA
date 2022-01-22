CC=gcc


PKGCONFIG=$(shell which pkg-config)

CPPFLAGS= `pkg-config --cflags sdl` -MMD

CFLAGS=-Wall -Wextra  -std=c99 -O3 -lm $(shell pkg-config --cflags gtk+-3.0) -export-dynamic

LDLIBS= $(shell pkg-config --libs gtk+-3.0) `pkg-config --libs sdl` -lSDL_image -lSDL_gfx -lm

LDFLAGS= -rdynamic



BandW = Black_and_white/BlackAndWhite/BlackandWhite.c
pixeloperation = Black_and_white/BlackAndWhite/PixelOperation/pixel_operations.c
display = Black_and_white/BlackAndWhite/Display/display.c
traitment = Black_and_white/traitment.c
interface = INTERFACE/interface.c
rotate = Black_and_white/BlackAndWhite/Rotate/rotate.c
sudoku = Black_and_white/Solver/Sudoku.c

neural_net = NEURAL_NETWORK/Neural_Network.c
toolbox = NEURAL_NETWORK/ToolBox/ToolBox.c
saveload = NEURAL_NETWORK/SaveLoad/SaveLoad.c
extract = EXTRACT_TILES/extract.c

cutimage =  EXTRACT_TILES/CutImage/cut_image.c
queue = EXTRACT_TILES/Watershed/queue.c
watershed = EXTRACT_TILES/Watershed/watershed.c
printnumbers = EXTRACT_TILES/PrintNumbers/print_numbers.c
resize = EXTRACT_TILES/Resize/resize.c



all: interface

interface: INTERFACE/interface.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(resize) $(queue) $(watershed) $(cutimage) $(printnumbers) $(extract) $(saveload) $(toolbox) $(neural_net) $(sudoku) $(BandW) $(pixeloperation) $(display) $(traitment) $(rotate) $(interface) -o INTERFACE/interface $(LDLIBS)


clean:
	${RM} EXTRACT_TILES/Tiles/*.bmp
	${RM} EXTRACT_TILES/TreatedImages/*.bmp
	${RM} Black_and_white/Images/*.bmp
	${RM} INTERFACE/interface
	${RM} INTERFACE/*.d
	${RM} INTERFACE/*.glade~
	$(RM) *.bmp
	${RM} INTERFACE/*.result.txt

# END
