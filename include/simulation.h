#pragma once

#include <random>
#include <stdbool.h>
#include <windows.h>

#include "cell.h"


struct Simulation
{
    Cell (*cells)[SIMULATION_WIDTH];
    int iterationCount;
    bool drawBorders;

    void init();
    void step();
    void draw(unsigned char *data);
};
