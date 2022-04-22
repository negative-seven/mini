#pragma once

#include "constants.h"


struct Cell
{
    unsigned char colorRed;
    unsigned char colorGreen;
    unsigned char colorBlue;
    int power;

    void randomize(int tick);
    Cell makeClone();
};
