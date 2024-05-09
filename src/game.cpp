#include "game.hpp"

#include <iostream>

Game::Game() {
    obstacles=CreateObstacles();
}

Game::~Game() {}

void Game::Draw() {
    spaceship.Draw();

    for (auto& laser : spaceship.lasers) {
        laser.Draw();
    }

    for(auto & obstacle : obstacles){
        obstacle.Draw(); 
    }
}

void Game::Update() {
    for (auto& laser : spaceship.lasers) {
        laser.Update();
    }

    DelateInactiveLasers();
}

void Game::HandleInput() {
    if (IsKeyDown(KEY_LEFT)) {
        spaceship.MoveLeft();
    } else if (IsKeyDown(KEY_RIGHT)) {
        spaceship.MoveRight();
    } else if (IsKeyDown(KEY_SPACE)) {
        spaceship.FireLaser();
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
}

std::vector<Obstacle> Game::CreateObstacles() {
    int obstacleWiidth = Obstacle::grid[0].size()*3;
    float gap  = (GetScreenWidth()-(4*obstacleWiidth))/5;

    for(int i = 0; i<4; i++){
        float offsetx = (i+1) * gap + i * obstacleWiidth;
        obstacles.push_back(Obstacle({offsetx,(float)GetScreenHeight()-100}));
    }
    return obstacles;
}
