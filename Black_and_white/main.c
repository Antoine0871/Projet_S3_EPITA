#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "BlackAndWhite/BlackandWhite.h"
#include "BlackAndWhite/Rotate/rotate.h"
#include <SDL/SDL_rotozoom.h>
#include <stdlib.h>
#include <math.h>
#include "BlackAndWhite/PixelOperation/pixel_operations.h"
#include "string.h"
#include "traitment.h"

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
	    printf("Invalid arguments, you must do ./main image_to_test\n");
	    return EXIT_FAILURE;
    }
	
    traitment(argv[1]);

    return 0;
}
