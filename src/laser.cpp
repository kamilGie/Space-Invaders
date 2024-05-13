#include "laser.hpp"

#include <iostream>

Laser::Laser(Vector2 position, int speed) : position(position), speed(speed) {}

void Laser::Draw() {
    if (active) {
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
    }
}

Rectangle Laser::getRect() {
    Rectangle rect;
    rect.x=position.x;
    rect.y=position.y;
    rect.width=4;
    rect.height=15;
    return rect;
}

void Laser::Update() {
    position.y += speed;
    if (active && (position.y > GetScreenHeight()-100 || position.y < 25)) {
        active = false;
    }
}
