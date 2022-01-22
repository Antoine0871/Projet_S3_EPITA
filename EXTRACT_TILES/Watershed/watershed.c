#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_rotozoom.h>
#include"../PixelOperations/pixel_operations.h"
#include"queue.h"
#include<math.h>

size_t Segment(SDL_Surface* image, SDL_Surface* segtab);
size_t Propagate(SDL_Surface* image, SDL_Surface* setgab, size_t chunkN, size_t x, size_t y);
void Colorize(SDL_Surface* image, SDL_Surface* segtab);
void CutUselessChunks(SDL_Surface* image, SDL_Surface* segtab, size_t maxChunkN);

void WatershedSegmentation(SDL_Surface* image, int type)
{
	SDL_Surface* segtab = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	size_t maxChunkN;

	maxChunkN = Segment(image, segtab);

	if (type == 0) //image is the grid
	{
		Colorize(image, segtab);

        	if (SDL_SaveBMP(image, "../EXTRACT_TILES/TreatedImages/image_colorized.bmp") != 0)
        	{
                	printf("Failed to save grid only image at path : %s\n", "../EXTRACT_TILES/TreatedImages/image_colorized.bmp");
        	}
	}
	
	CutUselessChunks(image, segtab, maxChunkN);

	SDL_FreeSurface(segtab);
}

size_t Segment(SDL_Surface* image, SDL_Surface* segtab)
{
	size_t maxChunkN = 1; 
	size_t maxChunkSize = 0;
	size_t chunkN = 1;
	for (size_t x = 0; x < (size_t)image->w; x++)
	{
		for (size_t y = 0; y < (size_t)image->h; y++)
		{
			Uint32 pixel;
			pixel = get_pixel(image, x, y);
			Uint8 r, g, b;
                    	SDL_GetRGB(pixel, image->format, &r, &g, &b);
			if (r == 0)
			{
				Uint32 segPixel;
				segPixel = get_pixel(segtab, x, y);
				if (segPixel == 0)
				{
					size_t chunkSize = Propagate(image, segtab, chunkN, x, y);
					if (chunkSize > maxChunkSize)
					{
						maxChunkSize = chunkSize;
						maxChunkN = chunkN;
					}
					chunkN += 1;
				}
			}
		}
	}
	return maxChunkN;
}

size_t Propagate(SDL_Surface* image, SDL_Surface* segtab, size_t chunkN, size_t x, size_t y)
{
	size_t chunkSize = 0;

	Uint32 pixel;
        Uint8 r, g, b;
        Uint32 segPixel;

	struct Queue* queueX = newQueue(image->w * image->h);
	enqueue(queueX, x);
	size_t _x;

	struct Queue* queueY = newQueue(image->w * image->h);
	enqueue(queueY, y);
	size_t _y;

	while (!isempty(queueX))
	{
		_x = front(queueX);
		dequeue(queueX);
		_y = front(queueY);
		dequeue(queueY);

		pixel = get_pixel(image, _x, _y);
		SDL_GetRGB(pixel, image->format, &r, &g, &b);
		segPixel = get_pixel(segtab, _x, _y);

		if (r == 0 && segPixel == 0)
		{
			chunkSize += 1;

			put_pixel(segtab, _x, _y, chunkN);
			
			if (_x < (size_t)image->w-1)
                	{
				enqueue(queueX, _x + 1);
				enqueue(queueY, _y);
                	}
                	if (_x > 0)
                	{
				enqueue(queueX, _x - 1);
				enqueue(queueY, _y);
                	}
                	if (_y < (size_t)image->h-1)
                	{
				enqueue(queueX, _x);
				enqueue(queueY, _y + 1);
                	}
                	if (_y > 0)
                	{
				enqueue(queueX, _x);
				enqueue(queueY, _y - 1);
                	}
		}
	}

	freeQueue(queueX);
	freeQueue(queueY);
	free(queueX);
	free(queueY);

	return chunkSize;

	/*
	size_t chunkSize = 1;
	Uint32 pixel;
	pixel = get_pixel(image, x, y);
        Uint8 r, g, b;
	SDL_GetRGB(pixel, image->format, &r, &g, &b);
	Uint32 segPixel;
	segPixel = get_pixel(segtab, x, y);
	if (r == 0 && segPixel == 0)
	{
		put_pixel(segtab, x, y, chunkN);
		if (x < (size_t)image->w-1)
		{
			chunkSize += Propagate(image, segtab, chunkN, x + 1, y);
		}
		if (x > 0)
		{
			chunkSize += Propagate(image, segtab, chunkN, x - 1, y);
		}
		if (y < (size_t)image->h-1)
		{
			chunkSize += Propagate(image, segtab, chunkN, x, y + 1);
		}
		if (y > 0)
		{
			chunkSize += Propagate(image, segtab, chunkN, x, y - 1);
		}
	}
	return chunkSize;
	*/
}

void Colorize(SDL_Surface* image, SDL_Surface* segtab)
{
	for (size_t x = 0; x < (size_t)image->w; x++)
	{
		for (size_t y = 0; y < (size_t)image->h; y++)
		{
			Uint32 pixel;
			pixel = get_pixel(segtab, x, y);
			Uint8 r, g, b;
        		SDL_GetRGB(pixel, image->format, &r, &g, &b);
			if (pixel != 0)
			{
				r = 10 * pixel % 256;
				g = 75 * pixel % 256;
				b = 200 * pixel % 256;
				pixel = SDL_MapRGB(image->format, r, g, b);
				put_pixel(image, x, y, pixel);
			}
		}
	}
}

void CutUselessChunks(SDL_Surface* image, SDL_Surface* segtab, size_t maxChunkN)
{
	for (size_t x = 0; x < (size_t)image->w; x++)
	{
		for (size_t y = 0; y < (size_t)image->h; y++)
                {
			Uint32 segPixel;
                        segPixel = get_pixel(segtab, x, y);
			Uint32 pixel;
                        pixel = get_pixel(image, x, y);
			if (segPixel == maxChunkN)
			{
				pixel = SDL_MapRGB(image->format, 0, 0, 0);
                                put_pixel(image, x, y, pixel);
			}
			else
			{
				pixel = SDL_MapRGB(image->format, 255, 255, 255);
                                put_pixel(image, x, y, pixel);
			}
		}
	}
}
