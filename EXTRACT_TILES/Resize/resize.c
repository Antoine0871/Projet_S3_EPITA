#include<err.h>
#include<stdio.h>
#include<stdlib.h>
#include"../PixelOperations/pixel_operations.h"
#include"../Watershed/watershed.h"
#include"../CutImage/cut_image.h"
#include"../PrintNumbers/print_numbers.h"
#include"resize.h"
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_rotozoom.h>

SDL_Surface* ResizeImage(SDL_Surface *image, int weight, int height)
{
        double zoomX = 1;
        double zoomY = 1;

        if(image->w > weight)
        {
                zoomX = weight / (float)image->w;
                zoomY = zoomX;
        }

        if(image->h > height)
        {
                zoomY = height / (float)image->h;
                zoomX = zoomY;
        }

        SDL_Surface* zoomedImage = zoomSurface(image, zoomX, zoomY, 0);
	return zoomedImage;
}
