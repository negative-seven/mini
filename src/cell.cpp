#include <climits>
#include <random>

#include "cell.h"
#include "random.h"


void Cell::randomize()
{
    colorHue = Random::getDouble();
    colorSaturation = 200;
    colorLightness = Random::get(96, 144);
    regionId = Random::get(INT_MIN, INT_MAX);

    int r = Random::get(1000);
    power = 1000000.0 / (r * r);
};

Cell Cell::makeClone()
{
    power *= 0.96;

    Cell newCell;
    newCell.colorHue = fmod(colorHue + Random::getDouble(-0.005, 0.005) + 1, 1);
    newCell.colorSaturation = colorSaturation;
    newCell.colorLightness = colorLightness;
    newCell.power = power;
    newCell.regionId = regionId;

    return newCell;
}
