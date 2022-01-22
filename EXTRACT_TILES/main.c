#include<err.h>
#include<stdio.h>
#include<stdlib.h>
#include"PixelOperations/pixel_operations.h"
#include"Watershed/watershed.h"
#include"CutImage/cut_image.h"
#include"PrintNumbers/print_numbers.h"
#include"Resize/resize.h"
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_rotozoom.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("main: function should be called with exactly one argument\n");
		return 1;
	}

	char* path = argv[1];
	printf("started running...\n");
    	SDL_Init(SDL_INIT_VIDEO);
    	SDL_Surface* image = IMG_Load(path);
	
	if (image == 0)
	{
		printf("main: failed to load image at %s : %s\n", path, SDL_GetError());
        	return 1;
	}
	
	printf("started WatershedSegmentation...\n");
	WatershedSegmentation(image, 0);

	if (SDL_SaveBMP(image, "TreatedImages/image_grid_only.bmp") != 0)
        {
		printf("Failed to save grid only image at path : %s\n", "TreatedImages/image_grid_only.bmp");
        }

	printf("started CutImage...\n");
	SDL_Surface* treatedImage = IMG_Load("TreatedImages/image_grid_only.bmp");
	SDL_FreeSurface(image);
	image = IMG_Load(path);
	CutImage(treatedImage, image);

	SDL_FreeSurface(treatedImage);
	SDL_FreeSurface(image);

	printf("started cleaning tiles...\n");

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			char tilePath[50];
			sprintf(tilePath, "Tiles/tile_%zu_%zu.bmp", i, j);
			SDL_Surface* tile = IMG_Load(tilePath);
			WatershedSegmentation(tile, 1);
			if (SDL_SaveBMP(tile, tilePath) != 0)
        		{
                		printf("Failed to save cleaned tile at path : %s\n", tilePath);
        		}

			SDL_FreeSurface(tile);
		}
	}

	for (size_t i = 0; i < 9; i++)
        {
                for (size_t j = 0; j < 9; j++)
                {
                        char tilePath[50];
                        sprintf(tilePath, "Tiles/tile_%zu_%zu.bmp", i, j);
                        SDL_Surface* tile = IMG_Load(tilePath);
                        CleanTile(tile);
                        if (SDL_SaveBMP(tile, tilePath) != 0)
                        {
                                printf("Failed to save cleaned tile at path : %s\n", tilePath);
                        }

                        SDL_FreeSurface(tile);
                }
        }

	for (size_t i = 0; i < 9; i++)
        {
                for (size_t j = 0; j < 9; j++)
                {
                        char tilePath[50];
                        sprintf(tilePath, "Tiles/tile_%zu_%zu.bmp", i, j);
                        SDL_Surface* tile = IMG_Load(tilePath);
			CenterTile(tile, tilePath);
			SDL_FreeSurface(tile);
		}
        }

	printf("started PrintNumbers...\n");
	PrintNumbers("TemplateGrids/grid.txt", "TemplateGrids/solved_grid.txt");

	return 0;
}
