#include "game.hpp"

#include <iostream>
#include <fstream>

Game::Game() {
    music = LoadMusicStream("Sounds/music.ogg");
    explosionSound=LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game() {
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

void Game::Draw() {
    spaceship.Draw();

    for (auto& laser : spaceship.lasers) {
        laser.Draw();
    }

    for (auto& obstacle : obstacles) {
        obstacle.Draw();
    }

    for (auto& alien : aliens) {
        alien.Draw();
    }

    for (auto& laser : alienLasers) {
        laser.Draw();
    }

    mysteryship.Draw();
}

void Game::Update() {
    if (run) {
        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryshipSpawnInterval) {
            mysteryship.Spawn();
            timeLastSpawn = GetTime();
            mysteryshipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto& laser : spaceship.lasers) {
            laser.Update();
        }

        MoveAliens();

        AlienShootLaser();

        for (auto& laser : alienLasers) {
            laser.Update();
        }

        DelateInactiveLasers();
        mysteryship.Update();

        CheckForColisions();
    }
}

void Game::HandleInput() {
    if (run) {
        if (IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        } else if (IsKeyDown(KEY_RIGHT)) {
            spaceship.MoveRight();
        } else if (IsKeyDown(KEY_SPACE)) {
            spaceship.FireLaser();
        }
    } else {
        if (IsKeyDown(KEY_ENTER)) {
            Reset();
            InitGame();
        }
    }
}

void Game::DelateInactiveLasers() {
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->active) {
            it = spaceship.lasers.erase(it);
        } else {
            ++it;
        }
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end();) {
        if (!it->active) {
            it = alienLasers.erase(it);
        } else {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles() {
    int obstacleWiidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWiidth)) / 5;

    for (int i = 0; i < 4; i++) {
        float offsetx = (i + 1) * gap + i * obstacleWiidth;
        obstacles.push_back(Obstacle({offsetx, (float)GetScreenHeight() - 200}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens() {
    std::vector<Alien> aliens;
    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column++) {
            int alienType;
            if (row == 0) {
                alienType = 3;
            } else if (row == 1 || row == 2) {
                alienType = 2;
            } else {
                alienType = 1;
            }

            float x = 75 + column * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for (auto& alien : aliens) {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25) {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance) {
    for (auto& alien : aliens) {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser() {
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired > alienLasersShootInterval) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width / 2, alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}

void Game::CheckForColisions() {
    // Spaceship Lasers
    for (auto& laser : spaceship.lasers) {
        auto it = aliens.begin();
        while (it != aliens.end()) {
            if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                PlaySound(explosionSound);
                if (it->type == 1) {
                    score += 100;
                } else if (it->type == 2) {
                    score += 200;
                } else if (it->type == 3) {
                    score += 300;
                }
                CHeckForHighScore();

                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }

        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
            mysteryship.alive = false;
            laser.active = false;
            score += 500;
            CHeckForHighScore();
            PlaySound(explosionSound);
        }
    }
    // Alien Lasers
    for (auto& laser : alienLasers) {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false;
            lives--;
            if (lives == 0) {
                GameOver();
            }
        }

        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }

    // alien colision witf obstacle
    for (auto& alien : aliens) {
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), alien.getRect())) {
                    it - obstacle.blocks.erase(it);
                } else {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver();
        }
    }
}

void Game::GameOver() {
    std::cout << " Game over" << std::endl;
    run = false;
}

void Game::Reset() {
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::InitGame() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0;
    timeLastSpawn = 0;
    lives = 3;
    score = 0;
    highScore = LoadHighScoreFromFile();
    run = true;
    mysteryshipSpawnInterval = GetRandomValue(10, 20);
}

void Game::CHeckForHighScore() {
    if(score>highScore){
        highScore=score;
        SaveHighscoreToFile(highScore);
    }
}

void Game::SaveHighscoreToFile(int highscore) {
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()){
        highscoreFile << highScore;
        highscoreFile.close();
    }else {
        std::cerr << " failed to save highscore to file " << std::endl;
    }
}

int Game::LoadHighScoreFromFile() {
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()){
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    }else{
        std::cerr<<" failed to lead highsocre from file"<< std::endl;
    }
    return loadedHighscore;
}
