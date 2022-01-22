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


void ExtractGrid(char path[])
{
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Surface* image = IMG_Load(path);

        if (image == 0)
        {
                printf("main: failed to load image at %s : %s\n", path, SDL_GetError());
        }

        WatershedSegmentation(image, 0);

        if (SDL_SaveBMP(image, "../EXTRACT_TILES/TreatedImages/image_grid_only.bmp") != 0)
        {
                printf("Failed to save grid only image at path : %s\n", "../EXTRACT_TILES/TreatedImages/image_grid_only.bmp");
        }

	SDL_FreeSurface(image);
}

void ExtractTile(char path[])
{
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Surface* image = IMG_Load(path);

	if (image == 0)
        {
                printf("main: failed to load image at %s : %s\n", path, SDL_GetError());
        }

        WatershedSegmentation(image, 0);

        if (SDL_SaveBMP(image, "../EXTRACT_TILES/TreatedImages/image_grid_only.bmp") != 0)
        {
                printf("Failed to save grid only image at path : %s\n", "../EXTRACT_TILES/TreatedImages/image_grid_only.bmp");
        }

        SDL_Surface* treatedImage = IMG_Load("../EXTRACT_TILES/TreatedImages/image_grid_only.bmp");
        SDL_FreeSurface(image);
        image = IMG_Load(path);
        CutImage(treatedImage, image);

        SDL_FreeSurface(treatedImage);
        SDL_FreeSurface(image);

	for (size_t i = 0; i < 9; i++)
        {
                for (size_t j = 0; j < 9; j++)
                {
                        char tilePath[50];
                        sprintf(tilePath, "../EXTRACT_TILES/Tiles/tile_%zu_%zu.bmp", i, j);
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
                        sprintf(tilePath, "../EXTRACT_TILES/Tiles/tile_%zu_%zu.bmp", i, j);
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
                        sprintf(tilePath, "../EXTRACT_TILES/Tiles/tile_%zu_%zu.bmp", i, j);
                        SDL_Surface* tile = IMG_Load(tilePath);
                        CenterTile(tile, tilePath);
                        SDL_FreeSurface(tile);
		}
	}
}

void GetResizedImages()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Surface* grid = IMG_Load("../EXTRACT_TILES/TreatedImages/image_grid_only.bmp");
	SDL_Surface* colorized = IMG_Load("../EXTRACT_TILES/TreatedImages/image_colorized.bmp");

	SDL_Surface* gridResized = ResizeImage(grid, 1200, 700);
	SDL_Surface* colorizedResized = ResizeImage(colorized, 1200, 700);

	if (SDL_SaveBMP(gridResized, "../EXTRACT_TILES/TreatedImages/image_grid_only_resized.bmp") != 0)
        {
        	printf("Failed to save resized grid at path : %s\n", "../EXTRACT_TILES/TreatedImages/image_grid_only_resized.bmp");
        }

	if (SDL_SaveBMP(colorizedResized, "../EXTRACT_TILES/TreatedImages/image_colorized_resized.bmp") != 0)
        {
                printf("Failed to save resized colorized image at path : %s\n", "../EXTRACT_TILES/TreatedImages/image_colorized_resized.bmp");
        }

	SDL_FreeSurface(grid);
	SDL_FreeSurface(colorized);
	SDL_FreeSurface(gridResized);
	SDL_FreeSurface(colorizedResized);
}

void PrintResult(char originalGrid[], char solvedGrid[])
{
	PrintNumbers(originalGrid, solvedGrid);
}
