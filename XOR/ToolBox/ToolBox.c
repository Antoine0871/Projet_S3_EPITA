#include "ToolBox.h"

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
    return (double)rand()/(double)RAND_MAX;
}
