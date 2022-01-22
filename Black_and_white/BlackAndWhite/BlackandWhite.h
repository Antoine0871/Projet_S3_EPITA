#ifndef BLACKANDWHITE_H_
#define BLACKANDWHITE_H_

#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>


void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
void SDL_FreeSurface(SDL_Surface *surface);
SDL_Surface* First_LineBlur(SDL_Surface* image_surface, int width);
SDL_Surface* Array_Blur(SDL_Surface* image_surface, int width, int height);
float Local_Average2(int i, int j, SDL_Surface* imageBlur);
int Sauvola(int i, int j, SDL_Surface* imageBlur);
void Grayscale(int height, int width,SDL_Surface* image_surface);
void increase_Contrast(SDL_Surface* image_surface);
void BlackandWhite(int height,int width,SDL_Surface* image_surface,SDL_Surface* Grayscale_image);
SDL_Surface* Resize_image(SDL_Surface *image, int weight, int height);
void Make_image_black(SDL_Surface* image_surface);
SDL_Surface* IncreaseContrast_With_Coef(SDL_Surface *image);

#endif
