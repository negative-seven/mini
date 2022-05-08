#include <stdio.h>

#include "constants.h"
#include "random.h"
#include "simulation.h"


void Simulation::init()
{
    cells = (Cell (*)[MAX_SIMULATION_WIDTH])malloc(sizeof(Cell) * MAX_SIMULATION_WIDTH * MAX_SIMULATION_WIDTH);
    for (int i = 0; i < MAX_SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < MAX_SIMULATION_HEIGHT; j++)
        {
            Cell cell;
            cell.randomize();

            cells[j][i] = cell;
        }
    }

    iterationCount = 0;
    drawBorders = true;

    regionSizes = (Counter *)malloc(sizeof(Counter));
    *regionSizes = Counter(1000000);
}

void Simulation::step(double scaleFactor)
{
    int simulationWidth = WINDOW_WIDTH / scaleFactor;
    int simulationHeight = WINDOW_HEIGHT / scaleFactor;

    for (int i = 0; i < 1200 / (scaleFactor * scaleFactor); i++)
    {
        int x = Random::get(simulationWidth);
        int y = Random::get(simulationHeight);
        cells[y][x].randomize();
        regionSizes->increment(cells[y][x].regionId);
    }

    for (int i = 0; i < 1200000 / (scaleFactor * scaleFactor); i++)
    {
        int x0 = Random::get(1, simulationWidth - 1);
        int y0 = Random::get(1, simulationHeight - 1);
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
            regionSizes->increment(cells[y0][x0].regionId);
            regionSizes->decrement(cells[y1][x1].regionId);
            cells[y1][x1] = cells[y0][x0].makeClone();
        }
        else if (power1 > power0)
        {
            regionSizes->decrement(cells[y0][x0].regionId);
            regionSizes->increment(cells[y1][x1].regionId);
            cells[y0][x0] = cells[y1][x1].makeClone();
        }
    }

    iterationCount++;
}

void Simulation::draw(double scaleFactor, unsigned char *data)
{
    int simulationWidth = WINDOW_WIDTH / scaleFactor;
    int simulationHeight = WINDOW_HEIGHT / scaleFactor;

    int rowDataSize = MAX_SIMULATION_WIDTH * 3;
    rowDataSize += ((rowDataSize % 4) + 4) % 4;

    for (int y = 0; y < simulationHeight; y++)
    {
        for (int x = 0; x < simulationWidth; x++)
        {
            int index = y * rowDataSize + x * 3;
            Cell &cell = cells[y][x];

            bool isBorder =
                drawBorders
                && x > 0
                && y > 0
                && x < simulationWidth - 1
                && y < simulationHeight - 1
                && (
                    cell.regionId > cells[y][x - 1].regionId
                    || cell.regionId > cells[y][x + 1].regionId
                    || cell.regionId > cells[y - 1][x].regionId
                    || cell.regionId > cells[y + 1][x].regionId
                )
                && regionSizes->getCount(cell.regionId) > 5
                && regionSizes->getCount(cells[y][x - 1].regionId) > 5
                && regionSizes->getCount(cells[y][x + 1].regionId) > 5
                && regionSizes->getCount(cells[y - 1][x].regionId) > 5
                && regionSizes->getCount(cells[y + 1][x].regionId) > 5
            ;

            if (isBorder)
            {
                data[index + 0] = 0;
                data[index + 1] = 0;
                data[index + 2] = 0;
            }
            else
            {
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
}
