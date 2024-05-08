#include "laser.hpp"

#include <iostream>

Laser::Laser(Vector2 position, int speed) : position(position), speed(speed) {}

void Laser::Draw() {
    if (active) {
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
    }
}

void Laser::Update() {
    position.y += speed;
    if (active && (position.y > GetScreenHeight() || position.y < 0)) {
        active = false;
    }
}
