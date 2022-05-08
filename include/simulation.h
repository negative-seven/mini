#pragma once

#include <random>
#include <stdbool.h>
#include <windows.h>

#include "cell.h"
#include "counter.h"


struct Simulation
{
    Cell (*cells)[MAX_SIMULATION_WIDTH];
    int iterationCount;
    bool drawBorders;
    Counter *regionSizes;

    void init();
    void step(double scaleFactor);
    void draw(double scaleFactor, unsigned char *data);
};
