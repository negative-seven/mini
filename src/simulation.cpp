#include "simulation.h"


void Simulation::init()
{
    for (int i = 0; i < SIMULATION_WIDTH; i++)
    {
        for (int j = 0; j < SIMULATION_HEIGHT; j++)
        {
            cells[i][j] = 0;
        }
    }
    cells[SIMULATION_WIDTH / 2][SIMULATION_HEIGHT / 2] = 1;
    cells[SIMULATION_WIDTH / 2][SIMULATION_HEIGHT / 2 - 1] = 1;
    cells[SIMULATION_WIDTH / 2][SIMULATION_HEIGHT / 2 + 1] = 1;
}

void Simulation::step()
{
    bool new_cells[SIMULATION_WIDTH][SIMULATION_HEIGHT];

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
            if (cells[i][j])
            {
                Rectangle(hdc, i * 20, j * 20, (i + 1) * 20, (j + 1) * 20);
            }
        }
    }

    EndPaint(hwnd, &ps);
}
