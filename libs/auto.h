//
// Created by patris on 26/11/20.
//
#pragma once
typedef struct voiture car;
struct voiture {
    int numero;
    int index;
    int finish;
    int nbrTour;
    float timeS1;//= 0;
    float bestTimeS1;//= INFINITY;
    int posS1;
    float timeS2;//= 0;
    float bestTimeS2;//= INFINITY;
    int posS2;
    float timeS3;//= 0;
    float bestTimeS3;//= INFINITY;
    int posS3;
    float tourTime;//= timeS1 + timeS2 + timeS3;
    float bestTourTime;
    int posTour;
    float totalTime;
    float gap;
    char stand;//"F";
    char out;//"F";
};

void update_time(car *voiture);