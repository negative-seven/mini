#define SIMULATION_WIDTH 20
#define SIMULATION_HEIGHT 20

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
