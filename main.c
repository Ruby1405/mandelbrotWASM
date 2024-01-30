#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#include <emscripten/emscripten.h>

// emcc -o game.html main.c -Os -Wall /opt/webRaylib/raylib-master/src/web/libraylib.a -I. -I /opt/webRaylib/raylib-master/src -L. -L /opt/webRaylib/raylib-master/src/web -s USE_GLFW=3 --shell-file ./shell.html -DPLATFORM_WEB -sGL_ENABLE_GET_PROC_ADDRESS
// emrun game.html        

const int gridWidth = 1024;
const int gridHeight = 1024;

int maxIterations = 4098;

int pixelSize = 64;

int grid[gridWidth][gridHeight];

clock_t begin;
clock_t end;
double time_spent = 0;

//linear mapping: x in [xMin, xMax] to y in [outMin, outMax]
double map(double x, double xMin, double xMax, double outMin, double outMax)
{
    return (x - xMin) * (outMax - outMin) / (xMax - xMin) + outMin;
}



int calculateItterations (double firstX, double firstY, int maxIterations)
{
    // Good view of the entire set
    firstX *= 0.0015;
    firstY *= 0.0015;
    firstX -= 0.5;

    // Zoomed in on the edge
    // firstX *= 0.0002;
    // firstY *= 0.0002;
    // firstX -= 0.6;
    // firstY -= 0.5;
    
    // More
    // firstX *= 0.00004;
    // firstY *= 0.00004;
    // firstX -= 0.52;
    // firstY -= 0.52;
    
    // Even more
    // firstX *= 0.00001;
    // firstY *= 0.00001;
    // firstX -= 0.52;
    // firstY -= 0.522;

    int iterration = 0;

    double x = firstX;
    double y = firstY;

    while (x*x + y*y <= 2*2 && iterration < maxIterations)
    {
        double newX =  pow(x, 2) - pow(y, 2) + firstX;
        double newY = 2 * x * y + firstY;

        x = newX;
        y = newY;

        iterration++;
    }

    return iterration;
}

void UpdateDrawFrame()
{
    for (int i = 0; i < gridWidth; i+=pixelSize)
        {
            for (int j = 0; j < gridHeight; j+=pixelSize)
            {
                if (grid[i][j] == -1)
                {
                    grid[i][j] = calculateItterations(i-gridWidth/2, j-gridHeight/2, maxIterations);
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < gridWidth; i+=pixelSize)
        {
            for (int j = 0; j < gridHeight; j+=pixelSize) {
                DrawRectangle(
                    i, j, pixelSize, pixelSize,
                    ColorFromHSV(
                        map(grid[i][j], 0, maxIterations, 0, 360),
                        1, grid[i][j] == maxIterations? 0: 1
                ));
            }
        }

        DrawText(TextFormat("Max iterations: %d", maxIterations), 0, 10, 20, WHITE);
        DrawText(TextFormat("Pixel size: %d", pixelSize), 0, 30, 20, WHITE);
        if (time_spent > 0)
        {
            DrawText(TextFormat("Time spent: %f", time_spent), 0, 50, 20, WHITE);
        }

        EndDrawing();
        if (pixelSize > 1)
        {
            pixelSize /= 2;
        }
        else
        {
            if (time_spent == 0)
            {
                clock_t end = clock();
                time_spent = (double)(end - begin);
            }
        }
}

int main() {

    begin = clock();
    
    // for (int i = 0; i < 5000; i++)
    // {
    //     printf("%d\n", i);
    // }
    
    
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            grid[i][j] = -1;
        }
    }

    InitWindow(gridWidth, gridHeight, "Raylib Test");


    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

    return 0;
}