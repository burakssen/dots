#pragma once

#include <random>
#include <limits>
#include <algorithm>
#include <vector>

enum NormalizeMode
{
    Local,
    Global
};

struct Vector2M
{
    float x;
    float y;
};

float fade(float);

float grad(int, float, float, float);

float lerp(float, float, float);

float max(float, float);

float min(float, float);

float clamp01(float);

float inverselerp(float a, float b, float v);

float perlin_values(float, float, float);

std::vector<float> PerlinNoise(int mapWidth, int mapHeight, int seed, float scale, int octaves, float persistance,
                               float lacunarity, Vector2M offset, Vector2M *octaveOffsets, NormalizeMode normalizeMode);
