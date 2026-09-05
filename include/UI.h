#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

void DrawText(
    SDL_Renderer *renderer,
    TTF_Font *font,
    const std::string &text,
    int x,
    int y,
    SDL_Color color
);

void RenderHUD(
    SDL_Renderer *renderer,
    TTF_Font *font,
    int playerMoney,
    int castleHealth,
    int currentWave,
    int aliveEnemies
);

