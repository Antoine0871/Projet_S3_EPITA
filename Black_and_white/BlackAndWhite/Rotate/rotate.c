#include <math.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include "SDL/SDL_image.h"

#include "rotate.h"
#include "../Display/display.h"
#include "../PixelOperation/pixel_operations.h"

#include <gtk/gtk.h>
//#include <gtk/gtkx.h>

/*SDL_Surface**/ void Rotate(SDL_Surface* image_surface, int width, int height, int alpha)
{
    SDL_Surface *screen = NULL, *image = NULL, *rotation = NULL;
    SDL_Rect rect;

    image = image_surface;

    rotation = rotozoomSurface(image, alpha, 1.0, 1);

    SDL_Init(SDL_INIT_VIDEO);
    rotozoomSurfaceSize(width,height,alpha,1,&width,&height);

    screen = SDL_SetVideoMode(width,height, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Rotate", NULL);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    rect.x =0; 
    rect.y =0 ;

    SDL_BlitSurface(rotation , NULL, screen, &rect);
    SDL_FreeSurface(rotation);

    SDL_Flip(screen);

    SDL_SaveBMP(screen, "../Black_and_white/Images/Rotation.bmp");

    SDL_Quit();
}


int angle_from_path(char path[])
{
	SDL_Surface * image_surface;
        init_sdl();
     
	image_surface = load_image(path);

	int alpha = angle(image_surface,image_surface->w,image_surface->h);
	return alpha;
}


int angle(SDL_Surface* image_surface, int width, int height)
{
        int x = width/2 - 30;
        int y =1;

        Uint8 r, g, b;
        Uint32 pixel;

        while (x < width-1 && y < height-1)
        {
                pixel = get_pixel(image_surface, y, x);
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

                if (r == 0)
                        break;
		y++;
        }
	int x1 = x;
	int y1 = y;

	x = width/2 + 30;
	y = 1;
	while (x < width-1 && y < height-1)
        {
                pixel = get_pixel(image_surface, y, x);
                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

                if (r == 0)
                        break;
                y++;
        }
	int x2 = x;
	int y2 = y;

	//FIRST CASE left lower than right
	x = x1;
	y = y1;
	if (y1 < y2)
	{
		printf("Leaning to the left\n");
		while ((1 < x && 0 < y) && y < height - 1)
		{
			pixel = get_pixel(image_surface, y, x-1);
                	SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

			if (r == 255)
			{
				pixel = get_pixel(image_surface, y+1, x-1);
                	        SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
				if (r == 255)
				{
					break;
				}
				y++;
			}
			x--;
		}	
		x1 = x;
		y1 = y;

		x = x2;
		y = y2;
		while (1 < y && x < width - 1)
		{
                        pixel = get_pixel(image_surface, y, x+1);
                        SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

                        if (r == 255)
                        {
                                pixel = get_pixel(image_surface, y-1, x+1);
                                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                                if (r == 255)
				{
                                       	break;
				}
                                y--;
                        }
                        x++;
                }
		x2 = x;
		y2 = y;
	}

	//SECOND CASE left higher than right
	else
	{
		printf("Leaning to the right\n");

		while (1 < x && 1 < y)
                {
                        pixel = get_pixel(image_surface, y, x-1);
                        SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

                        if (r == 255)
                        {
                                pixel = get_pixel(image_surface, y-1, x-1);
                                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                                if (r == 255)
				{
                                       	break;
				}
                                y--;
                        }
                        x--;
                }
                x1 = x;
                y1 = y;

                x = x2;
                y = y2;
		while (y < height - 1 && x < width - 1)
                {
                        pixel = get_pixel(image_surface, y, x+1);
                        SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);

                        if (r == 255)
                        {
                                pixel = get_pixel(image_surface, y+1, x+1);
                                SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                                if (r == 255)
				{
                                       	break;
				}
                                y++;
                        }
                        x++;
                }
                x2 = x;
                y2 = y;
	}

	double alpha = atan2(y2 - y1, x2 - x1) * 180 / 3.141592;

	printf("x1 = %d y1 = %d et x2 = %d y2 = %d \n", x1, y1, x2, y2);
	printf("angle alpha %d \n", (int)alpha);
        return (int)alpha;
}


void SaveRotation(gchar *path, int alpha)
{

	SDL_Surface * image_surface;
        init_sdl();
        image_surface = load_image(path);

	Rotate(image_surface,image_surface->w,image_surface->h, -alpha);

	SDL_FreeSurface(image_surface);
}
