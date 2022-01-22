#include "XOR_Neural_Network.h"
#include "SaveLoad/SaveLoad.h"

void NetworkInit(struct XOR_Neural_Network *XOR)
{
    srand(time(NULL));

    XOR->ErrorRate = 0;

    XOR->Expected[0] = 0;
    XOR->Expected[1] = 1;
    XOR->Expected[2] = 1;
    XOR->Expected[3] = 0;

    XOR->InputVal[0] = 0; XOR->InputVal[1] = 0;
    XOR->InputVal[2] = 0; XOR->InputVal[3] = 1;
    XOR->InputVal[4] = 1; XOR->InputVal[5] = 0;
    XOR->InputVal[6] = 1; XOR->InputVal[7] = 1;
    //setting all the weight and the bias to a random value between 0 and 1
    //and the delta of the weight to 0
    for(int i = 0; i < NB_INPUT*NB_HIDDEN;i++)
    {
        XOR->WeightIH[i] = rnd();
        XOR->dWeightIH[i] = 0;
    }

    for(int i = 0; i < NB_HIDDEN;i++)
    {
        XOR->WeightHO[i] = rnd();
        XOR->BiasH[i] = rnd();
        XOR->dWeightHO[i] = 0;
    }
    XOR->BiasO = rnd();
}



void ForwardPass(struct XOR_Neural_Network *XOR,int patternNb)
{
    double Sum;
    for(int i = 0; i < NB_HIDDEN;i++)
    {
        //Sum = input*weight for all the neuron of the hidden layer + bias
        Sum = 0;
        for(int j = 0; j < NB_INPUT;j++)
        {
            Sum += XOR->InputVal[j+patternNb*NB_HIDDEN] *
                XOR->WeightIH[i+j*NB_HIDDEN];
        }

        XOR->OutputH[i] = sigmoid(Sum + XOR->BiasH[i]);
    }

    Sum = 0;
    for(int i = 0;i < NB_HIDDEN;i++)
    {
        Sum += XOR->OutputH[i] * XOR->WeightHO[i];
    }
    XOR->Result = sigmoid(Sum + XOR->BiasO);
    XOR->ErrorRate += 0.5 * (XOR->Expected[patternNb] - XOR->Result) *
           (XOR->Expected[patternNb] - XOR->Result);
}

void Backtracking(struct XOR_Neural_Network *XOR,int patternNb)
{
    XOR->dResult = (XOR->Expected[patternNb] - XOR->Result) *
        sigmoid_prime(XOR->Result);

    for(int i = 0; i < NB_HIDDEN;i++)
    {
        XOR->dOutputH[i] = XOR->WeightHO[i] * XOR->dResult *
            sigmoid_prime(XOR->OutputH[i]);
    }

    XOR->BiasO += ETA * XOR->dResult;
    for(int i = 0; i < NB_HIDDEN;i++)
    {
        for(int j = 0; j < NB_INPUT;j++)
        {
            XOR->dWeightIH[i + j * NB_HIDDEN] = ETA * XOR->dOutputH[i] *
                XOR->InputVal[i+patternNb * NB_INPUT] + ALPHA *
                XOR->dWeightIH[i + j * NB_HIDDEN];

            XOR->WeightIH[i + j * NB_HIDDEN] +=
                XOR->dWeightIH[i + j * NB_HIDDEN];
        }

        XOR->BiasH[i] = ETA * XOR->dResult;
        XOR->dWeightHO[i] = ETA * XOR->OutputH[i] * XOR->dResult +
            ALPHA * XOR->dWeightHO[i];
        XOR->WeightHO[i] += XOR->dWeightHO[i];
    }
}

double XOR_Calc(struct XOR_Neural_Network *XOR, double a, double b)
{
	int patternNb = 0;
	if(a == 0){
		if(b==1){
			patternNb = 1;}}
	else if (a==1){
		if(b==0){
			patternNb = 2;}
		else{
			patternNb = 3;}}
	ForwardPass(XOR,patternNb);
	return XOR->Result;
}

void XOR_Train(struct XOR_Neural_Network *XOR)
{
    int patternNb = 4, epochNb = 0;
    do
    {
        if(epochNb%100==0)
            printf("\n========================================================"\
                    "\nEpoch n.%d :\n",epochNb);
        XOR->ErrorRate = 0;
        for(int j = 0; j < patternNb; j++)
        {
            ForwardPass(XOR,j);
            Backtracking(XOR,j);
            if(epochNb%100 == 0)
            {
                printf("%f XOR %f = %f, expected : %f\n",
                        XOR->InputVal[j*2],
                        XOR->InputVal[j*2+1],
                        XOR->Result,
                        XOR->Expected[j]);
            }
        }
        if(epochNb%100 == 0)
        {
            printf("Error rate = %f\n"\
                "========================================================\n",
                XOR->ErrorRate);
        }
        epochNb++;
    }while(XOR->ErrorRate > 0.001);
    printf("\n========================================================"\
            "\n                 TRAINING COMPLETED!\n"
            "Epoch needed : %d              Error rate : %lf\n"\
            "========================================================\n",
            epochNb, XOR->ErrorRate);
    XOR_Save(XOR);
}
