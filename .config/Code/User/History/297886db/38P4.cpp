#include <iostream>

#include <raylib.h>

int main()
{
    InitWindow(800, 450, "Raylib Deneme");
    SetTargetFPS(60);

    int scroolSpeed = 4;

    while (!WindowShouldClose())
    {
        ball.position.y -= (GetMouseWheelMove() * scroolSpeed);
        ball.ChangeColor();
        BeginDrawing();

        int val = GuiSlider((Rectangle){200, 20, 200, 20}, "Deneme", "deneme1", 0, 0, 100);

        Image proc = GenProceduralMap(400, 225, val);
        Texture2D texture;
        texture = LoadTextureFromImage(proc);
        UnloadImage(proc);
        DrawTexture(texture, 0, 0, WHITE);

        if (GuiButton((Rectangle){20, 20, 20, 20}, "Press me!"))
        {
            std::cout << "*************************** Pressed" << std::endl;
        }

        ClearBackground(RAYWHITE);
        ball.Draw();
        EndDrawing();
        UnloadTexture(texture);
    }
    CloseWindow();
    return EXIT_SUCCESS;
}