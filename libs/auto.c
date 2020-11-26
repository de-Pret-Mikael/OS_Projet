//
// Created by patris on 26/11/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const ID_CAR[20] = {44, 77, 16, 5, 33, 23, 55, 4, 3, 31, 10, 26, 11, 18, 7, 99, 20, 8, 63, 6};
const secteur[3] = {"S1","S2","S3"};

typedef struct voiture{
    int id = 0;
    float timeS1 = 0;
    float bestTimeS1 = INFINITY;
    float timeS2 = 0;
    float bestTimeS2 = INFINITY;
    float timeS3 = 0;
    float bestTimeS3 = INFINITY;
    float totTime = timeS1 + timeS2 + timeS3;
    float bestTimeSect = 0;
    char stand = "F";
    char out = "F";

    void upDateTimeS1(float timeS1, float bestTimeS1){

    }
/*
    int upDateTimeS2(){

    }

    int upDateTimeS3(){

    }

    int conserve(){
        if (stand != "F" || out != "F"){

        }
    };
    */
}voiture;

int main(int argc, char** argv){
    printf("%f\n", upDateTimeS1(10.4, 2.5))
}