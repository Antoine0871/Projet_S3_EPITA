#ifndef PRINT_NUMBERS_H_
#define PRINT_NUMBERS_H_

#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_rotozoom.h>
#include"../PixelOperations/pixel_operations.h"
#include<math.h>
#include<time.h>

void Print(SDL_Surface* image, char number, int color, size_t i, size_t j);
void PrintNumbers();

#endif
