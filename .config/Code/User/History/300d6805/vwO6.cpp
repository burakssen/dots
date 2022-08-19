#include <iostream>
#include <raylib.h>

class Ball
{
    std::string name;
    Color color;

public:
    Vector2 position;
    Ball(std::string);
    void Draw();
    void ChangeColor();
};

Ball::Ball(std::string name)
{
    this->name = name;
}

void Ball::Draw()
{

    DrawCircleV(position, 50, color);

    DrawText(this->name.c_str(), position.x - MeasureText(this->name.c_str(), 10) / 2, position.y, 10, YELLOW);
}

void Ball::ChangeColor()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        ballColor = MAROON;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
        ballColor = LIME;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        ballColor = DARKBLUE;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE))
        ballColor = PURPLE;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA))
        ballColor = YELLOW;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_FORWARD))
        ballColor = ORANGE;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_BACK))
        ballColor = BEIGE;
}

int main()
{

    InitWindow(800, 450, "Raylib Deneme");
    SetTargetFPS(60);

    Ball ball("Denek");
    ball.position = {(float)400, (float)225};

    while (!WindowShouldClose())
    {
        ball.position = GetMousePosition();
        ball.ChangeColor();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        ball.Draw();
        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}