//
// Created by patris on 26/11/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include "randomTime.h"
#include "auto.h"



void init() {
    for (int i = 0; i < NBR_CAR; i++) {
        tableauVoiture[i].numero = ID_CAR[i];
        tableauVoiture[i].bestTimeS1 = FLT_MAX;
        tableauVoiture[i].bestTimeS2 = FLT_MAX;
        tableauVoiture[i].bestTimeS3 = FLT_MAX;
        tableauVoiture[i].bestTourTime = FLT_MAX;
        tableauVoiture[i].totalTime = 0;
    }
}

car *select_car(int id) {
    car *obj;
    for (int i = 0; i < NBR_CAR; i++) {
        obj = &tableauVoiture[i];
        if (obj->numero == id) {
            return obj;
        }
    }
    return NULL;
}


int update_time(int id) {
    int min = 25;
    int max = 45;
    car *voiture = select_car(id);
    voiture->timeS1 = randomRange(min, max);
    if (voiture->timeS1 < voiture->bestTimeS1) {
        voiture->bestTimeS1 = voiture->timeS1;
    }
    voiture->timeS2 = randomRange(min, max);
    if (voiture->timeS2 < voiture->bestTimeS2) {
        voiture->bestTimeS2 = voiture->timeS2;
    }
    voiture->timeS3 = randomRange(min, max);
    if (voiture->timeS3 < voiture->bestTimeS3) {
        voiture->bestTimeS3 = voiture->timeS3;
    }
    voiture->tourTime = voiture->timeS1 + voiture->timeS2 + voiture->timeS3;
    if (voiture->tourTime < voiture->bestTourTime) {
        voiture->bestTourTime = voiture->tourTime;
    }
    voiture->totalTime += voiture->tourTime;
}

int main(int argc, char **argv) {
    srand48(time(NULL));
    init();
    car *voiture = select_car(16);
    for (int i = 0; i < 5; i++) {
        update_time(16);
        printf("%07.3f\n", voiture->timeS1);
        printf("%07.3f\n", voiture->timeS2);
        printf("%07.3f\n", voiture->timeS3);
        printf("%07.3f\n\n", voiture->bestTourTime);
    }
    return 0;
}