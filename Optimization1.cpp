//
// Created by egolg on 26.03.2021.
//
#include "Optimization1.h"
#include "math.h"


const int predictedNum = 250;
const int dx = 50;
const int dy = 50;

const float trueF = 0x0;
const float falseF = 0xFFFFFFFF;

float epsilon = 10e-7;


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

bool IsZeroM128 (__m128 a)
{
    for (int i = 0; i < 4; i ++)
    {

        if (fabs(a[i] - 1) < epsilon)
            return 0;
    }
    return 1;
}

void countColour (__m128 xb, __m128 yb, __m128 xx, __m128 yy, float radius, byte* colors)
{
    float SQR = radius * radius;
    __m128 sqrrad = {SQR, SQR, SQR, SQR};
    __m128 exitMask = {1,1,1,1};
    __m128 answ = {0,0,0,0};
    __m128 twos = {2,2,2,2};

    for (int i = 1 ; i <= predictedNum; i++)
    {
        __m128 sqrx    = _mm_mul_ps (xb,xb);
        __m128 sqry    = _mm_mul_ps (yb,yb);
        __m128 sqrNRad = _mm_add_ps (sqrx, sqry);   // necessary countings

        __m128 cmpr = _mm_cmple_ps (sqrNRad, sqrrad);
        exitMask = _mm_and_ps (exitMask, cmpr);         // if points are out of circle
        answ = _mm_add_ps (exitMask, answ);

        if (IsZeroM128 (exitMask))
        {
            //printf ("how awful\n");
            for (int i = 0; i < 4; i++)
            {
                colors[i] = (byte)answ[i];              //checking for exiting by all points
            }
            return;
        }
        __m128 temp = _mm_mul_ps (xb, yb);
        xb = _mm_mul_ps(_mm_add_ps(xx,_mm_sub_ps(sqrx, sqry)), exitMask);
        yb = _mm_mul_ps(_mm_add_ps(_mm_mul_ps (temp, twos), yy), exitMask);
    }
    for (int i = 0; i < 4; i++)
    {
        colors[i] = (byte)answ[i] * (1 - exitMask[i]);
    }
    return;
}

int ShowMandelbrotSet(struct WindowOptions* options, struct ComplexPoint* point)
{
    txCreateWindow (options->width, options->height, true);
    txBegin();

    RGBQUAD* videomem = txVideoMemory(); //get tx memory for faster access

    float radius = 2; //100000000000 * options->scale
    ComplexPoint currPoint = {0,0};

    __m128 xb = {point->x, point->x, point->x, point->x};
    __m128 yb = {point->y, point->y, point->y, point->y};

    __m128 xs = {0,0,0,0};
    __m128 ys = {0,0,0,0};
    byte* colors = (byte*) calloc (4, sizeof(byte));

    for (;;)
    {
        for (;;)
        {
            if (txGetAsyncKeyState (VK_ESCAPE)) return 0;
            if (txGetAsyncKeyState (VK_RIGHT)) {options->x -= dx; break;}
            if (txGetAsyncKeyState (VK_LEFT))  {options->x += dx; break;}
            if (txGetAsyncKeyState (VK_UP))    {options->y -= dy; break;}
            if (txGetAsyncKeyState (VK_DOWN))  {options->y += dy; break;}
            if (txGetAsyncKeyState ('A'))      {options->scale *= 2; break;}
            if (txGetAsyncKeyState ('Z'))      {options->scale /= 2; break;}
        }

        printf ("%lg\n", txGetFPS());
        for (int iy = 0;iy < options->height; iy++)
        {
            for (int ix = 0; ix < options->width; ix+=4) {
                if (txGetAsyncKeyState (VK_ESCAPE)) return 0;
                for (int i = 0; i < 4; i++)
                {
                    xs[i] = (-options->width / 2. + ix + i + options->x) * options->scale;
                    ys[i] = (-options->height / 2. + iy + options->y) * options->scale;
                }

                countColour (xb, yb, xs, ys, radius, colors);

                for (int i = 0; i < 4; i++)
                {
                    *(videomem + (int) (iy * options->width + ix + i)) = {(byte) (colors[i]*12) , (byte) (colors[i] * 17), (byte) (colors[i] * (-13))};
                }


                //SetPoint(&currPoint, (-options->width / 2. + ix + options->x) * options->scale,
                  //       (-options->width / 2. + iy + options->y) * options->scale);

                //byte n = countColour(point, &currPoint, radius);
                //*(videomem + (int) (ix * options->width + iy)) = {(byte) (*(n)*12) , (byte) (*n * 17), (byte) (*n * (-13))};
            }
        }
        txRedrawWindow();
    }

    //txSleep (10000);
    return 0;
}

