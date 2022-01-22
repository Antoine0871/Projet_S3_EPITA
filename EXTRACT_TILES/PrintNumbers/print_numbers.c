#include<stdlib.h>
#include<stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_rotozoom.h>
#include"../PixelOperations/pixel_operations.h"
#include<math.h>
#include<time.h>

void Print(SDL_Surface* image, char number, int color, size_t i, size_t j);

void PrintNumbers(char originalGrid[], char solvedGrid[])
{
	srand(time(NULL));

	SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* image = IMG_Load("../EXTRACT_TILES/PrinterImages/empty_grid.bmp");

	FILE* sgrid = NULL;
	sgrid = fopen(solvedGrid, "r");
	char currentChar;

	FILE* grid = NULL;
    grid = fopen(originalGrid, "r");
    char initialState;

	for (size_t i = 0; i < 9; i++)
	{
		for (size_t j = 0; j < 9; j++)
		{
			do
			{
				currentChar = fgetc(sgrid);
				initialState = fgetc(grid);
			} while (currentChar == ' ' || currentChar == '\n');
			if(currentChar == '0')
				continue;
			if (currentChar == EOF)
			{
				break;
			}

			if (initialState == '.')
			{
				//int color = rand() % 10;
				Print(image, currentChar, /*color*/ 0, i, j);
			}
			else
			{
				Print(image, currentChar, -1, i, j);
			}
		}

		if (currentChar == EOF)
		{
			break;
		}
	}

	if (SDL_SaveBMP(image, "../EXTRACT_TILES/TreatedImages/image_solved.bmp") != 0)
        {
                printf("Failed to save solved image at path : %s\n", "../EXTRACT_TILES/TreatedImages/image_solved.bmp");
        }

	fclose(sgrid);
	fclose(grid);
	SDL_FreeSurface(image);
}

void Print(SDL_Surface* image, char number, int color, size_t i, size_t j)
{
	size_t width = (size_t)image->w;
	size_t height = (size_t)image->h;

	char tilePath[50];
	sprintf(tilePath, "../EXTRACT_TILES/PrinterImages/tile_%c.bmp", number);
	SDL_Surface* tile = IMG_Load(tilePath);

	size_t widthTile = (size_t)tile->w;
	size_t heightTile = (size_t)tile->h;

	for (size_t x = 0; x < widthTile; x++)
	{
		for (size_t y = 0; y < heightTile; y++)
		{
			Uint32 imagePixel;
                        imagePixel = get_pixel(image, x, y);
                        Uint32 tilePixel;
                	tilePixel = get_pixel(tile, x, y);
			Uint8 r, g, b;
                        SDL_GetRGB(tilePixel, tile->format, &r, &g, &b);
			if (r == 0)
			{
				switch (color)
				{
					case 0:
						imagePixel = SDL_MapRGB(image->format, 255, 0, 0);
                                		put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
						break;
					case 1:
						imagePixel = SDL_MapRGB(image->format, 0, 255, 0);
                                                put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
						break;
					case 2:
						imagePixel = SDL_MapRGB(image->format, 0, 0, 255);
                                                put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
                                                break;
					case 3:
						imagePixel = SDL_MapRGB(image->format, 255, 204, 255);
                                                put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
                	                        break;
					case 4:
						imagePixel = SDL_MapRGB(image->format, 255, 255, 51);
                                                put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
                                                break;
					case 5:
						imagePixel = SDL_MapRGB(image->format, 0, 255, 255);
                                                put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
                                                break;
					case 6:
						imagePixel = SDL_MapRGB(image->format, 204, 0, 204);
                                                put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
                                                break;
					case 7:
						imagePixel = SDL_MapRGB(image->format, 255, 153, 51);
                                                put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
                                                break;
					case 8:
						imagePixel = SDL_MapRGB(image->format, 153, 0, 0);
                                                put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
                                                break;
					case 9:
						imagePixel = SDL_MapRGB(image->format, 204, 153, 255);
						put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, imagePixel);
                                                break;
					default:
						imagePixel = SDL_MapRGB(image->format, r, g, b);
                                		put_pixel(image, x + (width / 9) * j, y + (height / 9) * i, tilePixel);
						break;
				}
			}
		}
	}

	SDL_FreeSurface(tile);
}







