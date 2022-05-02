#pragma once

#include <random>
#include <stdbool.h>
#include <windows.h>

#include "cell.h"
#include "counter.h"


struct Simulation
{
    Cell (*cells)[SIMULATION_WIDTH];
    int iterationCount;
    bool drawBorders;
    Counter *regionSizes;

    void init();
    void step();
    void draw(unsigned char *data);
};
