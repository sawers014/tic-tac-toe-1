#include "raylib-5.0_macos/include/raylib.h"
#include "raylib-5.0_macos/include/raymath.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define ROWS 3
#define COLUMS 3
#define CELL_DIMENSIONS 120
#define CELL_PADDING 10

#define KNOTT_RADIUS 40
#define CROSS_PADDING 0.15

enum States {
    EMPTY,
    CROSS,
    KNOTT,
};

void drawKnott(Vector2 pos)
{
    Vector2 center = Vector2AddValue(pos, (float) CELL_DIMENSIONS/2);
    DrawRing(center, (float) KNOTT_RADIUS/2, KNOTT_RADIUS, 0, 360, 20, BLUE);
}

void drawCross(Vector2 pos)
{
    Vector2 startPos;
    Vector2 endPos;
    float padding = CELL_DIMENSIONS * CROSS_PADDING;

    startPos = Vector2AddValue(pos, padding);
    endPos = Vector2AddValue(pos, CELL_DIMENSIONS-padding);

    DrawLineEx(startPos, endPos, 15, BLUE);

    startPos = (Vector2){pos.x + CELL_DIMENSIONS - padding, pos.y + padding};
    endPos = (Vector2){pos.x + padding, pos.y + CELL_DIMENSIONS - padding};

    DrawLineEx(startPos, endPos, 15, BLUE);
}

int main()
{
    enum States board[ROWS][COLUMS] = {};
    enum States turn = KNOTT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "tic tac toe");
    SetTargetFPS(60);
    Camera2D camera = {
        .offset = (Vector2){(float) SCREEN_WIDTH/2, (float) SCREEN_HEIGHT/2},
        .target = (Vector2){0.0, 0.0},
        .rotation = 0.0,
        .zoom = 1.0f,
    };

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                for(int y = 0; y < COLUMS; ++y) {
                    for(int x = 0; x < ROWS; ++x) {
                        Vector2 pos = (Vector2){x * (CELL_DIMENSIONS + CELL_PADDING), y * (CELL_DIMENSIONS + CELL_PADDING)};
                        pos = GetScreenToWorld2D(pos, camera);

                        Rectangle rect = (Rectangle){pos.x, pos.y, CELL_DIMENSIONS, CELL_DIMENSIONS};
                        DrawRectangleRec(rect, RED);

                        if(board[x][y] == CROSS) {
                            drawCross(pos);
                        } else if(board[x][y] == KNOTT) {
                            drawKnott(pos);
                        } else {
                            // TODO change rect color on hover
                            Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera);

                            if(CheckCollisionPointRec(mouse, rect) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                                board[x][y] = turn == KNOTT ? CROSS : KNOTT;
                                turn = turn == KNOTT ? CROSS : KNOTT;
                            }
                        }
                    }
                }
            EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
