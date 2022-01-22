#include "SaveLoad.h"

void XOR_Save(struct XOR_Neural_Network *XOR)
{
    FILE *fp;
    fp = fopen(".save_xor","w+");
    for(int i = 0; i < NB_INPUT*NB_HIDDEN;i++)
    {
        fprintf(fp,"%f\n",XOR->WeightIH[i]);
    }
    for(int i = 0; i < NB_HIDDEN;i++)
    {
        fprintf(fp,"%f\n%f\n",XOR->WeightHO[i],XOR->BiasH[i]);
    }
	fprintf(fp,"%f\n",XOR->BiasO);
    fclose(fp);
}

void XOR_Load(struct XOR_Neural_Network *XOR)
{
    XOR->Expected[0] = 0;
    XOR->Expected[1] = 1;
    XOR->Expected[2] = 1;
    XOR->Expected[3] = 0;

    XOR->InputVal[0] = 0; XOR->InputVal[1] = 0;
    XOR->InputVal[2] = 0; XOR->InputVal[3] = 1;
    XOR->InputVal[4] = 1; XOR->InputVal[5] = 0;
    XOR->InputVal[6] = 1; XOR->InputVal[7] = 1;
    FILE *fp;
    fp = fopen(".save_xor","r+");
	if (fp == 0)
		printf("You didn't trained a neural network yet:(\n");
	else
	{

		char line[50];
		char *val;
		for(int i = 0;i<NB_INPUT*NB_HIDDEN;i++)
		{
		    XOR->WeightIH[i] = strtod(fgets(line,sizeof(line),fp),&val);
            XOR->dWeightIH[i] = 0;
		}

		for(int i = 0;i<NB_HIDDEN;i++)
		{
			XOR->WeightHO[i] = strtod(fgets(line,sizeof(line),fp),&val);
			XOR->dWeightHO[i] = 0;
			XOR->BiasH[i] = strtod(fgets(line,sizeof(line),fp),&val);
		}
		XOR->BiasO = strtod(fgets(line,sizeof(line),fp),&val);
	}
	fclose(fp);
}
