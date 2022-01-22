#include<stdio.h>
#include<SDL2/SDL.h>
#include"pixel_operations.h"
#include<math.h>

//void GetTopCorners(SDL_Surface* image, size_t* lx, size_t* rx, size_t* cy);
//void GetBottomCorners(SDL_Surface* image, size_t* lx, size_t* rx, size_t* cy);

void CutImage(SDL_Surface* treatedImage, SDL_Surface* image)
{
        size_t lx = 0;
        size_t *plx = &lx;
        size_t rx = 0;
        size_t *prx = &rx;
        size_t ty = 0;
        size_t *pty = &ty;
        size_t by = 0;
        size_t *pby = &by;

        GetCorners(treatedImage, plx, prx, pby, pty);
        printf("lx = %zu, rx = %zu, by = %zu, ty = %zu\n", *plx, *prx, *pby, *pty);

        //printf("plx = %zu\n", plx);
        //printf("*plx = %zu\n", *plx);
        //printf("&plx = %zu\n", &plx);
        //SeparateTiles(image, plx, prx, pby, pty);

        //GetTopCorners(image, ptlx, ptrx, pty);
        //GetBottomCorners(image, pblx, pbrx, pby);

        //printf("tlx = %zu, trx = %zu, ty = %zu\n", *ptlx, *ptrx, *pty);
        //printf("blx = %zu, brx = %zu, by = %zu\n", *pblx, *pbrx, *pby);
}

/*size_t GetTopLeftCorners(SDM_Surface* image, size_t* cx, size_t* cy)
{
        Uint32 pixel;
        Uint8 r, g, b;
        unsigned int notFoundPixel = 0;
        for (size_t x = 0; x < (size_t)image->w && notFoundPixel; x++)
        {
                for (size_t y = 0; y < (size_t)image->h && notFoundPixel; y++)
                {
                        pixel = get_pixel(image, x, y);
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
                        if (r == 0)
                        {
                                notFoundPixel = 1;
                                *cx = x;
                                *cy = y;
                        }
                }
        }
        unsigned int canTravel = 1;
        while (canTravel)
        {
                canTravel = 0;
                if (*cx > 0)
                {
                        if (*cy > 0)
                        {
                                pixel = get_pixel(image, *(cx) - 1, *(cy) - 1);
                                SDL_GetRGB(pixel, image->format, &r, &g, &b);
                                if (r == 0)
                                {
                                        canTravel = 1;
                                        *cx -= 1;
                                        *cy -= 1;
                                }       
                        }
                        else
                        {
                                pixel = get_pixel(image, *cx, *(cy) - 1);
                                SDL_GetRGB(pixel, image->format, &r, &g, &b);
                                if (r == 0)
                                {       
                                        canTravel = 1;
                                        *cy -= 1;
                                }
                        }
                }
        }
}*/

/*void GetTopCorners(SDL_Surface* image, size_t *lx, size_t *rx, size_t *cy)
{
        size_t heightHistogram[image->h];
        unsigned int notFoundPixel;
        Uint32 pixel;
        Uint8 r, g, b;
        for (size_t x = 0; x < (size_t)image->w; x++)
        {
                notFoundPixel = 0;
                for (size_t y = 0; y < (size_t)image->h && notFoundPixel; y++)
                {
                        pixel = get_pixel(image, x, y);
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
                        if (r == 0)
                        {
                                notFoundPixel = 1;
                                heightHistogram[y] += 1;
                        }
                }
        }

        for (size_t i = 0; i < (size_t)image->h; i++)
        {
                if (heightHistogram[0] < heightHistogram[i])
                {
                        heightHistogram[0] = heightHistogram[i];
                        printf("highest y = %zu\n", heightHistogram[0]);
                }
        }

        printf("ty should be %zu\n", heightHistogram[0]);
        *cy = heightHistogram[0];

        notFoundPixel = 0;
        for (size_t x = 0; x < (size_t)image->w && notFoundPixel; x++)
        {
                pixel = get_pixel(image, x, heightHistogram[0]);
                SDL_GetRGB(pixel, image->format, &r, &g, &b);
                if (r == 0)
                {
                        notFoundPixel = 1;
                        printf("tlx should be %zu\n", x);
                        *lx = x;
                }
        }

        notFoundPixel = 0;
        for (size_t x = (size_t)image->w - 1; x > 0 && notFoundPixel; x--)
        {
                pixel = get_pixel(image, x, heightHistogram[0]);
                SDL_GetRGB(pixel, image->format, &r, &g, &b);
                if (r == 0)
                {
                        notFoundPixel = 1;
                        printf("trx should be %zu\n", x);
                        *rx = x;
                }
        }
}

void GetBottomCorners(SDL_Surface* image, size_t *lx, size_t *rx, size_t *cy)
{
        size_t heightHistogram[image->h];
        unsigned int notFoundPixel;
        Uint32 pixel;
        Uint8 r, g, b;
        for (size_t x = 0; x < (size_t)image->w; x++)
        {
                notFoundPixel = 0;
                for (size_t y = (size_t)image->h - 1; y > 0 && notFoundPixel; y--)
                {
                        pixel = get_pixel(image, x, y);
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
                        if (r == 0)
                        {
                                notFoundPixel = 1;
                                heightHistogram[y] += 1;
                        }
                }
        }

        heightHistogram[0] = (size_t)image->h;
        for (size_t i = 0; i < (size_t)image->h; i++)
        {
                if (heightHistogram[i] != 0 && heightHistogram[0] > heightHistogram[i])
                {
                        heightHistogram[0] = heightHistogram[i];
                        printf("lowest y = %zu\n", heightHistogram[0]);
                }
        }

        printf("by should be %zu\n", heightHistogram[0]);
        *cy = heightHistogram[0];

        notFoundPixel = 0;
        for (size_t x = 0; x < (size_t)image->w && notFoundPixel; x++)
        {
                pixel = get_pixel(image, x, heightHistogram[0]);
                SDL_GetRGB(pixel, image->format, &r, &g, &b);
                if (r == 0)
                {
                        notFoundPixel = 1;
                        printf("blx should be %zu\n", x);
                        *lx = x;
                }
        }

        notFoundPixel = 0;
        for (size_t x = (size_t)image->w - 1; x > 0 && notFoundPixel; x--)
        {
                pixel = get_pixel(image, x, heightHistogram[0]);
                SDL_GetRGB(pixel, image->format, &r, &g, &b);
                if (r == 0)
                {
                        notFoundPixel = 1;
                        printf("brx should be %zu\n", x);
                        *rx = x;
                }
        }
}*/
