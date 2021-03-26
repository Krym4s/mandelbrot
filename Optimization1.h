//
// Created by egolg on 26.03.2021.
//

#ifndef MANDELBROTSET_OPTIMIZATION1_H
#define MANDELBROTSET_OPTIMIZATION1_H

#include "TXLib.h"
#include <xmmintrin.h>
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
void SetPointCluster (struct PointerClaster* cluster, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

void countColour (__m128 xb, __m128 yb, __m128 xx, __m128 yy, float radius, byte* colors);
bool IsZeroM128 (__m128 a, __m128 b);

int ShowMandelbrotSet (struct WindowOptions* options, struct ComplexPoint* point);

#endif //MANDELBROTSET_OPTIMIZATION1_H
