//
// Created by patris on 26/11/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int NBR_CAR = 20;
const int ID_CAR[20] = {
        44, 77, 16, 5, 33, 23, 55, 4, 3, 31, 10, 26, 11, 18, 7, 99, 20, 8, 63, 6};
const char SECTEUR[3][2] = {"S1", "S2", "S3"};

typedef struct voiture car;
struct voiture {
    int id;//= 0;
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
        car obj = {ID_CAR[i], 0, 0, 0, 0, 0, 0, 0, 0, 0};
        tableauVoiture[i] = obj;
    }
}

void lap(int id) {
    car voitureSelected;
    for(int i = 0; i < NBR_CAR;i++){
        car obj = tableauVoiture[i];
        if (obj.id == id){
            voitureSelected = obj;
            break;
        }
    }
    printf("%d\n", voitureSelected.id);

}

int main(int argc, char **argv) {
    init();
    lap(16);
}