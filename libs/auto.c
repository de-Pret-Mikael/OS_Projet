//
// Created by patris on 26/11/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "randomTime.h"
#include <unistd.h>
#include <time.h>

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
    float totTime;//= timeS1 + timeS2 + timeS3;
    char stand;//"F";
    char out;//"F";
} tableauVoiture[20];


void init() {
    for (int i = 0; i < NBR_CAR; i++) {
        tableauVoiture[i].numero = ID_CAR[i];
    }
}

car* select_car(int id) {
    car *obj;
    for(int i = 0; i < NBR_CAR;i++){
        obj = &tableauVoiture[i];
        if (obj->numero == id){
            return obj;
        }
    }
    return NULL;
}



int update_time(int id){
    int min = 25;
    int max = 45;
    car* voiture = select_car(id);
    voiture->timeS1 = randomRange(min,max);
    voiture->timeS2 = randomRange(min,max);
    voiture->timeS3 = randomRange(min,max);
}

int main(int argc, char **argv) {
    srand48(time(NULL));
    init();
    car* voiture = select_car(16);
    update_time(16);
    printf("%f\n", voiture->timeS1);
    printf("%f\n", voiture->timeS2);
    printf("%f\n", voiture->timeS3);
    return 0;
}