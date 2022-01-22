#include "Neural_Network.h"
#include "SaveLoad/SaveLoad.h"
#include "mnist.h"

void NetworkInit(Neural_Network *nn)
{
    srand(time(NULL));

    nn->ErrorRate = 0;

    //setting all the weight and the bias to a random value between 0 and 1
    //and the delta of the weight to 0
    for(int i = 0; i < NB_INPUT*NB_HIDDEN;i++)
    {
        nn->WeightIH[i] = rnd();
        nn->dWeightIH[i] = 0;
    }

    for(int i = 0; i < NB_HIDDEN* NB_OUTPUT;i++)
    {
        nn->WeightHO[i] = rnd();
        nn->dWeightHO[i] = 0;
    }
    for(int i = 0; i< NB_HIDDEN; i++)
    {
        nn->BiasH[i] = rnd();
    }
    for(int i = 0; i < NB_OUTPUT;i++)
    {
        nn->BiasO[i] = rnd();
    }
}



void ForwardPass(Neural_Network *nn)
{
    double Sum;
    for(int i = 0; i < NB_HIDDEN; i++)
    {
        Sum = 0;
        for(int j = 0; j < NB_INPUT; j++)
        {
            Sum += nn->image[j] * nn->WeightIH[i + NB_HIDDEN * j];
        }
        nn->OutputH[i] = sigmoid(Sum + nn->BiasH[i]);
    }
    for(int i = 0;i < NB_OUTPUT; i++)
    {
        Sum = 0;
        for(int j = 0; j < NB_HIDDEN; j++)
        {
            Sum += nn->OutputH[j] * nn->WeightHO[i + NB_OUTPUT * j];
        }
        nn->OutputO[i] = sigmoid(Sum + nn->BiasO[i]);
    }
    /*for(int i = 0; i< NB_OUTPUT; i++)
    {
        printf("%f ", nn->OutputO[i]);
    }
    printf("\n");*/
    //softmax(nn->OutputO, NB_OUTPUT);
    nn->ResultVal = getMax(nn->OutputO, NB_OUTPUT);
    nn->Result = getMaxIndex(nn->OutputO, NB_OUTPUT) + 1;
    for(int i = 0; i < NB_OUTPUT; i++)
    {
        if(nn->Expected[i] == 1)
            nn->ErrorRate += error(nn->Result, i+1);
    }
        //meanSquarredError(nn->OutputO, nn->Expected, NB_OUTPUT);
}

void BackwardPass(Neural_Network *nn)
{
    for(int i = 0; i < NB_OUTPUT; i++)
    {
        nn->dOutputO[i] = (nn->Expected[i]- nn->OutputO[i]) *
        sigmoid_prime(nn->OutputO[i]);
    }

    for(int i = 0; i < NB_HIDDEN; i++)
    {
        nn->dOutputH[i] = 0;
        for(int j = 0; j < NB_OUTPUT; j++)
        {
            nn->dOutputH[i] += nn->WeightHO[j + NB_OUTPUT * i] *nn->dOutputO[j];
        }
        nn->dOutputH[i] *= sigmoid_prime(nn->OutputH[i]);
    }

    for(int i = 0; i < NB_OUTPUT; i++)
    {
        nn->BiasO[i] += LEARNING_RATE * nn->dOutputO[i];
        for(int j = 0; j < NB_HIDDEN; j++)
        {
            nn->WeightHO[i + NB_OUTPUT * j] += LEARNING_RATE *
                nn->OutputH[j] * nn->dOutputO[i];
        }
    }

    for(int i = 0; i < NB_HIDDEN; i++)
    {
        nn->BiasH[i] += LEARNING_RATE * nn->dOutputH[i];
        for(int j = 0; j < NB_INPUT; j++)
        {
            nn->WeightIH[i + NB_HIDDEN * j] += LEARNING_RATE *
                nn->image[j] * nn->dOutputH[i];
        }

    }
}

void NN_Train(Neural_Network *nn, Images_Set *set)
{
    for(int j = 0 ; j < 1000; j++)
    {
	    for(int i = 0; i < NB_TRAINING; i++)
	    {
            for(int k = 1; k < NB_INPUT+1; k++)
                 {
                    nn->image[k-1] = (double)set->Training_Set[i][k];
                }
            for(int k = 0; k < NB_OUTPUT; k++)
            {
                if((int) set->Training_Set[i][0] == k + 1 + '0')
                    nn->Expected[k] = 1;
                else
                    nn->Expected[k] = 0;
            }
            ForwardPass(nn);
            BackwardPass(nn);
        }
    }
    NN_Save(nn);
}

void NN_Test(Neural_Network *nn, Images_Set *set)
{
	nn->ErrorRate = 0;
    for(int i = 0; i < NB_TEST; i++)
    {
        for(int j = 1; j < NB_INPUT+1; j++)
        {
            nn->image[j-1] = (double) set->Test_Set[i][j];
        }
        for(int k = 0; k < NB_OUTPUT; k++)
        {
            if((int) set->Test_Set[i][0] == k + 1 + '0')
                nn->Expected[k] = 1;
            else
                nn->Expected[k] = 0;
        }
        ForwardPass(nn);
        printf("Got :%d,%c was expected\n",(int)nn->Result,set->Test_Set[i][0]);
    }
    //double total = (double) NB_TEST + NUM_TEST;
    int test = NB_TEST;
    printf("Error : %f\n",(nn->ErrorRate*100) * 1. / (double)test);
}

void NN_img2nn(Neural_Network *nn, char path[])
{
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(EXIT_FAILURE, "Invalide image");
    SDL_Surface *img;
    img = IMG_Load(path);
    if(!img)
        errx(1,"Invalide path : %s", path);
    int width = img->w;
    int height = img->h;
    /*if(height != width && height != 16)
        errx(1,"Invalide image : size to big or to small");*/
    Uint32 pixel;
    Uint8 r,g,b;
    int count = 0;
    for(size_t i = 0; i <(size_t) height; i++)
    {
        for(size_t j = 0; j < (size_t) width; j++)
        {
            pixel = get_Pixel(img, j, i);
            SDL_GetRGB(pixel, img->format,&r,&g,&b);
            nn->image[count] = (r >= 245) ? 0 : 1;
            count++;
        }
    }
    pixel = get_Pixel(img, 0, 0);
    SDL_GetRGB(pixel, img->format, &r, &g, &b);
    if(r == 42)
        nn->image[0] = 42;
    SDL_FreeSurface(img);
}


size_t NN_Calc(Neural_Network *nn, char path[])
{
    NN_img2nn(nn, path);
    if(nn->image[0] == 42)
        return 0;
    ForwardPass(nn);
    return nn->Result;
}

void images2txt(Neural_Network *nn)
{
    FILE *fp;
    fp = fopen("grid_01.txt","w+");
    if(!fp)
        errx(1,"Something went wrong");
    char path[50];
    size_t res;
    char l = 0, c = 0;
    for(size_t y = 0; y < 9; y++)
    {
        for(size_t x = 0; x < 9; x++)
        {
            sprintf(path, "../EXTRACT_TILES/Tiles/tile_%zu_%zu.bmp", x, y);
            res = NN_Calc(nn, path);
            if(res == 0 || nn->OutputO[res-1] < 0.5)
                fprintf(fp, ".");
            else
                fprintf(fp, "%lu", res);
            c++;
            if(c%3 == 0 && c%9 != 0)
                fprintf(fp, " ");
        }
        fprintf(fp, "\n");
        l++;
        if(l%3 == 0)
            fprintf(fp, "\n");
    }
    fclose(fp);
}
