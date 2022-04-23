#include "random.h"


std::mt19937 *Random::_rng;

void Random::init()
{
    _rng = (std::mt19937 *)malloc(sizeof(std::mt19937));
    *_rng = std::mt19937(4);
}

int Random::get(int max)
{
    return (*_rng)() % max;
}

int Random::get(int min, int max)
{
    return min + ((*_rng)() % (max - min));
}

double Random::getDouble(double max)
{
    return ((double)(*_rng)() / _rng->max()) * max;
}

double Random::getDouble(double min, double max)
{
    return min + ((double)(*_rng)() / _rng->max()) * (max - min);
}