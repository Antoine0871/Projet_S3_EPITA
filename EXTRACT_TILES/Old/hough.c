#include<stdlib.h>
#include<iostream>
#include<SDL2/SDL.h>
using namespace std;

void Transorm()

size_t array_max_index(int array[], size_t len)
{
    unsigned int max_index = 0;
    for (unsigned int i = 0; i < len; i++)
    {
            if (array[i] > array[max_index])
            {
                    max_index = i;
            }
    }
    return max_index;
}
