#include "SaveLoad.h"

void NN_Save(Neural_Network *nn)
{  
    FILE *fp;
    fp = fopen(".save_nn","w+");
    for(int i = 0; i < NB_INPUT*NB_HIDDEN; i++)
    {
        fprintf(fp,"%f\n",nn->WeightIH[i]);
    }
    for(int i = 0; i < NB_HIDDEN * NB_OUTPUT; i++)
    {
        fprintf(fp,"%f\n",nn->WeightHO[i]);
    }
    for(int i = 0; i < NB_HIDDEN; i++)
    {
        fprintf(fp,"%f\n",nn->BiasH[i]);
    }
    for(int i = 0; i < NB_OUTPUT; i++)
    {
	    fprintf(fp,"%f\n",nn->BiasO[i]);
    }
    fclose(fp);
}

void NN_Load(Neural_Network *nn, char path[])
{
    FILE *fp;
    fp = fopen(path, "r+");
	if (fp == 0)
		errx(1,"You didn't trained a neural network yet:(\n");
	else
	{
		char line[50];
		char *val;
		for(int i = 0; i< NB_INPUT*NB_HIDDEN; i++)
		{   
		    nn->WeightIH[i] = strtod(fgets(line,sizeof(line),fp),&val);
            nn->dWeightIH[i] = 0;
		}
		for(int i = 0; i<NB_HIDDEN * NB_OUTPUT; i++)
		{
			nn->WeightHO[i] = strtod(fgets(line,sizeof(line),fp),&val);
			nn->dWeightHO[i] = 0;
		}
        for(int i = 0; i < NB_HIDDEN; i++)
        {
			nn->BiasH[i] = strtod(fgets(line,sizeof(line),fp),&val);
        }
        for(int i = 0; i < NB_OUTPUT; i++)
        {
		    nn->BiasO[i] = strtod(fgets(line,sizeof(line),fp),&val);
        }
	}
	fclose(fp);
}
