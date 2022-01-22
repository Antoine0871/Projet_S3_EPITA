#include "ToolBox.h"
        
double relu(double x)
{
    if(x > 0)
        return x;
    return 0;
}

double sigmoid(double x)
{
    return (1.0/(exp(-x)+1.0));
}

double sigmoid_prime(double x)
{
    return((x)*(1-(x)));
}

double rnd()
{
    return (double)rand()/((double)RAND_MAX/2)-1;
}

void softmax(double val[], size_t len)
{
    double shift = getMax(val, len);
    double expsum = 0;
    for(size_t i = 0; i < len; i++)
    {
        val[i] -= shift;
        expsum += exp(val[i]);
    }
    for(size_t i = 0; i < len; i++)
    {
        val[i] = exp(val[i])/expsum;
    }

}

void softmax_prime(double val[], double d_val[], size_t len)
{
    double xpsum = 0;
    double jacobian[len][len];
    double si;
    double sj;
    double shift = getMax(val, len);
    for(size_t i = 0; i < len; i++)
    {
        val[i] -= shift;
        xpsum += exp(val[i]);
    }
    for(size_t i = 0; i < len; i++)
    {
        for(size_t j = 0; j < len; j++)
        {
            si = exp(val[i])/xpsum;
            sj = exp(val[j])/xpsum;
            if(i == j)
                jacobian[i][j] = si*(1-si);
            else
                jacobian[i][j] = -si*sj;
            d_val[i] += jacobian[i][j] * val[j];
        }
    }

}

double error(double res, double expected)
{
    return (res - expected == 0) ? 0 : 1;
}

double meanSquarredError(double result[], double expected[], size_t len)
{
    double sum = 0;
    for(size_t i = 0; i < len; i++)
    {
        sum += (expected[i] - result[i]) * (expected[i] - result[i]);
    }
    return sqrt((1.0/len) * sum);
}

double crossEntropy(double result[], double expected[], size_t len)
{
    double sum = 0;
    for(size_t i = 0; i < len; i++)
    {
        if(result[i] == 0)
            sum += -INFINITY;
        else
            sum += expected[i] * log2(result[i]);
    }
    return -sum;
}

double getMax(double val[], size_t len)
{
    double max = val[0];
    for(size_t i = 1; i < len; i++)
    {
        max = (val[i] > max) ? val[i] : max;
    }
    return max;
}

size_t getMaxIndex(double val[], size_t len)
{
    size_t maxi = 0;
    double max = val[0];
    for(size_t i = 1; i < len; i++)
    {
        if(val[i] > max)
        {
            maxi = i;
            max = val[i];
        }
    }
    return maxi;
}

static inline
Uint8* pixel_Ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_Pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_Ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
}


void Convert_Image2Number(Images_Set *set, char *fileName, char mode, int index)
{
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(EXIT_FAILURE,"Invalide image");
    SDL_Surface *img;
    img = IMG_Load(fileName);
    if(!img)
        errx(1,"Invalide path : %s", fileName);
    int width = img->w;
    int height = img->h;
   // if(height!=width && height!=16)
     //   errx(1,"Invalide image : size too big :%d * %d, %s",width, height, fileName);
    size_t count = 1;
    Uint32 pixel;
    Uint8 r,g,b;
    for(size_t i = 0; i < 28*28+1; i++)
    {
        if(!mode)
            set->Training_Set[index][i] = 0;
        else
            set->Test_Set[index][i] = 0;
    }
    for(size_t i = 0; i < (size_t)height; i++)
    {
        for(size_t j = 0; j <(size_t) width; j++)
        {
            pixel = get_Pixel(img,j,i);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            if(!mode)
               set->Training_Set[index][count] = (r >=  245) ? 0 : 1;
            else
                set->Test_Set[index][count] = (r >= 245) ? 0 : 1;
            count++;
        }
    }
    char number = fileName[strlen(fileName)-5];
    if(!mode)
        set->Training_Set[index][0] = number;
    else
        set->Test_Set[index][0] = number;
    SDL_FreeSurface(img);
}

void Fill_Set(Images_Set* set)
{
    srand(time(NULL)); 
    int index;
    int training_i = 0;
    int test_i = 0;
    char mode;
    DIR *dp;
    struct dirent *dirp;
    dp = opendir("../BIBLIOTHEQUE");
    if(dp == NULL)
    {
        perror("opendir() failed");
        exit(EXIT_FAILURE);
    }
    char fileName[342] = "../BIBLIOTHEQUE/";
    while((dirp = readdir(dp)) != NULL)
    {
        if(strcmp(dirp->d_name, "..") == 0 || strcmp(dirp->d_name,".") == 0)
            continue;
        for(char i = 1; i < 10;i++)
        {
            sprintf(fileName,"../BIBLIOTHEQUE/%s/%d.bmp",dirp->d_name,i);
            if(training_i == NB_TRAINING)
            {
                index = test_i;
                mode = 1;
                test_i++;
            }
            else if(test_i == NB_TEST)
            {
                index = training_i;
                mode = 0;
                training_i++;
            }
            else
            {
                if(rand() % 100 < 70)
                {
                    index = training_i;
                    mode = 0;
                    training_i++;
                }
                else
                {
                    index = test_i;
                    mode = 1;
                    test_i++;
                }
            }
            Convert_Image2Number(set,fileName,mode,index);
            index++;
        }
 
    }
    closedir(dp);
}
