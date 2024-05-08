#include <raylib.h>
#include "spaceship.hpp"

int main() {

    Color grey ={29,29,29,255};
    const int screenWidth = 750;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "space Invaders");
    SetTargetFPS(120);

    Spaceship Spaceship;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(grey);
        Spaceship.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}