#pragma once

#include <stdbool.h>
#include <windows.h>
#include <random>

#include "cell.h"


struct Simulation
{
    Cell (*cells)[SIMULATION_WIDTH];
    int iterationCount;

    void init();
    void step();
    void draw(unsigned char *data);
};
