//
// Created by Cyril Grandjean on 10-12-20.
//
#pragma once
typedef struct shareInfo{
    int shmid;
    int shm_key;
    int sem_key;
    int semid;
    int size;
} SharedInfo;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

car *getAllVoitures(SharedInfo shared);
int memShare(SharedInfo *shared);
int detVoiture(car *ptr, int index);
int delAllVoiture(SharedInfo *shared);
int getSemaphore(int index, SharedInfo shared);
int freeSemaphore(int index, SharedInfo shared);
int getVoitureCopy(SharedInfo shared, int index, car* pipe);
int getAllVoitureCopy(SharedInfo shared, car* pipe);
int setVoiture(SharedInfo shared, int index, car* pipe);

