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
    for (int i = 0; i < 100; i++)
    {
        int x = Random::get(SIMULATION_WIDTH);
        int y = Random::get(SIMULATION_HEIGHT);
        cells[y][x].randomize(iterationCount);
    }

    for (int i = 0; i < 100000; i++)
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

        int power0 = cells[y0][x0].power;
        int power1 = cells[y1][x1].power;

        if (power0 > power1)
        {
            cells[y1][x1] = cells[y0][x0].makeClone();
        }
        else if (power1 > power0)
        {
            cells[y0][x0] = cells[y1][x1].makeClone();
        }
    }

    iterationCount++;
}

void Simulation::draw(unsigned char *data)
{
    int rowDataSize = SIMULATION_WIDTH * 3;
    rowDataSize += (-rowDataSize + 4) % 4;

    for (int y = 0; y < SIMULATION_HEIGHT; y++)
    {
        for (int x = 0; x < SIMULATION_WIDTH; x++)
        {
            int index = y * rowDataSize + x * 3;
            Cell &cell = cells[y][x];

            double h = cell.colorHue;
            double s = (double)cell.colorSaturation / 255;
            double l = (double)cell.colorLightness / 255;
            double c = (1 - abs(l * 2 - 1)) * s;
            double y = c * (1 - abs(fmod(h * 6, 2) - 1));
            double m = l - c / 2;
            double r, g, b;
            if (h < 1.0/6)
            {
                r = c + m;
                g = y + m;
                b = m;
            }
            else if (h < 2.0/6)
            {
                r = y + m;
                g = c + m;
                b = m;
            }
            else if (h < 3.0/6)
            {
                r = m;
                g = c + m;
                b = y + m;
            }
            else if (h < 4.0/6)
            {
                r = m;
                g = y + m;
                b = c + m;
            }
            else if (h < 5.0/6)
            {
                r = y + m;
                g = m;
                b = c + m;
            }
            else
            {
                r = c + m;
                g = m;
                b = y + m;
            }

            data[index + 0] = r * 255;
            data[index + 1] = g * 255;
            data[index + 2] = b * 255;
        }
    }
}
