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
#include "cli.h"

int NBR_CAR = 20;
int ID_CAR[20] = {
        44, 77, 16, 5, 33, 23, 55, 4, 3, 31, 10, 26, 11, 18, 7, 99, 20, 8, 63, 6};
int tour = 1;
float minTemps;
float bestTimeS1;
car typeTri;
car emplacement_temporaire;


void init(car *tableauVoiture) {
    for (int i = 0; i < NBR_CAR; i++) {
        tableauVoiture[i].numero = ID_CAR[i];
        tableauVoiture[i].bestTimeS1 = FLT_MAX;
        tableauVoiture[i].bestTimeS2 = FLT_MAX;
        tableauVoiture[i].bestTimeS3 = FLT_MAX;
        tableauVoiture[i].bestTourTime = FLT_MAX;
        tableauVoiture[i].totalTime = 0;
    }
}

void update_time(car *voiture) {
    int min = 25;
    int max = 45;
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

void tri_tour_temps(car *tableauVoiture) {
    for (int i = 0; i < NBR_CAR; i++) {
        for (int j = 0; j < NBR_CAR; j++) {
            if (tableauVoiture[j].bestTourTime > tableauVoiture[i].bestTourTime) {
                emplacement_temporaire = tableauVoiture[i];
                tableauVoiture[i] = tableauVoiture[j];
                tableauVoiture[j] = emplacement_temporaire;
            }
        }
    }
}

void diff_tot_time(car *tableauVoiture){
    float gap;
    for (int i = 0; i < NBR_CAR; i++) {
        if (i != 0) {
        gap = tableauVoiture[i].bestTourTime - tableauVoiture[i-1].bestTourTime;
        tableauVoiture[i].gap = gap;
        } else {
            tableauVoiture[i].gap = 0.0;
        }
    }
}


int main(int argc, char **argv) {
    car tableauVoiture[NBR_CAR];
    srand48(time(NULL));
    init(tableauVoiture);
    for (int i = 0; i < NBR_CAR; i++) {
        car *voiture = &tableauVoiture[i];
        update_time(voiture);
    }
//    for (int i = 0; i < NBR_CAR; i++) {
//        if (tableauVoiture[i].bestTimeS1 < minTemps){
//            minTemps = tableauVoiture[i].bestTimeS1;
//        }
//    }
//    affichage(tableauVoiture, NBR_CAR);
    printf("Meilleur temps S1\n");
    tri_tour_temps(tableauVoiture);
    diff_tot_time(tableauVoiture);
    affichage(tableauVoiture, NBR_CAR);
//    for (int i=0; i < NBR_CAR; i++) {
//        printf("%f\n", tableauVoiture[i].bestTimeS1);
//    }

//
//
//    printf("LE MAX EST LE SUIVANT : %f\n", minTemps);
//    }



    return 0;
}