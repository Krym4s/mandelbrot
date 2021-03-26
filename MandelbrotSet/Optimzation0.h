//
// Created by egolg on 25.03.2021.
//

#ifndef MANDELBROTSET_OPTIMZATION0_H
#define MANDELBROTSET_OPTIMZATION0_H
#include "TXLib.h"
#include <stdlib.h>
#include <stdio.h>

struct WindowOptions
{
    float width;
    float height;

    float x;
    float y;

    float scale;
};

struct ComplexPoint
{
    float x;
    float y;
};

void SetWindowOptions (struct WindowOptions* option, float width, float height, float x, float y, float scale);
void SetPoint (struct ComplexPoint* point, float x, float y);

byte countColour (struct ComplexPoint* beginPoint, struct ComplexPoint* constPoint, float radius);

int ShowMandelbrotSet (const struct WindowOptions* options, struct ComplexPoint* point);

#endif //MANDELBROTSET_OPTIMZATION0_H
