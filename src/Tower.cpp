#include "Tower.h"

#include <cmath>
#include <iostream>

void HandleTowerClick(
    std::vector<Tower> &towers,
    int mouseX,
    int mouseY,
    int &playerMoney
)
{
    for (Tower& tower : towers)
    {
        bool mouseInsideTower =
            mouseX >= tower.rect.x
            && mouseX <= tower.rect.x + tower.rect.w
            && mouseY >= tower.rect.y
            && mouseY <= tower.rect.y + tower.rect.h;

        if (!mouseInsideTower)
        {
            continue;
        }

        if (!tower.built)
        {
            if (playerMoney >= 30)
            {
                tower.built = true;
                tower.level = 1;

                playerMoney -= 30;

                tower.range = 180;
                tower.damage = 25;

                tower.attackCooldown = 1.0f;
                tower.attackTimer = 0.0f;

                std::cout << "Tower built" << std::endl;
            }
        }
        else if (tower.level == 1)
        {
            if (playerMoney >= 100)
            {
                tower.level = 2;

                playerMoney -= 100;

                tower.range = 250;
                tower.damage = 60;

                tower.attackCooldown = 0.7f;
                tower.attackTimer = 0.0f;

                std::cout << "Tower upgraded" << std::endl;
            }
        }
    }
}

void UpdateTowers(
    std::vector<Tower> &towers,
    std::vector<Bot> &bots,
    int &playerMoney,
    float deltaTime
)
{
    for (Tower& tower : towers)
    {
        if (!tower.built)
        {
            continue;
        }

        if (tower.shooting)
        {
            tower.shootingTimer -= deltaTime;

            if (tower.shootingTimer <= 0.0f)
            {
                tower.shooting = false;
            }
        }

        tower.attackTimer += deltaTime;

        float towerCenterX =
            tower.rect.x + tower.rect.w / 2.0f;

        float towerCenterY =
            tower.rect.y + tower.rect.h / 2.0f;

        Bot* target = nullptr;

        float closestDistance =
            static_cast<float>(tower.range);

        for (Bot& bot : bots)
        {
            if (!bot.alive)
            {
                continue;
            }

            float botCenterX =
                bot.x + bot.size / 2.0f;

            float botCenterY =
                bot.y + bot.size / 2.0f;

            float dx =
                botCenterX - towerCenterX;

            float dy =
                botCenterY - towerCenterY;

            float distance =
                std::sqrt(dx * dx + dy * dy);

            if (distance < closestDistance)
            {
                closestDistance = distance;
                target = &bot;
            }
        }

        if (
            target != nullptr
            && tower.attackTimer >= tower.attackCooldown
        )
        {
            target->health -= tower.damage;

            tower.shooting = true;
            tower.shootingTimer = 0.1f;

            tower.targetX =
                target->x + target->size / 2.0f;

            tower.targetY =
                target->y + target->size / 2.0f;

            if (target->health <= 0)
            {
                target->health = 0;
                target->alive = false;

                playerMoney += target->reward;

                std::cout
                    << "Tower killed enemy"
                    << std::endl;
            }

            tower.attackTimer = 0.0f;
        }
    }
}

void RenderTowers(
    SDL_Renderer *renderer,
    const std::vector<Tower> &towers
)
{
    for (const Tower& tower : towers)
    {
        SDL_SetRenderDrawColor(
            renderer,
            0,
            0,
            0,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &tower.rect
        );

        if (tower.built)
        {
            SDL_Rect towerVisual = {
                tower.rect.x + 5,
                tower.rect.y + 5,
                60,
                60
            };

            if (tower.level == 1)
            {
                SDL_SetRenderDrawColor(
                    renderer,
                    50,
                    100,
                    255,
                    255
                );
            }
            else if (tower.level == 2)
            {
                SDL_SetRenderDrawColor(
                    renderer,
                    255,
                    180,
                    0,
                    255
                );
            }

            SDL_RenderFillRect(
                renderer,
                &towerVisual
            );
        }

        if (tower.shooting)
        {
            SDL_SetRenderDrawColor(
                renderer,
                255,
                0,
                0,
                255
            );

            int towerCenterX =
                tower.rect.x + tower.rect.w / 2;

            int towerCenterY =
                tower.rect.y + tower.rect.h / 2;

            SDL_RenderDrawLine(
                renderer,
                towerCenterX,
                towerCenterY,
                static_cast<int>(tower.targetX),
                static_cast<int>(tower.targetY)
            );
        }
    }
}
