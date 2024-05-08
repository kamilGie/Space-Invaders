#include <raylib.h>

#include "game.hpp"
#include "laser.hpp"

int main() {
    Color grey = {29, 29, 29, 255};
    const int screenWidth = 750;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "space Invaders");
    SetTargetFPS(120);

    Game game;

        while (!WindowShouldClose()) {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}