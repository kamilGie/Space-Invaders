#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

class Game {
   public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    bool run;
    int lives;
    int score;
    int highScore;
    Music music;

   private:
    void DelateInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    void CheckForColisions();
    void GameOver();
    void Reset();
    void InitGame();
    void CHeckForHighScore();
    void SaveHighscoreToFile(int highscore);
    int LoadHighScoreFromFile();
   private:
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    std::vector<Laser> alienLasers;
    Mysteryship mysteryship;
    int aliensDirection;
    constexpr static float alienLasersShootInterval = 0.35;
    float timeLastAlienFired;
    float mysteryshipSpawnInterval;
    float timeLastSpawn;
    Sound explosionSound;
};