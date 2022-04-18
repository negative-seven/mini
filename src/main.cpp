#include <windows.h>
#include <stdio.h>

#include "simulation.h"


Simulation simulation;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    const char CLASS_NAME[]  = " ";

    WNDCLASS wc = {};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "GFK 2022",
        WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1024,
        768,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    simulation.init();

    ShowWindow(hwnd, SW_SHOW);

    LARGE_INTEGER targetTime;
    LARGE_INTEGER currentTime;
    LARGE_INTEGER tickTime;

    QueryPerformanceFrequency(&tickTime);
    tickTime.QuadPart = (double)tickTime.QuadPart / TPS;

    QueryPerformanceCounter(&targetTime);

    while (true)
    {
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        QueryPerformanceCounter(&currentTime);
        if (currentTime.QuadPart > targetTime.QuadPart)
        {
            targetTime.QuadPart += tickTime.QuadPart;
            simulation.step();
            InvalidateRect(hwnd, NULL, false);
        }
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        simulation.draw(hwnd);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
