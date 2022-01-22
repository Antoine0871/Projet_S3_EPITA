#ifndef RESIZE_H_
#define RESIZE_H_

#include<err.h>
#include<stdio.h>
#include<stdlib.h>
#include"../PixelOperations/pixel_operations.h"
#include"../Watershed/watershed.h"
#include"../CutImage/cut_image.h"
#include"../PrintNumbers/print_numbers.h"
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_rotozoom.h>

SDL_Surface* ResizeImage(SDL_Surface *image, int weight, int height);

#endif
