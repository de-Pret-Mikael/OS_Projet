//
// Created by Cyril Grandjean on 26-11-20.
//
#include "math.h"
#include "stdio.h"
int random(Fvalue,Svalue){
    float nbrRand = Svalue - Fvalue;
    float number = rand();
    return number;
}
void main(){
    printf(random(25,45));
}
