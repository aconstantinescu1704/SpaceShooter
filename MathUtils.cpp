#include "MathUtils.h"
#include<cmath>
#include<SFML/graphics.hpp>

float rand01()
{
    return (float)rand() / RAND_MAX;
}

int intRandRange(int a, int b)
{
    return rand() % (b - a) + a;
}

float floatRandRange(float a, float b)
{
    return rand01() * (b - a) + a;
}

float magnitude(sf::Vector2f v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}