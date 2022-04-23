#pragma once

#include "constants.h"


struct Cell
{
    double colorHue;
    unsigned char colorSaturation;
    unsigned char colorLightness;
    int power;

    void randomize(int tick);
    Cell makeClone();
};
