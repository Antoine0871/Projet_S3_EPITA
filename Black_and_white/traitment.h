#ifndef TRAITEMENT_H_
#define TRAITEMENT_H_

#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>

#include <gtk/gtk.h>
//#include <gtk/gtkx.h>

void traitment(gchar *path);
void ResizeRotation();
void dilatation_image(SDL_Surface* image_surface);

#endif
