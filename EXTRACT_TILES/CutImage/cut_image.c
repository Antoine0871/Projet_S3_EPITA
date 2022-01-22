#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h>
#include"../PixelOperations/pixel_operations.h"
#include"../Resize/resize.h"
#include<math.h>

void RemoveGrid(SDL_Surface* image, SDL_Surface* treatedImage);
void GetCorners(SDL_Surface* treatedImage, size_t *lx, size_t *rx, size_t *by, size_t *ty);
void SeparateTiles(SDL_Surface* image, size_t *lx, size_t* rx, size_t* by, size_t* ty);
void CleanTile(SDL_Surface* tile);
void CenterTiles(SDL_Surface* tile, char path[]);

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

	RemoveGrid(image, treatedImage);

	GetCorners(treatedImage, plx, prx, pby, pty);

	SeparateTiles(image, plx, prx, pby, pty); 
}

void GetCorners(SDL_Surface* treatedImage, size_t *lx, size_t *rx, size_t *by, size_t *ty)
{
        Uint32 pixel;
        Uint8 r, g, b;
	size_t foundPixel;
	size_t imageWidth = (size_t)treatedImage->w;
	size_t imageHeight = (size_t)treatedImage->h;
	size_t leftxHistogram[imageWidth];
	size_t rightxHistogram[imageWidth];
	size_t topyHistogram[imageHeight];
	size_t bottomyHistogram[imageHeight];

	for (size_t i = 0; i < imageWidth; i++)
	{
		leftxHistogram[i] = 0;
		rightxHistogram[i] = 0;
	}

	for (size_t i = 0; i < imageHeight; i++)
	{
		topyHistogram[i] = 0;
		bottomyHistogram[i] = 0;
	}

	for (size_t x = 0; x < imageWidth; x += imageWidth / 30)
        {
                foundPixel = 0;
                for (size_t y = 0; y < imageHeight && !foundPixel; y++)
                {
                        pixel = get_pixel(treatedImage, x, y);
                        SDL_GetRGB(pixel, treatedImage->format, &r, &g, &b);
                        if (r == 0)
                        {
                                foundPixel = 1;
                                topyHistogram[y] += 1;
                        }
                }
        }

        for (size_t i = 0; i < imageHeight; i++)
        {
                if (topyHistogram[0] < topyHistogram[i])
                {
                        topyHistogram[0] = topyHistogram[i];
			*ty = i;
                }
        }

	for (size_t x = 0; x < imageWidth; x += imageWidth / 30)
	{
		foundPixel = 0;
		for (size_t y = imageHeight - 1; y > 0 && !foundPixel; y--)
		{
			pixel = get_pixel(treatedImage, x, y);
                        SDL_GetRGB(pixel, treatedImage->format, &r, &g, &b);
                        if (r == 0)
                        {
                                foundPixel = 1;
                                bottomyHistogram[y] += 1;
                        }
		}
	}

        for (size_t i = 0; i < imageHeight; i++)
        {
                if (bottomyHistogram[0] < bottomyHistogram[i])
                {
                        bottomyHistogram[0] = bottomyHistogram[i];
			*by = i;
                }
        }

	for (size_t y = 0; y < imageHeight; y += imageHeight / 30)
        {
                foundPixel = 0;
                for (size_t x = 0; x < imageWidth && !foundPixel; x++)
                {
                        pixel = get_pixel(treatedImage, x, y);
                        SDL_GetRGB(pixel, treatedImage->format, &r, &g, &b);
                        if (r == 0)
                        {
                                foundPixel = 1;
                                leftxHistogram[x] += 1;
                        }
                }
        }

        for (size_t i = 0; i < imageWidth; i++)
        {
                if (leftxHistogram[0] < leftxHistogram[i])
                {
                        leftxHistogram[0] = leftxHistogram[i];
			*lx = i;
                }
        }

	for (size_t y = 0; y < imageHeight; y += imageHeight / 30)
        {
                foundPixel = 0;
                for (size_t x = imageWidth - 1; x > 0 && !foundPixel; x--)
                {
                        pixel = get_pixel(treatedImage, x, y);
                        SDL_GetRGB(pixel, treatedImage->format, &r, &g, &b);
                        if (r == 0)
                        {
                                foundPixel = 1;
                                rightxHistogram[x] += 1;
                        }
                }
        }

        for (size_t i = 0; i < imageWidth; i++)
        {
                if (rightxHistogram[0] < rightxHistogram[i])
                {
                        rightxHistogram[0] = rightxHistogram[i];
			*rx = i;
                }
        }
}

void RemoveGrid(SDL_Surface* image, SDL_Surface* treatedImage)
{
	Uint32 pixel;
        Uint32 gridPixel;
        Uint8 r, g, b;

	for (size_t x = 0; x < (size_t)image->w; x++)
	{
		for (size_t y = 0; y < (size_t)image->h; y++)
		{
			gridPixel = get_pixel(treatedImage, x, y);
                        SDL_GetRGB(gridPixel, treatedImage->format, &r, &g, &b);
			if (r == 0)
			{
				pixel = SDL_MapRGB(image->format, 255, 255, 255);
                                put_pixel(image, x, y, pixel);
			}
		}
	}
}

void SeparateTiles(SDL_Surface* image, size_t *lx, size_t* rx, size_t* by, size_t* ty)
{
	Uint32 pixel;
	Uint32 tilePixel;
	Uint8 r, g, b;
	
	size_t gridSideH = *rx - *lx;
	size_t gridSideV = *by - *ty;
	size_t tileSideH = (size_t) gridSideH / 9;
	size_t tileSideV = (size_t) gridSideV / 9;

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			SDL_Surface* tile = SDL_CreateRGBSurface(0, tileSideH, tileSideV, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
			for (size_t x = 0; x < tileSideH; x++)
			{
				for (size_t y = 0; y < tileSideV; y++)
				{
					pixel = get_pixel(image, x + *lx + tileSideH * i, y + *ty + tileSideV * j);
					SDL_GetRGB(pixel, image->format, &r, &g, &b);
					tilePixel = SDL_MapRGB(tile->format, r, g, b);
					put_pixel(tile, x, y, tilePixel);
				}
			}
			char path[50];
			sprintf(path, "../EXTRACT_TILES/Tiles/tile_%zu_%zu.bmp", i, j);
			if (SDL_SaveBMP(tile, path) != 0)
        		{
                		printf("Failed to save tile at path : %s\n", path);
	        	}
			SDL_FreeSurface(tile);
		}
	}
}

void CleanTile(SDL_Surface* tile)
{
	size_t width = (size_t)tile->w;
	size_t height = (size_t)tile->h;

	float blackPixels = 0;

	Uint32 tilePixel;
        Uint8 r, g, b;

	Uint32 whitePixel = SDL_MapRGB(tile->format, 255, 255, 255);

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			tilePixel = get_pixel(tile, x, y);
                        SDL_GetRGB(tilePixel, tile->format, &r, &g, &b);
			if (r == 0)
			{
				if (x == 0 || y == 0 || x == (size_t)tile->w - 1 || y == (size_t)tile->h - 1)
				{
                                	put_pixel(tile, x, y, whitePixel);
				}
				else
				{
					blackPixels += 1;
				}
			}
		}
	}

	if (blackPixels < (tile->w * 0.15) * (tile->w * 0.15))
	{
		for (size_t y = 0; y < height; y++)
        	{
                	for (size_t x = 0; x < width; x++)
                	{
                        	tilePixel = get_pixel(tile, x, y);
				SDL_GetRGB(tilePixel, tile->format, &r, &g, &b);
				r = 42;
				g = 69;
				b = 150;
                                tilePixel = SDL_MapRGB(tile->format, r, g, b);
                        	put_pixel(tile, x, y, tilePixel);
				SDL_GetRGB(tilePixel, tile->format, &r, &g, &b);
                	}
        	}	
	}
}

void CenterTile(SDL_Surface* tile, char path[])
{
	size_t width = (size_t)tile->w;
	size_t height = (size_t)tile->h;

	Uint32 tilePixel;
	Uint32 numberPixel;
        Uint8 r, g, b;

	size_t ml = width - 1;
	size_t mr = 0;
	size_t mu = height - 1;
	size_t md = 0;
	size_t blackPixels = 0;

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			tilePixel = get_pixel(tile, x, y);
                	SDL_GetRGB(tilePixel, tile->format, &r, &g, &b);
			if (r == 0)
			{
				blackPixels += 1;
				if (x < ml)
				{
					ml = x;
				}
				if (x > mr)
				{
					mr = x;
				}
				if (y < mu)
				{
					mu = y;
				}
				if (y > md)
				{
					md = y;
				}
			}
		}
	}

	if (blackPixels > 0)
	{
		//Uint32 centeredPixel;

		size_t numberW = mr - ml;
        	size_t numberH = md - mu;

        	SDL_Surface* numberTile = SDL_CreateRGBSurface(0, numberW + 2, numberH + 2, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
		SDL_FillRect(numberTile, NULL, SDL_MapRGB(numberTile->format, 255, 255, 255));

		for (size_t y = 0; y < numberH + 2; y++)
        	{
                	for (size_t x = 0; x < numberW + 2; x++)
                	{
                        	tilePixel = get_pixel(tile, x + ml, y + mu);
                        	SDL_GetRGB(tilePixel, tile->format, &r, &g, &b);
				if (r == 0)
				{
					put_pixel(numberTile, x, y, tilePixel);
				}
                	}
        	}

		SDL_Surface* resizedNumber = ResizeImage(numberTile, 10, 16);
		SDL_Surface* centeredTile = SDL_CreateRGBSurface(0, 28, 28, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
                SDL_FillRect(centeredTile, NULL, SDL_MapRGB(centeredTile->format, 255, 255, 255));

		for (size_t y = 0; y < (size_t)resizedNumber->h; y++)
		{
			for (size_t x = 0; x < (size_t)resizedNumber->w; x++)
			{
				numberPixel = get_pixel(resizedNumber, x, y);
				SDL_GetRGB(numberPixel, resizedNumber->format, &r, &g, &b);
				if (r == 0)
				{
					put_pixel(centeredTile, x + 8, y + 6, numberPixel);
				}
			}
		}

        	if (SDL_SaveBMP(centeredTile, path) != 0)
                {
                        printf("Failed to save tile at path : %s\n", path);
                }

		SDL_FreeSurface(centeredTile);
		SDL_FreeSurface(numberTile);
		SDL_FreeSurface(resizedNumber);
	}
}



