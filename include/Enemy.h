#pragma once

#include <SDL2/SDL.h>
#include <vector>

struct Point
{
    float x;
    float y;
};

struct Bot
{
    float x;
    float y;

    int size;
    float speed;

    int health;
    int maxHealth;

    int reward;
    int castleDamage;

    int currentPoint;

    bool reachedCastle;
    bool alive;
};

void UpdateBots(
    std::vector<Bot> &bots,
    const std::vector<Point> &path,
    float deltaTime
);

void CheckBotDeaths(
    std::vector<Bot> &bots,
    int& playerMoney
);

void CheckCastleReach(
    std::vector<Bot> &bots,
    const std::vector<Point> &path,
    int &castleHealth,
    bool &gameOver
);

void RenderBots(
    SDL_Renderer *renderer,
    const std::vector<Bot> &bots
);
