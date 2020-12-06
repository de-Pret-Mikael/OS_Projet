//
// Created by Cyril Grandjean on 03-12-20.
//
#include <stdlib.h>
#include <stdio.h>
#include "auto.h"
#include "cli.h"

//voiture   S1   S2   S3   tour   gap   stands
void affichage(car *tableau, int taille) {
    printf("%2s %6s %8s %8s %9s %8s %8s\n", "vehicule", "S1", "S2", "S3", "tour", "gap", "stands");
    for (int i = 1; i < taille; i++) {
        car* voiture = &tableau[i];
        int numero = voiture->numero;
        float S1 = voiture->timeS1;
        float S2 = voiture->timeS2;
        float S3 = voiture->timeS3;
        float bestTourTime = voiture->bestTourTime;
        float gap = voiture->gap;
        printf("   %2d    %8.3f %8.3f %8.3f %9.3f %+8.3f\n", numero, S1, S2, S3, bestTourTime, gap);
    }
}

