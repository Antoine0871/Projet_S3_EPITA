#ifndef TOOLBOX
#define TOOLBOX

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <err.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h> 
#include <libgen.h> 
#include <time.h> 

#define NB_IMAGES 29*9 //34 set of 9 number
#define NB_TRAINING NB_IMAGES*70/100 + 1
#define NB_TEST NB_IMAGES*30/100
#define IMAGES_SIZE 28

typedef struct Images_Set
{
    char Training_Set[NB_TRAINING][1+IMAGES_SIZE*IMAGES_SIZE];
    char Test_Set[NB_TEST][1+IMAGES_SIZE*IMAGES_SIZE];
}Images_Set;

double getMax(double val[], size_t len);
size_t getMaxIndex(double val[], size_t len);
void softmax(double val[], size_t len);
void softmax_prime(double val[], double d_val[], size_t len);
double relu(double x);
double sigmoid(double x);
double sigmoid_prime(double x);
double rnd();
double error(double res, double expected);
double meanSquarredError(double result[], double expected[], size_t len);
double crossEntropy(double result[], double expected[], size_t len);
void Fill_Set(Images_Set* set);
void Convert_Image2Number(Images_Set *set, char *fileName,char mode, int index);
Uint32 get_Pixel(SDL_Surface *surf , unsigned x, unsigned y);
#endif
