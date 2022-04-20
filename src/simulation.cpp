#include "simulation.h"


void Simulation::init()
{
    cells = (bool (*)[SIMULATION_WIDTH])malloc(sizeof(bool) * SIMULATION_WIDTH * SIMULATION_HEIGHT);

    for (int i = 0; i < SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < SIMULATION_HEIGHT; j++)
        {
            cells[i][j] = (723436127 % (i * SIMULATION_WIDTH + j + 1)) % 3 == 0;
        }
    }
}

void Simulation::step()
{
    bool (*new_cells)[SIMULATION_WIDTH] = (bool (*)[SIMULATION_WIDTH])malloc(sizeof(bool) * SIMULATION_WIDTH * SIMULATION_HEIGHT);

    for (int i = 0; i < SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < SIMULATION_HEIGHT; j++)
        {
            new_cells[i][j] = 0;
        }
    }

    for (int i = 1; i < SIMULATION_WIDTH - 1; i++)
    {
        for (int j = 1; j < SIMULATION_HEIGHT - 1; j++)
        {
            int count = 0;
            count += cells[i - 1][j - 1];
            count += cells[i - 1][j];
            count += cells[i - 1][j + 1];
            count += cells[i][j - 1];
            count += cells[i][j + 1];
            count += cells[i + 1][j - 1];
            count += cells[i + 1][j];
            count += cells[i + 1][j + 1];

            bool state = cells[i][j];
            new_cells[i][j] = (state && (count == 2)) || (count == 3);
        }
    }

    for (int i = 0; i < SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < SIMULATION_HEIGHT; j++)
        {
            cells[i][j] = new_cells[i][j];
        }
    }

    free(new_cells);
}

void Simulation::draw(unsigned char *data, int width, int height)
{
    int rowDataSize = width * 3;
    rowDataSize += 4 - (rowDataSize % 4);

    for (int y = 0; y < SIMULATION_HEIGHT; y++)
    {
        for (int x = 0; x < SIMULATION_WIDTH; x++)
        {
            int index = y * rowDataSize + x * 3;

            if (cells[y][x])
            {
                data[index + 0] = 0;
                data[index + 1] = 0;
                data[index + 2] = 255;
            }
            else
            {
                data[index + 0] = 255;
                data[index + 1] = 255;
                data[index + 2] = 255;
            }
        }
    }
}
