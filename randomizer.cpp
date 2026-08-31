//
// Created by elbus on 2026-08-29.
//
#include <ctime>
#include <cstdlib>
#include "randomizer.h"

#include <iostream>

static bool isSeeded{false};

int rnd::getRandomNumber(const int min, const int max) {
    if (!isSeeded) {
        std::srand(std::time(nullptr));
        isSeeded = true;
    }
    int rnd_value = 0;
    do {
        rnd_value = std::rand() % max;
    } while (rnd_value < min);

    return rnd_value;
}
