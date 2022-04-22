#include <random>

#include "cell.h"
#include "random.h"


void Cell::randomize(int tick)
{
    colorRed = Random::get(256);
    colorGreen = Random::get(256);
    colorBlue = Random::get(256);

    int r = Random::get(1000);
    power = 1000000.0 / (r * r);
};

Cell Cell::makeClone()
{
    power *= 0.99;

    Cell newCell;
    newCell.colorRed = colorRed;
    newCell.colorGreen = colorGreen;
    newCell.colorBlue = colorBlue;
    newCell.power = power;

    return newCell;
}
