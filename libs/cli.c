//
// Created by Cyril Grandjean on 03-12-20.
//
#include <stdlib.h>
#include <stdio.h>
#include "auto.h"
#include "cli.h"


void couleur(char pos){
    switch (pos) {
        case 0:
            printf("\e[38;5;207m\e[48;5;226m");
            break;
        case 1:
            printf("\e[38;5;20m\e[48;5;1m");
            break;
        case 2:
            printf("\e[38;5;45m\e[48;5;163m");
            break;
    }

}

//voiture   S1   S2   S3   tour   gap   stands
void affichage(car **tableau, int taille) {
    printf("%2s %6s %8s %8s %9s %8s %8s\n", "vehicule", "S1", "S2", "S3", "tour", "gap", "stands");
    for (int i = 0; i < taille; i++) {
        car* voiture = tableau[i];
        int numero = voiture->numero;
        printf("   %2d    ",numero);
        float S1 = voiture->timeS1;
        couleur(voiture->posS1);
        printf("%8.3f",S1);
        printf("\e[0m");
        float S2 = voiture->timeS2;
        couleur(voiture->posS2);
        printf(" %8.3f",S2);
        printf("\e[0m");
        float S3 = voiture->timeS3;
        couleur(voiture->posS3);
        printf(" %8.3f",S3);
        printf("\e[0m");
        float bestTourTime = voiture->bestTourTime;
        printf(" %9.3f",bestTourTime);
        float gap = voiture->gap;
        printf(" %+8.3f\e[0m\n",gap);
    }
    couleur(0);
    printf("1er   ");
    printf("\e[0m");
    couleur(1);
    printf("2ème   ");
    printf("\e[0m");
    couleur(2);
    printf("3ème");
    printf("\e[0m\n");
}

