#ifndef CUT_IMAGE_H_
#define CUT_IMAGE_H_

#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h>
#include"../PixelOperations/pixel_operations.h"
#include"../Resize/resize.h"

void CutImage(SDL_Surface* treatedImage, SDL_Surface* image);
void RemoveGrid(SDL_Surface* image, SDL_Surface* treatedImage);
void GetCorners(SDL_Surface* treatedImage, size_t *lx, size_t *rx, size_t *by, size_t *ty);
void SeparateTiles(SDL_Surface* image, size_t *lx, size_t* rx, size_t* by, size_t* ty);
void CleanTile(SDL_Surface* tile);
void CenterTile(SDL_Surface* tile, char path[]);

#endif
