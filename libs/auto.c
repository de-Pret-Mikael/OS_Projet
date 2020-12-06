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


void tri_tour_temps(car **tableTri, car *table) {
    for (int i = 0; i < NBR_CAR; i++) {
        tableTri[i] = &table[i];
    }
    for (int i = 0; i < NBR_CAR; i++) {
        for (int j = 0; j < NBR_CAR; j++) {
            if (tableTri[j]->bestTourTime > tableTri[i]->bestTourTime) {
                car *emplacement_temporaire = tableTri[i];
                tableTri[i] = tableTri[j];
                tableTri[j] = emplacement_temporaire;
            }
        }
    }
}

void tri_S1(car *table) {
    car *tableTri[NBR_CAR];
    for (int i = 0; i < NBR_CAR; i++) {
        tableTri[i] = &table[i];
    }
    for (int i = 0; i < NBR_CAR; i++) {
        for (int j = 0; j < NBR_CAR; j++) {
            if (tableTri[j]->timeS1 > tableTri[i]->timeS1) {
                car *emplacement_temporaire = tableTri[i];
                tableTri[i] = tableTri[j];
                tableTri[j] = emplacement_temporaire;
            }
        }
    }
    for (int i = 0; i < NBR_CAR; i++) {
        tableTri[i]->posS1 = i;
    }
}

void tri_S2(car *table) {
    car *tableTri[NBR_CAR];
    for (int i = 0; i < NBR_CAR; i++) {
        tableTri[i] = &table[i];
    }
    for (int i = 0; i < NBR_CAR; i++) {
        for (int j = 0; j < NBR_CAR; j++) {
            if (tableTri[j]->timeS2 > tableTri[i]->timeS2) {
                car *emplacement_temporaire = tableTri[i];
                tableTri[i] = tableTri[j];
                tableTri[j] = emplacement_temporaire;
            }
        }
    }
    for (int i = 0; i < NBR_CAR; i++) {
        tableTri[i]->posS2 = i;
    }
}

void tri_S3(car *table) {
    car *tableTri[NBR_CAR];
    for (int i = 0; i < NBR_CAR; i++) {
        tableTri[i] = &table[i];
    }
    for (int i = 0; i < NBR_CAR; i++) {
        for (int j = 0; j < NBR_CAR; j++) {
            if (tableTri[j]->timeS3 > tableTri[i]->timeS3) {
                car *emplacement_temporaire = tableTri[i];
                tableTri[i] = tableTri[j];
                tableTri[j] = emplacement_temporaire;
            }
        }
    }
    for (int i = 0; i < NBR_CAR; i++) {
        tableTri[i]->posS3 = i;
    }
}

void diff_tot_time(car **tableauVoiture) {
    float gap;
    for (int i = 0; i < NBR_CAR; i++) {
        if (i != 0) {
            gap = tableauVoiture[i]->bestTourTime - tableauVoiture[i - 1]->bestTourTime;
            tableauVoiture[i]->gap = gap;
        } else {
            tableauVoiture[i]->gap = 0.0;
        }
    }
}


int main(int argc, char **argv) {
    car tableauVoiture[NBR_CAR];
    car *tableauVoitureTri[NBR_CAR];
    init(tableauVoiture);
    printf("Meilleur temps S1\n");
    srand48(time(NULL));
    for (int i = 0; i < 3; i++) {
        for (int i = 0; i < NBR_CAR; i++) {
            car *voiture = &tableauVoiture[i];
            update_time(voiture);
        }
        tri_S1(tableauVoiture);
        tri_S2(tableauVoiture);
        tri_S3(tableauVoiture);
        tri_tour_temps(tableauVoitureTri, tableauVoiture);
        diff_tot_time(tableauVoitureTri);
        affichage(tableauVoitureTri, NBR_CAR);
        sleep(1);
    }
    return 0;
}