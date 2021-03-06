//
// Created by Cyril Grandjean on 03-12-20.
//
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "auto.h"
#include "cli.h"



void couleur(char pos) {
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

void descr_couleur() {
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

void printPerso(char* format, float nbr){
    if (nbr == FLT_MAX){
        printf("%s","     --- ");
    }else{
        printf(format, nbr);
    }
}

//voiture   S1   S2   S3   tour   gap   stands
void affichage(car *tableau, int taille, char *title, int nbrCar) {
    system("clear");
    printf("%s\n\n", title);
    printf("%2s %6s %8s %8s %9s %8s %8s\n", "vehicule", "S1", "S2", "S3", "tour", "gap", "stands");
    for (int i = 0; i < taille; i++) {
        int actif = (i<nbrCar);
        car *voiture = &tableau[i];
        if (!actif || voiture->out){
            printf("\e[38;5;0m\e[48;5;254m");
            printf("   %2d   ", voiture->numero);
            printf(" %8.3f", voiture->timeS1);
            printf(" %8.3f", voiture->timeS2);
            printf(" %8.3f", voiture->timeS3);
            printf(" %9.3f", voiture->bestTourTime);
            printf(" %s", "   ---  ");
            printf(" %s\e[0m\n", "   ---  ");
            continue;
        }else {
            int numero = voiture->numero;
            printf("   %2d   ", numero);

            float S1 = voiture->timeS1;
            couleur(voiture->posS1);
            printPerso(" %8.3f", S1);
            printf("\e[0m");

            float S2 = voiture->timeS2;
            couleur(voiture->posS2);
            printPerso(" %8.3f", S2);
            printf("\e[0m");

            float S3 = voiture->timeS3;
            couleur(voiture->posS3);
            printPerso(" %8.3f", S3);
            printf("\e[0m");

            float bestTourTime = voiture->bestTourTime;
            printPerso(" %9.3f", bestTourTime);

            float gap = voiture->gap;
            printPerso(" %+8.3f\e[0m", gap);

            if (voiture->stand) {
                printf("     %d", voiture->stand);
            } else {
                printf(" %s", "   ---  ");
            }

            printf("\n");
        }
    }
    descr_couleur();
}




void aff_voiture_final(car *voiture){
    //voiture   S1   S2   S3   TOUR TOURS TEMPS GAP STAND
    int numero = voiture->numero;
    printf("   %2d   ", numero);

    float S1 = voiture->timeS1;
    couleur(voiture->posS1);
    printPerso(" %8.3f", S1);
    printf("\e[0m");

    float S2 = voiture->timeS2;
    couleur(voiture->posS2);
    printPerso(" %8.3f", S2);
    printf("\e[0m");

    float S3 = voiture->timeS3;
    couleur(voiture->posS3);
    printPerso(" %8.3f", S3);
    printf("\e[0m");

    float bestTourTime = voiture->bestTourTime;
    couleur(voiture->posTour);
    printPerso(" %9.3f", bestTourTime);
    printf("\e[0m");

    int nbrtour = voiture->nbrTour;
    printf("   %2d   ", nbrtour);

    float totalTime = voiture->totalTime;
    printPerso(" %8.3f", totalTime);

    float gap = voiture->gap;
    printPerso(" %+8.3f\e[0m", gap);

    if (voiture->stand) {
        printf("     %d", voiture->stand);
    } else {
        printf(" %s", "   ---  ");
    }
    printf("\n");
}

void affichage_final(car *tableau, int taille, char *title, int nbrCar) {
    system("clear");
    printf("%s\n\n", title);
    printf("%2s %6s %8s %8s %9s %8s %8s %8s %8s\n", "vehicule", "S1", "S2", "S3", "tour", "tours", "temps", "gap", "stands");
    for (int i = 0; i < taille; i++){
        car *voiture = &tableau[i];
        int actif = (i<nbrCar);
        if (!actif || voiture->out){
            printf("\e[38;5;0m\e[48;5;254m");
            printf("   %2d   ", voiture->numero);
            printf(" %8.3f", voiture->timeS1);
            printf(" %8.3f", voiture->timeS2);
            printf(" %8.3f", voiture->timeS3);
            printf(" %9.3f", voiture->bestTourTime);
            printf(" %s", "   ---  ");
            printf(" %s", "   ---  ");
            printf(" %s", "   ---  ");
            printf(" %s\e[0m\n", "   ---  ");
            continue;
        }else {
        aff_voiture_final(voiture);

        }
    }
    descr_couleur();
}