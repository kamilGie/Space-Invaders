#pragma once
#include <raylib.h>


class Laser {
    public:
        Laser(Vector2 position, int speed);
        void Update();
        void Draw();
        bool active=true;
    private:
    Vector2 position;
    int speed;

};