#ifndef WATERSHED_H_
#define WATERSHED_H_

#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_rotozoom.h>
#include"../PixelOperations/pixel_operations.h"

void WatershedSegmentation(SDL_Surface* image, int type);
size_t Segment(SDL_Surface* image, SDL_Surface* segtab);
size_t Propagate(SDL_Surface* image, size_t chunkN, size_t x, size_t y);
void Colorize(SDL_Surface* image, SDL_Surface* segtab);
void CutUselessChunks(SDL_Surface* image, SDL_Surface* segtab, size_t maxChunkN);

#endif
