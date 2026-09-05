#include "UI.h"

void DrawText(
    SDL_Renderer *renderer,
    TTF_Font *font,
    const std::string &text,
    int x,
    int y,
    SDL_Color color
)
{
    SDL_Surface *textSurface =
        TTF_RenderText_Solid(
            font,
            text.c_str(),
            color
        );

    if (textSurface == nullptr)
    {
        return;
    }

    SDL_Texture *textTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            textSurface
        );

    SDL_Rect textRect = {
        x,
        y,
        textSurface->w,
        textSurface->h
    };

    SDL_FreeSurface(textSurface);

    SDL_RenderCopy(
        renderer,
        textTexture,
        nullptr,
        &textRect
    );

    SDL_DestroyTexture(textTexture);
}

void RenderHUD(
    SDL_Renderer *renderer,
    TTF_Font *font,
    int playerMoney,
    int castleHealth,
    int currentWave,
    int aliveEnemies
)
{
    SDL_Rect infoDisplay = {
        0,
        0,
        300,
        150
    };

    SDL_SetRenderDrawColor(
        renderer,
        34,
        159,
        34,
        105
    );

    SDL_RenderFillRect(
        renderer,
        &infoDisplay
    );

    SDL_Color white = {
        255,
        255,
        255,
        255
    };

    DrawText(
        renderer,
        font,
        "Money: " + std::to_string(playerMoney),
        20,
        15,
        white
    );

    DrawText(
        renderer,
        font,
        "Castle Health: " + std::to_string(castleHealth),
        20,
        45,
        white
    );

    DrawText(
        renderer,
        font,
        "Wave: " + std::to_string(currentWave),
        20,
        75,
        white
    );

    DrawText(
        renderer,
        font,
        "Enemies: " + std::to_string(aliveEnemies),
        20,
        105,
        white
    );
}
