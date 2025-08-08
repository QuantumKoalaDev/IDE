#pragma once

#include <GL/glew.h>

#include <array>

struct Size
{
    Size() : x(0), y(0) {};
    Size(unsigned int x, unsigned int y): x(x), y(y) {};

    unsigned int x;
    unsigned int y;
};

struct Bearing
{
    Bearing() : x(0), y(0) {};
    Bearing(int x, int y) : x(x), y(y) {};
    signed int x;
    signed int y;
};

struct Character
{
    GLuint TextureID;
    Size Size;
    Bearing Bearing;
    GLuint Advance;
};
