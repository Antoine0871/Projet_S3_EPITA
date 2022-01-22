#ifndef ROTATE
#define ROTATE


#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>


#include "../Display/display.h"

void Rotate(SDL_Surface* image_surface, int width, int height, int alpha);

int angle(SDL_Surface* image_surface, int width, int height);

int angle_from_path(char path[]);

void SaveRotation(char path[], int alpha);

#endif
