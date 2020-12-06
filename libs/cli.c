//
// Created by Cyril Grandjean on 03-12-20.
//
#include <stdlib.h>
#include <stdio.h>
#include "auto.h"
#include "cli.h"

//voiture   S1   S2   S3   tour   gap   stands
void affichage(car **tableau, int taille) {
    printf("%2s %6s %8s %8s %9s %8s %8s\n", "vehicule", "S1", "S2", "S3", "tour", "gap", "stands");
    for (int i = 0; i < taille; i++) {
        car* voiture = tableau[i];
        int numero = voiture->numero;
        printf("   %2d    ",numero);
        float S1 = voiture->timeS1;
        printf("%8.3f",S1);
        float S2 = voiture->timeS2;
        printf(" %8.3f",S2);
        float S3 = voiture->timeS3;
        printf(" %8.3f",S3);
        float bestTourTime = voiture->bestTourTime;
        printf(" %9.3f",bestTourTime);
        float gap = voiture->gap;
        printf(" %+8.3f\n",gap);
    }
}

