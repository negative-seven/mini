#include <random>

#include "cell.h"
#include "random.h"


void Cell::randomize(int diceSum)
{
    colorRed = Random::get(256);
    colorGreen = Random::get(256);
    colorBlue = Random::get(256);

    int sum = diceSum;
    for (int i = 0; i < DICE_FACES_COUNT - 1; i++)
    {
        int value = Random::get(sum + 1);
        dice[i] = value;
        sum -= value;
    }
    dice[DICE_FACES_COUNT - 1] = sum;
};

Cell Cell::copy()
{
    Cell newCell;
    newCell.colorRed = colorRed;
    newCell.colorGreen = colorGreen;
    newCell.colorBlue = colorBlue;
    for (int i = 0; i < DICE_FACES_COUNT; i++)
    {
        newCell.dice[i] = dice[i];
    }
    
    return newCell;
}
