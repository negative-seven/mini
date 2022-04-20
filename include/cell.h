#pragma once

#include "constants.h"


struct Cell
{
    unsigned char colorRed;
    unsigned char colorGreen;
    unsigned char colorBlue;
    int dice[DICE_FACES_COUNT];

    void randomize(int diceSum);
    Cell copy();
};
