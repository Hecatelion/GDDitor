#pragma once
#include <iostream>
#include <QDebug>

// vec2
template<typename T>
struct vec2
{
public:
    T x;
    T y;

    vec2(T _x = 0, T _y = 0)
    {
        x = _x;
        y = _y;
    }
};
