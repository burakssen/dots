#include <iostream>

#include <raylib.h>

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