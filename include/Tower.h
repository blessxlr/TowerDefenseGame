#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Enemy.h"

struct Tower
{
    SDL_Rect rect;

    int level;

    int range;
    int damage;

    float attackCooldown;
    float attackTimer;

    bool built;

    bool shooting;
    float shootingTimer;

    float targetX;
    float targetY;
};

void HandleTowerClick(
    std::vector<Tower> &towers,
    int mouseX,
    int mouseY,
    int &playerMoney
);

void UpdateTowers(
    std::vector<Tower> &towers,
    std::vector<Bot> &bots,
    int &playerMoney,
    float deltaTime
);

void RenderTowers(
    SDL_Renderer *renderer,
    const std::vector<Tower> &towers
);
