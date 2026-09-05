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

        bool currentTargetValid = false;
        if (tower.targetIndex >= 0 &&
            tower.targetIndex < static_cast<int>(bots.size())
        )
        {
            Bot &currentTarget = bots[tower.targetIndex];
            float dx = currentTarget.x - towerCenterX;
            float dy = currentTarget.y - towerCenterY;

            float distance = std::sqrt(dx * dx + dy * dy);
            if (currentTarget.alive && distance <= tower.range)
            {
                currentTargetValid = true;
            }
            else
            {
                tower.targetIndex = -1;
            }
        }
        if (!currentTargetValid)
        {
            float closetDistance = static_cast<float>(tower.range);

            for(int i = 0; i < static_cast<int>(bots.size()); i++)
            {
                Bot &bot = bots[i];
                if (!bot.alive)
                {
                    continue;
                }

                float dx = bot.x - towerCenterX;
                float dy = bot.y - towerCenterY;
                float distance = std::sqrt(dx * dx + dy * dy);

                if (distance <= closetDistance)
                {
                    closetDistance = distance;
                    tower.targetIndex = i;
                    currentTargetValid = true;
                }
            }
        }

        if (currentTargetValid && tower.attackTimer >= tower.attackCooldown)
        {
            Bot &target = bots[tower.targetIndex];
            target.health -= tower.damage;
            tower.shooting = true;
            tower.shootingTimer = 0.1f;
            tower.targetX = target.x;
            tower.targetY = target.y;

            if (target.health <= 0)
            {
                target.health = 0;
                target.alive = false;
                playerMoney += target.reward;
                tower.targetIndex = -1;
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
