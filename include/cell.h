#pragma once

#include "constants.h"


struct Cell
{
    unsigned char colorHue;
    unsigned char colorSaturation;
    unsigned char colorLightness;
    int power;

    void randomize(int tick);
    Cell makeClone();
};
