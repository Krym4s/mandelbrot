//
// Created by egolg on 25.03.2021.
//

#include "Optimzation0.h"

const int predictedNum = 250;

void SetWindowOptions (struct WindowOptions* option, float width, float height, float x, float y, float scale)
{
    option->height = height;
    option->width  = width;

    option->x      = x;
    option->y      = y;

    option->scale  = scale;
}

void SetPoint (struct ComplexPoint* point, float x, float y)
{
    point->x = x;
    point->y = y;
}

byte countColour (struct ComplexPoint* beginPoint, struct ComplexPoint* constPoint, float radius)
{
    struct ComplexPoint currentPoint = *beginPoint;

    float sqrRad  = radius * radius;
    for(int i = 1; i <= predictedNum; i++)
    {
        float currRad = currentPoint.x * currentPoint.x + currentPoint.y * currentPoint.y;

        if (currRad > sqrRad)
        {
            return i;
        }

        float temp = currentPoint.x;
        currentPoint.x = currentPoint.x * currentPoint.x - currentPoint.y * currentPoint.y + constPoint->x;
        currentPoint.y = 2. * temp * currentPoint.y + constPoint->y;
    }
    return 0;
}

int ShowMandelbrotSet(const struct WindowOptions* options, struct ComplexPoint* point)
{
    txCreateWindow (options->width, options->height, true);
    txBegin();

    RGBQUAD* videomem = txVideoMemory(); //get tx memory for faster access

    float radius = 10.9; //100000000000 * options->scale
    ComplexPoint currPoint = {0,0};
    for (int ix = 0;ix < options->width; ix++)
    {
        for (int iy = 0; iy < options->height; iy++) {
            SetPoint(&currPoint, (-options->width / 2. + ix + options->x) * options->scale,
                     (-options->width / 2. + iy + options->y) * options->scale);
            byte n = countColour(point, &currPoint, radius);
            //printf ("%d\n",n);
            *(videomem + (int) (ix * options->width + iy)) = {(byte) (n*12) , (byte) (n * 17), (byte) (n * (-13))};
        }
    }
    txRedrawWindow();


    return 0;
}

