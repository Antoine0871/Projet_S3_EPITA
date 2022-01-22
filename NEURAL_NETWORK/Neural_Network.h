#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK


#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <time.h>
#include <unistd.h>
#include "ToolBox/ToolBox.h"

#define NB_INPUT 28*28//IMAGES_SIZE*IMAGES_SIZE 
#define NB_HIDDEN 150
#define NB_OUTPUT 9
#define LEARNING_RATE 0.01

typedef struct Neural_Network
{

    double ErrorRate;

    double Expected[NB_OUTPUT];
    
    double image[NB_INPUT];
    //weight from the input to the hidden layer
    double WeightIH[NB_INPUT*NB_HIDDEN];
    //weight from the hidden to the output layer
    double WeightHO[NB_HIDDEN*NB_OUTPUT];
    //delta arrays for backtracking
    double dWeightIH[NB_INPUT*NB_HIDDEN];
    double dWeightHO[NB_HIDDEN*NB_OUTPUT];

    //bias array for the hidden layer + the bias of the output neuron
    double BiasH[NB_HIDDEN];
    double BiasO[NB_OUTPUT];

    //output arrays of the hidden layer + delta for backtracking
    double OutputH[NB_HIDDEN];
    double dOutputH[NB_HIDDEN];

    //output from the output layer neuron giving the
    double OutputO[NB_OUTPUT];
    double dOutputO[NB_OUTPUT];

    double ResultVal;
    double Result;
}Neural_Network;

void NetworkInit(Neural_Network *nn);
void NN_Train(Neural_Network *nn, Images_Set *set);
size_t NN_Calc(Neural_Network *nn, char path[]);
void NN_Test(Neural_Network *nn, Images_Set *set);
void images2txt(Neural_Network *nn);
#endif
