#define SIMULATION_WIDTH 800
#define SIMULATION_HEIGHT 800

#include <stdbool.h>
#include <windows.h>


struct Simulation
{
    bool *cells;

public:
    void init();
    void step();
    void draw(HWND hwnd);
};
