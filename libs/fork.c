//
// Created by Cyril Grandjean on 06-12-20.
//

#include "fork.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <float.h>
#include "randomTime.h"
#include "auto.h"
#include "cli.h"
#include "mem.h"

void creatFork(SharedInfo shared, int index, int maxTime) {
    pid_t PID = fork();
    if (PID == 0) {//enfant
        srand48(time(NULL) + getpid());
        car voiture;
        if (!getVoitureCopy(shared, index, &voiture)) {
            exit(0);
        }
        while (voiture.totalTime< maxTime) {
            update_time(&voiture);
            if (!setVoiture(shared, index, &voiture)) {
                exit(0);
            }
            sleep(1);
        }
        voiture.finish = 1;
        if (!setVoiture(shared, index, &voiture)) {
            exit(0);
        }

        exit(0);
    }
}