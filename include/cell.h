#pragma once

#include "constants.h"


struct Cell
{
    double colorHue;
    unsigned char colorSaturation;
    unsigned char colorLightness;
    int power;
    int regionId;

    void randomize();
    Cell makeClone();
};
