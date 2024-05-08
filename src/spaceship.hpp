#pragma once 
#include <raylib.h>


class Spaceship{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaster();

    private:
    Texture2D image;
    Vector2 position;

};