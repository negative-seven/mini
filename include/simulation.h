#define SIMULATION_WIDTH 800
#define SIMULATION_HEIGHT 800

#include <stdbool.h>
#include <windows.h>


struct Simulation
{
    bool (*cells)[SIMULATION_WIDTH];

public:
    void init();
    void step();
    void draw(HDC hdc, PAINTSTRUCT ps);
};
