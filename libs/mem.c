//
// Created by Cyril Grandjean on 10-12-20.
//
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include "auto.h"
#include "mem.h"

car *getAllVoitures(SharedInfo shared){
    car* voiture = (car *) shmat(shared.shmid, NULL, 0);
    if (voiture == (void * ) -1){
        perror("Shared memory attach");
        return NULL;
    }
    return voiture;
}

int memShare(SharedInfo *shared){
    key_t shm_key = 69;
    key_t sem_key = 96;
    int nbrVoiture = 20;
    size_t size = sizeof(car) * nbrVoiture;
    union semun u;
    u.val = 1;


    int shmid = shmget(shm_key, size, 0777 | IPC_CREAT);
    if (shmid == -1){
        perror("shared memory");
        return 0;
    }

    int semid = semget(sem_key, nbrVoiture + 1, 0777 | IPC_CREAT);
    if (semid ==-1){
        perror("semaphore");
        return 0;
    }

    for (int i = 0;i < nbrVoiture; i++){
        if((semctl(semid, i, SETVAL, u)) == -1){
            perror("Semaphore set value");
            return 0;
        }
    }

    shared->shmid  = shmid;
    shared->shm_key  = shm_key;
    shared->size  = nbrVoiture;
    shared->semid  = semid;
    shared->sem_key  = sem_key;
    return 1;
}

int detVoiture(car *ptr, int index){
    if (shmdt(ptr - index) == -1){
        perror("Shared memory detach");
        return 0;
    }
    return 1;
}

int delAllVoiture(SharedInfo *shared){
    if ((shmctl(shared->shmid, IPC_RMID, 0)) == -1){
        perror("Shared memory destroy");
    }
    if ((semctl(shared->semid, 0 , IPC_RMID)) == -1){
        perror("Semaphore destroy");
        return 0;
    }
    return 1;
}

int getSemaphore(int index, SharedInfo shared){
    struct sembuf buf = {index, -1, SEM_UNDO};
    if (semop(shared.semid, &buf, 1) < 0){
        perror("Semaphore set -1");
        return 0;
    }
    return 1;
}

int freeSemaphore(int index, SharedInfo shared){
    struct sembuf buf = {index, +1, SEM_UNDO};
    if (semop(shared.semid, &buf, 1) < 0){
        perror("Semaphore set -1");
        return 0;
    }
    return 1;
}

int getVoitureCopy(SharedInfo shared, int index, car* pipe){
    car *voiture = getAllVoitures(shared);
    if (!voiture) {
        return 0;
    }
    if(!getSemaphore(index, shared)){
        return 0;
    }
    *pipe = voiture[index];
    if(!freeSemaphore(index, shared)){
        return 0;
    }
    if(!detVoiture(voiture, 0)){
        return 0;
    }
    return 1;
}

int getAllVoitureCopy(SharedInfo shared, car* pipe){
    for ( int i =0; i < shared.size; i++){
        if(!getVoitureCopy(shared, i, &(pipe[i]))){
            return 0;
        }
    }
    return 1;
}

int setVoiture(SharedInfo shared, int index, car* pipe){
    car *voiture = getAllVoitures(shared);
    if (!voiture) {
        return 0;
    }
    if(!getSemaphore(index, shared)){
        return 0;
    }
    voiture[index] = *pipe;
    if(!freeSemaphore(index, shared)){
        return 0;
    }
    if(!detVoiture(voiture, 0)){
        return 0;
    }
    return 1;
}