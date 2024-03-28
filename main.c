#include <stdio.h>
#include <math.h>

#include "raylib.h"

#define RAD_TO_DEG(rad) (rad) * (180 / PI)
#define DEG_TO_RAD(deg) (deg) / (180 / PI)

#define COLOR ORANGE

const Vector2 screen = {.x = 1000, .y = 1000};

void branche(Vector2 origin, float base_angle, float angle, float step, int level)
{
    if (level <= 0)
        return;

    Vector2 dest = {
        .x = origin.x + cos(DEG_TO_RAD(angle)) * step,
        .y = origin.y - sin(DEG_TO_RAD(angle)) * step,
    };
    DrawLineEx(origin, dest, level/6, COLOR);

    branche(dest, base_angle, angle + base_angle/2, step*3/4, level-1);
    branche(dest, base_angle, angle - base_angle/2, step*3/4, level-1);
}

void arbre(float angle, float step, float level)
{
    Vector2 origin = {screen.x/2, screen.y - 50};
    Vector2 dest = {origin.x, origin.y - step};
    DrawLineEx(origin, dest, level/4, COLOR);

    branche(dest, angle, 90.0f + angle/2, step/2, level);
    branche(dest, angle, 90.0f - angle/2, step/2, level);
}

int main(void)
{
    float angle = 90.0f;

    SetTraceLogLevel(LOG_ERROR);
    InitWindow(screen.x, screen.y, "arbre");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);

            if (IsKeyDown(KEY_D))
                angle -= 0.7f;
            if (IsKeyDown(KEY_A))
                angle += 0.7f;

            arbre(angle, screen.x/4, 16);

            printf(" %.02f         \r", angle);
            fflush(stdout);
        }
        EndDrawing();
    }

    CloseWindow();
    printf("\n");
    return 0;
}
