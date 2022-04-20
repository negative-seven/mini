#include <stdio.h>

#include "constants.h"
#include "random.h"
#include "simulation.h"


void Simulation::init()
{
    cells = (Cell (*)[SIMULATION_WIDTH])malloc(sizeof(Cell) * SIMULATION_WIDTH * SIMULATION_HEIGHT);
    for (int i = 0; i < SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < SIMULATION_HEIGHT; j++)
        {
            Cell cell;
            cell.randomize(0);

            cells[j][i] = cell;
        }
    }

    iterationCount = 0;
}

void Simulation::step()
{
    for (int i = 0; i < 10000; i++)
    {
        int x0 = Random::get(1, SIMULATION_WIDTH - 1);
        int y0 = Random::get(1, SIMULATION_HEIGHT - 1);
        int direction = Random::get(4);

        int x1, y1;
        switch (direction)
        {
        case 0:
            x1 = x0;
            y1 = y0 - 1;
            break;
        case 1:
            x1 = x0;
            y1 = y0 + 1;
            break;
        case 2:
            x1 = x0 - 1;
            y1 = y0;
            break;
        case 3:
            x1 = x0 + 1;
            y1 = y0;
            break;
        }

        int roll0 = cells[y0][x0].dice[Random::get(DICE_FACES_COUNT)];
        int roll1 = cells[y1][x1].dice[Random::get(DICE_FACES_COUNT)];

        if (roll0 > roll1)
        {
            cells[y1][x1] = cells[y0][x0].copy();
        }
        else if (roll1 > roll0)
        {
            cells[y0][x0] = cells[y1][x1].copy();
        }
    }

    for (int i = 0; i < 1000; i++)
    {
        int x = Random::get(SIMULATION_WIDTH);
        int y = Random::get(SIMULATION_HEIGHT);
        cells[y][x].randomize(iterationCount / 30 * 10000 + 1);
    }

    iterationCount++;
}

void Simulation::draw(unsigned char *data, int width, int height)
{
    int rowDataSize = width * 3;
    rowDataSize += (-rowDataSize + 4) % 4;

    for (int y = 0; y < SIMULATION_HEIGHT; y++)
    {
        for (int x = 0; x < SIMULATION_WIDTH; x++)
        {
            int index = y * rowDataSize + x * 3;
            Cell &cell = cells[y][x];

            data[index + 0] = cell.colorBlue;
            data[index + 1] = cell.colorGreen;
            data[index + 2] = cell.colorRed;
        }
    }
}
