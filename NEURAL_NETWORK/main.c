#include "Neural_Network.h" 
#include "SaveLoad/SaveLoad.h"
int main()
{
    Neural_Network nn;
    Images_Set set;
    Fill_Set(&set);
    NetworkInit(&nn);
    NN_Train(&nn,&set);
    //NN_Load(&nn, "good_nn");
    //NN_Save(&nn);
    images2txt(&nn);    
    NN_Test(&nn, &set);
    //NN_Save(&nn);
    //size_t res = NN_Calc(&nn, "../../Downloads/tile_2_5.bmp");
    return 0;
}
