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

void creatFork(car *voiture) {
    pid_t PID = fork();
    if (PID == 0) {//enfant
        for (int i = 0; i < 3; i++) {
            update_time(voiture);
            sleep(1);
        }
        exit(0);
    }
}