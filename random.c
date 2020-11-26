//
// Created by Cyril Grandjean on 26-11-20.
//
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float my_random(float Fvalue, float Svalue, int seed) {
    float minMax = Svalue - Fvalue;
    srand(seed);
    float nbrRand = rand() * pow(RAND_MAX,-1);
    float numberF = nbrRand * Fvalue;
    float number = minMax + numberF;
    return number;
}

/*1804289383*/
void main() {
    int nbr = 11;
    for(int nbrTour = 0;nbrTour < 3;nbrTour++){
        for (int i = 1; i < nbr; i++) {
            int seed = i + (nbr*nbrTour);
            printf("%f\n", my_random(25.0, 45.0,seed));
        }
    }
}
