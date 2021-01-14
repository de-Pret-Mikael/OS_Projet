//
// Created by patris on 26/11/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include <wait.h>
#include "randomTime.h"
#include "auto.h"
#include "cli.h"
#include "fork.h"
#include "mem.h"

int NBR_CAR = 20;
int ID_CAR[20] = {
        44, 77, 16, 5, 33, 23, 55, 4, 3, 31, 10, 26, 11, 18, 7, 99, 20, 8, 63, 6};


void update_time(car *voiture) {
    if (!voiture->out) {
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
        double stand = randomRange(0, 100);
        if (stand < 5) {
            voiture->stand = 10;
            voiture->totalTime += 10;
        }
        double out = randomRange(0, 100);
        if (out < 2) {
            voiture->out = 1;
        }
    }
}


void tri_tour_temps(car *tableTri, car *table, int nbrCar) {
    for (int i = 0; i < nbrCar; i++) {
        int index = tableTri[i].index;
        tableTri[i] = table[index];
    }
    for (int i = 0; i < nbrCar; i++) {
        for (int j = 0; j < nbrCar; j++) {
            if (tableTri[j].bestTourTime > tableTri[i].bestTourTime) {
                car emplacement_temporaire = tableTri[i];
                tableTri[i] = tableTri[j];
                tableTri[j] = emplacement_temporaire;
            }
        }
    }
}

void tri_S1(car *table, car *tableTriAll, int nbrCar) {
    car *tableTri[NBR_CAR];
    for (int i = 0; i < NBR_CAR; i++) {
        int index = tableTriAll[i].index;
        tableTri[i] = &table[index];
    }
    for (int i = 0; i < nbrCar; i++) {
        for (int j = 0; j < nbrCar; j++) {
            if (!tableTri[i]->out) {
                if (tableTri[j]->timeS1 > tableTri[i]->timeS1) {
                    car *emplacement_temporaire = tableTri[i];
                    tableTri[i] = tableTri[j];
                    tableTri[j] = emplacement_temporaire;
                }
            }
        }
    }
    for (int i = 0; i < nbrCar; i++) {
        tableTri[i]->posS1 = i;
    }
}

void tri_S2(car *table, car *tableTriAll, int nbrCar) {
    car *tableTri[NBR_CAR];
    for (int i = 0; i < NBR_CAR; i++) {
        int index = tableTriAll[i].index;
        tableTri[i] = &table[index];
    }
    for (int i = 0; i < nbrCar; i++) {
        for (int j = 0; j < nbrCar; j++) {
            if (!tableTri[i]->out) {
                if (tableTri[j]->timeS2 > tableTri[i]->timeS2) {
                    car *emplacement_temporaire = tableTri[i];
                    tableTri[i] = tableTri[j];
                    tableTri[j] = emplacement_temporaire;
                }
            }
        }
    }
    for (int i = 0; i < nbrCar; i++) {
        tableTri[i]->posS2 = i;
    }
}

void tri_S3(car *table, car *tableTriAll, int nbrCar) {
    car *tableTri[NBR_CAR];
    for (int i = 0; i < NBR_CAR; i++) {
        int index = tableTriAll[i].index;
        tableTri[i] = &table[index];
    }
    for (int i = 0; i < nbrCar; i++) {
        for (int j = 0; j < nbrCar; j++) {
            if (!tableTri[i]->out){
                if (tableTri[j]->timeS3 > tableTri[i]->timeS3) {
                    car *emplacement_temporaire = tableTri[i];
                    tableTri[i] = tableTri[j];
                    tableTri[j] = emplacement_temporaire;
                }
            }
        }
    }
    for (int i = 0; i < nbrCar; i++) {
        tableTri[i]->posS3 = i;
    }
}

void tri_temps_tour(car *table, car *tableTriAll, int nbrCar) {
    car *tableTri[NBR_CAR];
    for (int i = 0; i < NBR_CAR; i++) {
        int index = tableTriAll[i].index;
        tableTri[i] = &table[index];
    }
    for (int i = 0; i < nbrCar; i++) {
        for (int j = 0; j < nbrCar; j++) {
            if (!tableTri[i]->out) {
                if (tableTri[j]->tourTime > tableTri[i]->tourTime) {
                    car *emplacement_temporaire = tableTri[i];
                    tableTri[i] = tableTri[j];
                    tableTri[j] = emplacement_temporaire;
                }
            }
        }
    }
    for (int i = 0; i < nbrCar; i++) {
        tableTri[i]->posTour = i;
    }
}

void tri_final(car *tableTri, car *table, int nbrCar) {
    for (int i = 0; i < nbrCar; i++) {
        int index = tableTri[i].index;
        tableTri[i] = table[index];
    }
    for (int i = 0; i < nbrCar; i++) {
        for (int j = 0; j < nbrCar; j++) {
            if (tableTri[j].nbrTour < tableTri[i].nbrTour) {
                if (tableTri[j].totalTime < tableTri[i].totalTime) {
                    car emplacement_temporaire = tableTri[i];
                    tableTri[i] = tableTri[j];
                    tableTri[j] = emplacement_temporaire;
                }
            } else if (tableTri[j].nbrTour == tableTri[i].nbrTour) {
                if (tableTri[j].totalTime > tableTri[i].totalTime) {
                    car emplacement_temporaire = tableTri[i];
                    tableTri[i] = tableTri[j];
                    tableTri[j] = emplacement_temporaire;
                }
            }

        }
    }
}

void diff_best_time(car *tableauVoiture) {
    float gap;
    for (int i = 0; i < NBR_CAR; i++) {
        if (i != 0) {
            gap = tableauVoiture[i].bestTourTime - tableauVoiture[i - 1].bestTourTime;
            tableauVoiture[i].gap = gap;
        } else {
            tableauVoiture[i].gap = 0.0;
        }
    }
}

void diff_total_time(car *tableauVoiture) {
    float gap;
    for (int i = 0; i < NBR_CAR; i++) {
        if (i != 0) {
            gap = tableauVoiture[i].totalTime - tableauVoiture[i - 1].totalTime;
            tableauVoiture[i].gap = gap;
        } else {
            tableauVoiture[i].gap = 0.0;
        }
    }
}

int initVoiture(SharedInfo shared) {
    car *voiture = getAllVoitures(shared);
    if (!voiture) {
        return 0;
    }

    for (int i = 0; i < NBR_CAR; i++) {
        voiture[i].numero = ID_CAR[i];
        voiture[i].index = i;
        voiture[i].bestTimeS1 = FLT_MAX;
        voiture[i].bestTimeS2 = FLT_MAX;
        voiture[i].bestTimeS3 = FLT_MAX;
        voiture[i].bestTourTime = FLT_MAX;
        voiture[i].totalTime = 0;
        voiture[i].finish = 0;
        voiture[i].stand = 0;
        voiture[i].out = 0;
        voiture[i].nbrTour = 0;
    }
    if (!detVoiture(voiture, 0)) {
        return 0;
    }
    return 1;
}

int resetVoiture(SharedInfo shared, int nbrCar, car *tableTri) {
    car *voiture = getAllVoitures(shared);
    if (!voiture) {
        return 0;
    }

    for (int i = 0; i < nbrCar; i++) {
        int index = tableTri[i].index;
        voiture[index].bestTimeS1 = FLT_MAX;
        voiture[index].bestTimeS2 = FLT_MAX;
        voiture[index].bestTimeS3 = FLT_MAX;
        voiture[index].bestTourTime = FLT_MAX;
        voiture[index].totalTime = 0;
        voiture[index].nbrTour = 0;
        voiture[index].finish = 0;
        voiture[index].out = 0;
        voiture[index].stand = 0;
    }
    if (!detVoiture(voiture, 0)) {
        return 0;
    }
    return 1;
}

int forkFini(car *voiture) {
    for (int i = 0; i < NBR_CAR; i++) {
        if (!voiture[i].finish) {
            return 0;
        }
    }
    return 1;
}


int lancerEssai(SharedInfo shared, car *tableTri, int nbrCar, int maxTime, char *title) {
    if (!resetVoiture(shared, nbrCar, tableTri)) {
        return -1;
    }
    for (int i = 0; i < nbrCar; i++) {
        creatFork(shared, tableTri[i].index, maxTime);
    }
    while (1) {
        int status;
        car tableauVoiture[NBR_CAR];
        if (!getAllVoitureCopy(shared, tableauVoiture)) {
            return 0;
        }
        tri_S1(tableauVoiture, tableTri, nbrCar);
        tri_S2(tableauVoiture, tableTri, nbrCar);
        tri_S3(tableauVoiture, tableTri, nbrCar);
        tri_tour_temps(tableTri, tableauVoiture, nbrCar);
        diff_best_time(tableTri);
        affichage(tableTri, NBR_CAR, title, nbrCar);
        if (forkFini(tableauVoiture)) {
            break;
        }
        sleep(1);
    }
    return 0;
}

int lancerFinal(SharedInfo shared, car *tableTri, int nbrCar, int maxTour, char *title) {
    if (!resetVoiture(shared, nbrCar, tableTri)) {
        return -1;
    }
    for (int i = 0; i < nbrCar; i++) {
        finaleFork(shared, tableTri[i].index, maxTour);
    }
    while (1) {
        car tableauVoiture[NBR_CAR];
        if (!getAllVoitureCopy(shared, tableauVoiture)) {
            return 0;
        }
        tri_S1(tableauVoiture, tableTri, nbrCar);
        tri_S2(tableauVoiture, tableTri, nbrCar);
        tri_S3(tableauVoiture, tableTri, nbrCar);
        tri_temps_tour(tableauVoiture, tableTri, nbrCar);
        tri_final(tableTri, tableauVoiture, nbrCar);
        diff_total_time(tableTri);
        affichage_final(tableTri, NBR_CAR, title, nbrCar);
        if (forkFini(tableauVoiture)) {
            break;
        }
        sleep(1);
    }
    return 0;
}


int main(int argc, char **argv) {
    SharedInfo shared;
    car tableVoitureTri[NBR_CAR];
    if (!memShare(&shared)) {
        return -1;
    }
    if (!initVoiture(shared)) {
        return -1;
    }
    if (!getAllVoitureCopy(shared, tableVoitureTri)) {
        return 0;
    }
    lancerEssai(shared, tableVoitureTri, NBR_CAR, 360, "P1");
    lancerEssai(shared, tableVoitureTri, NBR_CAR, 360, "P2");
    lancerEssai(shared, tableVoitureTri, NBR_CAR, 360, "P3");
    lancerEssai(shared, tableVoitureTri, NBR_CAR, 360, "Q1");
    lancerEssai(shared, tableVoitureTri, 15, 360, "Q2");
    lancerEssai(shared, tableVoitureTri, 10, 360, "Q3");
    lancerFinal(shared, tableVoitureTri, 10, 20, "FINAL");
    delAllVoiture(&shared);
}