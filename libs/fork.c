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

int creatFork(SharedInfo shared, int index) {
    pid_t PID = fork();
    if (PID == 0) {//enfant
        srand48(time(NULL) + getpid());
        car voiture;
        if (!getVoitureCopy(shared, index, &voiture)) {
            return 0;
        }
        for (int i = 0; i < 3; i++) {
            update_time(&voiture);
            if (!setVoiture(shared, index, &voiture)) {
                return 0;
            }
            sleep(1);
        }

        exit(0);
    }
}