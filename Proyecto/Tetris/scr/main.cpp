#include "raylib.h"
#include "iostream"
#include "game.hpp"
#include "eventTriger.hpp"
#include "constants.hpp"
#include "colors.hpp"
#include <iostream>

using namespace std;

int main(void)
{
    const int window_width = 421 + GameConstants::PADDING_LEFT;
    const int window_height = 810 + GameConstants::PADDING_BOTTOM;
    InitWindow(window_width, window_height, "Tetris");
    SetTargetFPS(60);
    Font font = LoadFontEx("/Users/fiorellaflores/Desktop/Coding File/C++ Projects/CCOMP I | Proyecto Final/Tetris/Tetris/scr/Font/monogram.ttf", 64, 0, 0);
    Game game = Game();

    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.HandleLevel();
        game.HandleInput();
        
        if (EventTriggered(game.GetMoveInterval(), game.GetAdditionalMoveInterval())) {
            game.MoveBlockDown(0);
        }
        
        BeginDrawing();
        ClearBackground(black);

        char levelText[10];
        snprintf(levelText, sizeof(levelText), "Level %d", game.level);
        Vector2 levelTextSize = MeasureTextEx(font, levelText, 38, 2);
        DrawTextEx(font, levelText, {window_width - 175 + (170 - levelTextSize.x) / 2, 15}, 38, 2, beige);

        DrawTextEx(font, "Score", {window_width - 140, 85}, 38, 2, beige);
        DrawRectangleRounded({window_width - 180, 135, 170, 60}, 0.3, 6, orange);
        DrawTextEx(font, "Next", {window_width - 130, 225}, 38, 2, beige);
        
        if (game.gameOver) {
            DrawTextEx(font, "GAME OVER", {window_width - 184, 600}, 38, 2, beige);
        }
        char scoreText[10];
        snprintf(scoreText, sizeof(scoreText), "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {window_width - 175 + (170 - textSize.x) / 2, 145}, 38, 2, beige);
        DrawRectangleRounded({window_width - 180, 280, 170, 140}, 0.3, 6, orange);

        game.Draw();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}

