#include <iostream>

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"

int main()
{
    InitWindow(800, 450, "Raylib Deneme");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}