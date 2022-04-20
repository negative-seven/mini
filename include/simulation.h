#pragma once

#include <stdbool.h>
#include <windows.h>


struct Simulation
{
    bool (*cells)[SIMULATION_WIDTH];

public:
    void init();
    void step();
    void draw(unsigned char *data, int width, int height);
};
