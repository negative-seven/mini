#include <random>

#include "cell.h"
#include "random.h"


void Cell::randomize(int tick)
{
    colorHue = Random::get(256);
    colorSaturation = 200;
    colorLightness = Random::get(96, 144);

    int r = Random::get(1000);
    power = 1000000.0 / (r * r);
};

Cell Cell::makeClone()
{
    power *= 0.96;

    Cell newCell;
    newCell.colorHue = colorHue;
    newCell.colorSaturation = colorSaturation;
    newCell.colorLightness = colorLightness;
    newCell.power = power;

    double r = Random::getDouble();
    if (r < 0.2)
    {
        newCell.colorHue += Random::get(2) ? 1 : -1;
    }

    return newCell;
}
