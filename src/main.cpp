#include <raylib.h>

#include "game.hpp"
#include "laser.hpp"

int main() {
    Color grey = {29, 29, 29, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    const int screenWidth = 750;
    const int screenHeight = 700;

    InitWindow(screenWidth + offset, screenHeight + 2 * offset, "space Invaders");

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

    SetTargetFPS(120);

    Game game;

    while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);

        if (game.run) {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        } else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }
        float x = 50.0;
        for (int i = 0; i < game.lives; i++) {
            DrawTextureV(spaceshipImage,{x,745},WHITE);
            x+=50;
        }
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}