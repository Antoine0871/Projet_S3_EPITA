#ifndef XOR_NEURAL_NETWORK
#define XOR_NEURAL_NETWORK


#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <time.h>
#include <unistd.h>
#include "ToolBox/ToolBox.h"

#define NB_INPUT 2
#define NB_HIDDEN 3 
#define NB_OUTPUT 1
#define ETA 3.0
#define ALPHA 1/ETA //learning rate
#define PATTERN_Nb 4


struct XOR_Neural_Network
{
    double Expected[4];
    double InputVal[8];

    double ErrorRate;
    //weight from the input to the hidden layer
    double WeightIH[NB_INPUT*NB_HIDDEN];
    //weight from the hidden to the output layer
    double WeightHO[NB_HIDDEN*NB_OUTPUT];
    //delta arrays for backtracking
    double dWeightIH[NB_INPUT*NB_HIDDEN];
    double dWeightHO[NB_HIDDEN*NB_OUTPUT];

    //bias array for the hidden layer + the bias of the output neuron
    double BiasH[NB_HIDDEN];
    double BiasO;

    //output arrays of the hidden layer + delta for backtracking
    double OutputH[NB_HIDDEN];
    double dOutputH[NB_HIDDEN];

    //output from the output layer neuron giving the
    double Result;
    double dResult;
};

void NetworkInit(struct XOR_Neural_Network *XOR);
void XOR_Train(struct XOR_Neural_Network *XOR);
double XOR_Calc(struct XOR_Neural_Network *XOR,double a,double b);
#endif
