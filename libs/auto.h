//
// Created by patris on 26/11/20.
//
#pragma once
typedef struct voiture car;
struct voiture {
    int numero;
    float timeS1;//= 0;
    float bestTimeS1;//= INFINITY;
    float timeS2;//= 0;
    float bestTimeS2;//= INFINITY;
    float timeS3;//= 0;
    float bestTimeS3;//= INFINITY;
    float tourTime;//= timeS1 + timeS2 + timeS3;
    float bestTourTime;
    float totalTime;
    float gap;
    char stand;//"F";
    char out;//"F";
};