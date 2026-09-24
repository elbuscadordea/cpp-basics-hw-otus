//
// Created by elbus on 2026-09-21.
//

#pragma once
#include "Ball.hpp"
#include "Dust.h"

#include <vector>

class Duster {
private:
    std::pmr::vector<Dust> dusts;

public:
    Duster() = default;

    void addDustsOnCollision(const Ball& ballA, const Ball& ballB);
    void processTick();
};

