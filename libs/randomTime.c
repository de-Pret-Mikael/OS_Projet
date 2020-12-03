//
// Created by Cyril Grandjean on 26-11-20.
//
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/random.h>

double randomRange(double min, double max) {
    return rand48() * (max - min) + min
}

