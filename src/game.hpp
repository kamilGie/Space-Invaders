#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"

class Game {
   public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

   private:
    void DelateInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
   private:
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    std::vector<Laser> alienLasers;
    int aliensDirection;
    constexpr static float alienLasersShootInterval = 0.35;
    float timeLastAlienFired;
};