#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#include <emscripten/emscripten.h>

// Compilation
// emcc -o game.html main.c -Os -Wall /opt/webRaylib/raylib-master/src/web/libraylib.a -I. -I /opt/webRaylib/raylib-master/src -L. -L /opt/webRaylib/raylib-master/src/web -s USE_GLFW=3 --shell-file ./shell.html -DPLATFORM_WEB -sGL_ENABLE_GET_PROC_ADDRESS

// Resolution of the grid that will be calculated
const int gridWidth = 1024;
const int gridHeight = 1024;

// Default maximum number of iterations to calculate
int maxIterations = 4098;

// Initial size of the pixels
int pixelSize = 64;

// Default zoom and offset
double zoom = 0.0015;
double xOffset = 0;
double yOffset = 0;

// The grid
int grid[gridWidth][gridHeight];

// Timing
clock_t begin;
clock_t end;
double time_spent = 0;

// Mandelbrot escape time algorithm
int calculateItterations(double firstX, double firstY, int maxIterations)
{
    // Adjust for viewpoint
    firstX *= zoom;
    firstY *= zoom;
    firstX += xOffset;
    firstY += yOffset;

    // Current iterration
    int iterration = 0;

    // The real number
    double x = firstX;
    // Coefficient of i
    double y = firstY;

    // Escape clause
    while (x * x + y * y <= 4 && iterration < maxIterations)
    {
        // Mandelbrot formula
        double newX = x * x - y * y + firstX;
        double newY = 2 * x * y + firstY;

        // Simple loop detection
        if (
            (newX == x && newY == y) ||
            (newX == firstX && newY == firstY))
        {
            iterration = maxIterations;
            // puts("Broke");
            break;
        }

        // Update
        x = newX;
        y = newY;

        // Next iterration
        iterration++;
    }

    return iterration;
}

void UpdateDrawFrame()
{
    // Run the escape time algorithm for each pixel in the current resolution
    for (int j = 0; j < gridHeight; j += pixelSize)
    {
        for (int i = 0; i < gridWidth; i += pixelSize)
        {
            if (grid[i][j] == -1)
            {
                grid[i][j] = calculateItterations(i - gridWidth / 2, j - gridHeight / 2, maxIterations);
            }
        }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw the pixels in different colors based on the number of itterations before escape
    for (int i = 0; i < gridWidth; i += pixelSize)
    {
        for (int j = 0; j < gridHeight; j += pixelSize)
        {
            DrawRectangle(
                i, j, pixelSize, pixelSize,
                ColorFromHSV(
                    (int)powf((grid[i][j] / (double)maxIterations) * 360, 1.5) % 360,
                    1, 1 - grid[i][j] / (double)maxIterations));
        }
    }

    // Current settings
    DrawText(TextFormat("Max iterations: %d", maxIterations), 0, 10, 20, WHITE);
    DrawText(TextFormat("Pixel size: %d", pixelSize), 0, 30, 20, WHITE);
    // Time spent
    if (time_spent > 0)
    {
        DrawText(TextFormat("Time spent: %f", time_spent), 0, 50, 20, WHITE);
    }

    EndDrawing();
    // Increase the resolution
    if (pixelSize > 1)
    {
        pixelSize /= 2;
    }
    else
    {
        // Stop the timer
        if (time_spent == 0)
        {
            clock_t end = clock();
            time_spent = (double)(end - begin);
        }
    }
}

int main()
{

    // ------------------------------------------
    // Different zooms and offsets that look good
    // ------------------------------------------

    maxIterations = 512;

    // Good view of the entire set
    // zoom = 0.002;
    // xOffset = -0.5;
    // yOffset = -0.1;

    // Zoomed in on the edge
    // zoom = 0.0002;
    // xOffset = -0.6;
    // yOffset = -0.5;

    // More
    // zoom = 0.00004;
    // xOffset = -0.52;
    // yOffset = -0.52;

    // Even more
    // zoom = 0.00001;
    // xOffset = -0.52;
    // yOffset = -0.522;

    // Even more more
    zoom = 0.000001;
    xOffset = -0.518;
    yOffset = -0.5215;

    // Start the timer
    begin = clock();

    // Initialize the grid
    for (int i = 0; i < gridWidth; i++)
    {
        for (int j = 0; j < gridHeight; j++)
        {
            grid[i][j] = -1;
        }
    }

    // Initialize the window
    InitWindow(gridWidth, gridHeight, "Raylib Test");

    // Start the main loop
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

    return 0;
}