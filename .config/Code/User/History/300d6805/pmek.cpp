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

Image GenProceduralMap(int width, int height)
{
    Color *pixels = (Color *)RL_MALLOC(width * height * sizeof(Color));

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {

            pixels[i * height + j] = (Color){255, i * 255 / width, j * 255 / height, 255};
        }
    }

    Image image = {
        .data = pixels,
        .width = width,
        .height = height,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        .mipmaps = "1"};

    return image;
}

void Ball::ChangeColor()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        this->color = MAROON;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
        this->color = LIME;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        this->color = DARKBLUE;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_SIDE))
        this->color = PURPLE;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_EXTRA))
        this->color = YELLOW;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_FORWARD))
        this->color = ORANGE;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_BACK))
        this->color = BEIGE;
}

int main()
{

    InitWindow(800, 450, "Raylib Deneme");
    SetTargetFPS(60);

    Ball ball("Denek");
    ball.position = {(float)400, (float)225};

    int scroolSpeed = 4;

    while (!WindowShouldClose())
    {
        ball.position.y -= (GetMouseWheelMove() * scroolSpeed);
        ball.ChangeColor();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        ball.Draw();
        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}