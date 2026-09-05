#include "Enemy.h"

#include <cmath>
#include <iostream>

void UpdateBots(
    std::vector<Bot> &bots,
    const std::vector<Point> &path,
    float deltaTime
)
{
    for (Bot& bot : bots)
    {
        if (
            bot.alive
            && !bot.reachedCastle
            && bot.currentPoint < static_cast<int>(path.size())
        )
        {
            Point target = path[bot.currentPoint];

            float dx = target.x - bot.x;
            float dy = target.y - bot.y;

            float distance = std::sqrt(dx * dx + dy * dy);

            float movement = bot.speed * deltaTime;

            if (distance <= movement)
            {
                bot.x = target.x;
                bot.y = target.y;

                bot.currentPoint++;
            }
            else
            {
                bot.x += (dx / distance) * movement;
                bot.y += (dy / distance) * movement;
            }
        }
    }
}

void CheckBotDeaths(
    std::vector<Bot> &bots,
    int &playerMoney
)
{
    for (Bot& bot : bots)
    {
        if (bot.health <= 0 && bot.alive)
        {
            bot.health = 0;
            bot.alive = false;

            playerMoney += bot.reward;

            std::cout
                << "Bot died. Reward: "
                << bot.reward
                << std::endl;
        }
    }
}

void CheckCastleReach(
    std::vector<Bot> &bots,
    const std::vector<Point> &path,
    int &castleHealth,
    bool &gameOver
)
{
    for (Bot& bot : bots)
    {
        if (
            bot.currentPoint >= static_cast<int>(path.size())
            && bot.alive
            && !bot.reachedCastle
        )
        {
            bot.reachedCastle = true;
            bot.alive = false;

            castleHealth -= bot.castleDamage;

            if (castleHealth <= 0)
            {
                castleHealth = 0;
                gameOver = true;

                std::cout << "GAME OVER" << std::endl;
            }
        }
    }
}

void RenderBots(
    SDL_Renderer *renderer,
    const std::vector<Bot> &bots
)
{
    for (const Bot& bot : bots)
    {
        if (bot.alive && !bot.reachedCastle)
        {
            SDL_Rect botRect = {
                static_cast<int>(bot.x - bot.size / 2),
                static_cast<int>(bot.y - bot.size / 2),
                bot.size,
                bot.size
            };

            SDL_SetRenderDrawColor(
                renderer,
                200,
                40,
                40,
                255
            );

            SDL_RenderFillRect(
                renderer,
                &botRect
            );
        }
    }
}
