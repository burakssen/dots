#include "perlinnoise.h"

#include <time.h>

bool filled = false;

int perm[] = {
    151, 160, 137, 91, 90, 15, // Hash lookup table as defined by Ken Perlin.  This is a randomly
    131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
    // arranged array of all numbers from 0-255 inclusive.
    190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
    88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
    77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
    102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
    135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
    5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
    223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
    129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
    251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
    49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
    138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180};

int p[512];

void fill()
{
    for (int x = 0; x < 512; x++)
    {
        p[x] = perm[x % 256];
    }
    filled = true;
}

float perlin_values(float x, float y, float z)
{
    if (!filled)
        fill();

    int xi, yi, zi;
    float xf, yf, zf;

    if (x < 0.0)
    {
        xi = 255 - ((int)(-x) & 255);
        xf = 1 + x - (int)x;
    }
    else
    {
        xi = (int)x & 255;
        xf = x - (int)x;
    }

    if (y < 0.0)
    {
        yi = 255 - ((int)(-y) & 255);
        yf = 1 + y - (int)y;
    }
    else
    {
        yi = (int)y & 255;
        yf = y - (int)y;
    }

    if (z < 0.0)
    {
        zi = 255 - ((int)(-z) & 255);
        zf = 1 + z - (int)z;
    }
    else
    {
        zi = (int)z & 255;
        zf = z - (int)z;
    }
    float u = fade(xf);
    float v = fade(yf);
    float w = fade(zf);

    int a = p[xi] + yi;
    int aa = p[a] + zi;
    int ab = p[a + 1] + zi;
    int b = p[xi + 1] + yi;
    int ba = p[b] + zi;
    int bb = p[b + 1] + zi;

    float x1, x2, y1, y2;
    x1 = lerp(grad(p[aa], xf, yf, zf),
              grad(p[ba], xf - 1, yf, zf),
              u);
    x2 = lerp(grad(p[ab], xf, yf - 1, zf),
              grad(p[bb], xf - 1, yf - 1, zf),
              u);
    y1 = lerp(x1, x2, v);

    x1 = lerp(grad(p[aa + 1], xf, yf, zf - 1),
              grad(p[ba + 1], xf - 1, yf, zf - 1),
              u);
    x2 = lerp(grad(p[ab + 1], xf, yf - 1, zf - 1),
              grad(p[bb + 1], xf - 1, yf - 1, zf - 1),
              u);
    y2 = lerp(x1, x2, v);

    return (lerp(y1, y2, w) + 1) / 2;
}

float fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float grad(int hash, float x, float y, float z)
{
    int h = hash % 15;
    float u = h < 8 ? x : y;
    float v;
    if (h < 4)
        v = y;
    else if (h == 12 || h == 14)
        v = x;
    else
        v = z;

    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

float lerp(float a, float b, float x)
{
    return a + x * (b - a);
}

float max(float first, float second)
{
    return first > second ? first : second;
}

float min(float first, float second)
{
    return first < second ? first : second;
}

float clamp(float v, float minV, float maxV)
{
    return min(max(v, minV), maxV);
}

float inverselerp(float a, float b, float v)
{
    return clamp((v - a) / (b - a), 0.0f, 1.0f);
}
std::vector<float> PerlinNoise(int mapWidth, int mapHeight, int seed, float scale, int octaves, float persistance,
                               float lacunarity, Vector2M offset, Vector2M *octaveOffsets, NormalizeMode normalizeMode)
{
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> gen(-100000, 100000);
    float maxPossibleHeight = 0;
    float amplitude = 1;
    float frequency = 1;

    std::vector<float> noiseMap;
    noiseMap.reserve(mapHeight * mapWidth);

    for (int i = 0; i < octaves; i++)
    {
        float offsetX = gen(rng) + offset.x;
        float offsetY = gen(rng) - offset.y;
        octaveOffsets[i].x = offsetX;
        octaveOffsets[i].y = offsetY;
        maxPossibleHeight += amplitude;
        amplitude *= persistance / 2;
    }

    if (scale <= 0.0)
        scale = 0.0001f;

    float maxLocalNoiseHeight = std::numeric_limits<float>::min();
    float minLocalNoiseHeight = std::numeric_limits<float>::max();

    // for zooming in to center of the noisemap
    float halfWidth = mapWidth / 2.0f;
    float halfHeight = mapHeight / 2.0f;

    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            amplitude = 1;
            frequency = 1;
            float noiseHeight = 0;

            for (int i = 0; i < octaves; i++)
            {
                float sampleX = (x - halfWidth + octaveOffsets[i].x) / scale * frequency;
                float sampleY = (y - halfHeight + octaveOffsets[i].y) / scale * frequency;
                float perlinValue = perlin_values(sampleX, sampleY, 0.0f);
                noiseHeight += perlinValue * amplitude;
                amplitude *= persistance / 2;
                frequency *= lacunarity / 2;
            }

            if (noiseHeight > maxLocalNoiseHeight)
            {
                maxLocalNoiseHeight = noiseHeight;
            }
            else if (noiseHeight < minLocalNoiseHeight)
            {
                minLocalNoiseHeight = noiseHeight;
            }

            noiseMap[x * mapHeight + y] = noiseHeight;
        }
    }

    for (int x = 0; x < mapWidth; x++)
    {
        for (int y = 0; y < mapHeight; y++)
        {
            if (normalizeMode == NormalizeMode::Local)
            {
                noiseMap[x * mapHeight + y] = inverselerp(minLocalNoiseHeight, maxLocalNoiseHeight,
                                                          noiseMap[x * mapHeight + y]);
            }
            else
            {
                float normalizedHeight = (noiseMap[x * mapHeight + y]) / (maxPossibleHeight * 0.535f);
                noiseMap[x * mapHeight + y] = clamp(normalizedHeight, 0.0f, std::numeric_limits<float>::max()) - 0.35f;
            }
        }
    }

    return noiseMap;
}
