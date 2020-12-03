//
// Created by patris on 26/11/20.
//
#pragma once
const int NBR_CAR = 20;
const int ID_CAR[20] = {
        44, 77, 16, 5, 33, 23, 55, 4, 3, 31, 10, 26, 11, 18, 7, 99, 20, 8, 63, 6};
const char SECTEUR[3][2] = {"S1", "S2", "S3"};
int tour = 1;
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
    char stand;//"F";
    char out;//"F";
} tableauVoiture[20];