#include "simulation.h"


void Simulation::init()
{
    cells = (bool *)malloc(sizeof(bool) * SIMULATION_WIDTH * SIMULATION_HEIGHT);

    for (int i = 0; i < SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < SIMULATION_HEIGHT; j++)
        {
            cells[i * SIMULATION_WIDTH + j] = ((723436127 % (i + 253)) % (j + 245)) % 2;
        }
    }
}

void Simulation::step()
{
    bool *new_cells = (bool *)malloc(sizeof(bool) * SIMULATION_WIDTH * SIMULATION_HEIGHT);

    for (int i = 0; i < SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < SIMULATION_HEIGHT; j++)
        {
            new_cells[i * SIMULATION_WIDTH + j] = 0;
        }
    }

    for (int i = 1; i < SIMULATION_WIDTH - 1; i++)
    {
        for (int j = 1; j < SIMULATION_HEIGHT - 1; j++)
        {
            int count = 0;
            count += cells[(i - 1) * SIMULATION_WIDTH + j - 1];
            count += cells[(i - 1) * SIMULATION_WIDTH + j];
            count += cells[(i - 1) * SIMULATION_WIDTH + j + 1];
            count += cells[i * SIMULATION_WIDTH + j - 1];
            count += cells[i * SIMULATION_WIDTH + j + 1];
            count += cells[(i + 1) * SIMULATION_WIDTH + j - 1];
            count += cells[(i + 1) * SIMULATION_WIDTH + j];
            count += cells[(i + 1) * SIMULATION_WIDTH + j + 1];

            bool state = cells[i * SIMULATION_WIDTH + j];
            new_cells[i * SIMULATION_WIDTH + j] = (state && (count == 2)) || (count == 3);
        }
    }

    for (int i = 0; i < SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < SIMULATION_HEIGHT; j++)
        {
            cells[i * SIMULATION_WIDTH + j] = new_cells[i * SIMULATION_WIDTH + j];
        }
    }

    free(new_cells);
}

void Simulation::draw(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SelectObject(hdc, GetStockObject(DC_BRUSH));

    FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

    SetDCPenColor(hdc, RGB(255, 0, 0));
    SetDCBrushColor(hdc, RGB(255, 0, 0));
    for (int i = 0; i < SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < SIMULATION_HEIGHT; j++)
        {
            if (cells[i * SIMULATION_WIDTH + j])
            {
                Rectangle(hdc, i * 20, j * 20, (i + 1) * 20, (j + 1) * 20);
            }
        }
    }

    EndPaint(hwnd, &ps);
}
