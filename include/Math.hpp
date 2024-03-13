#pragma once

struct vector2f
{
    float x, y;

    vector2f()
    :x(0.0f), y(0.0f)
    {}

    vector2f(float p_x, float p_y)
    :x(p_x), y(p_y)
    {}
};