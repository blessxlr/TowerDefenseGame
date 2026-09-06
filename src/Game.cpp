#include "Game.h"

#include "Enemy.h"
#include "Map.h"
#include "Tower.h"
#include "UI.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <vector>

Game::Game()
{
    gameState = GameState::StartScreen;
}

bool Game::Init()
{
    return true;
}

void Game::Run()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr
            << "Ошибка SDL: "
            << SDL_GetError()
            << std::endl;

        return;
    }

    if (TTF_Init() == -1)
    {
        std::cerr
            << "Ошибка SDL_ttf: "
            << TTF_GetError()
            << std::endl;

        SDL_Quit();

        return;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Tower Defense",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1920,
        1080,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }

    SDL_Renderer* renderer =
        SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
        );

    if (renderer == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;

        SDL_DestroyWindow(window);

        return;
    }

    SDL_SetRenderDrawBlendMode(
        renderer,
        SDL_BLENDMODE_BLEND
    );

    TTF_Font* font = TTF_OpenFont(
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        24
    );

    if (font == nullptr)
    {
        std::cerr
            << TTF_GetError()
            << std::endl;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        return;
    }

    SDL_Rect startButton = {
        760,
        500,
        400,
        100
    };

    SDL_Rect restartButton = {
        760,
        500,
        400,
        100
    };

    std::vector<Point> path = {
        {545, 635},
        {545, 170},
        {735, 170},
        {1015, 170},
        {1015, 685},
        {1015, 805},
        {1440, 805},
        {1440, 405},
        {1685, 405}
    };

    std::vector<Bot> bots;

    std::vector<Tower> towers;

    towers.push_back({
        {250, 500, 70, 70},
        0,
        0,
        0,
        0.0f,
        0.0f,
        false,
        false,
        0.0f,
        0.0f,
        0.0f,
        -1
    });

    towers.push_back({
        {250, 700, 70, 70},
        0,
        0,
        0,
        0.0f,
        0.0f,
        false,
        false,
        0.0f,
        0.0f,
        0.0f,
        -1
    });

    towers.push_back({
        {410, 305, 70, 70},
        0,
        0,
        0,
        0.0f,
        0.0f,
        false,
        false,
        0.0f,
        0.0f,
        0.0f,
        -1
    });

    towers.push_back({
        {1080, 360, 70, 70},
        0,
        0,
        0,
        0.0f,
        0.0f,
        false,
        false,
        0.0f,
        0.0f,
        0.0f,
        -1
    });

    towers.push_back({
        {1305, 500, 70, 70},
        0,
        0,
        0,
        0.0f,
        0.0f,
        false,
        false,
        0.0f,
        0.0f,
        0.0f,
        -1
    });

    towers.push_back({
        {1600, 270, 70, 70},
        0,
        0,
        0,
        0.0f,
        0.0f,
        false,
        false,
        0.0f,
        0.0f,
        0.0f,
        -1
    });

    towers.push_back({
        {1085, 870, 70, 70},
        0,
        0,
        0,
        0.0f,
        0.0f,
        false,
        false,
        0.0f,
        0.0f,
        0.0f,
        -1
    });

    towers.push_back({
        {1230, 870, 70, 70},
        0,
        0,
        0,
        0.0f,
        0.0f,
        false,
        false,
        0.0f,
        0.0f,
        0.0f,
        -1
    });

    int currentWave = 1;

    int botsSpawned = 0;
    int maxBots = 5;

    float spawnTimer = 0.0f;
    float spawnInterval = 1.5f;

    bool waitingForNextWave = false;

    float waveTimer = 0.0f;
    float waveInterval = 5.0f;

    bool gameWavesFinished = false;

    int playerMoney = 40;

    int castleHealth = 500;

    bool gameOver = false;
    bool gameWon = false;

    bool running = true;

    SDL_Event event;

    Uint64 previousTime = SDL_GetTicks64();

    while (running)
    {
        Uint64 currentTime = SDL_GetTicks64();

        float deltaTime =
            (currentTime - previousTime)
            / 1000.0f;

        previousTime = currentTime;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN
                && event.button.button == SDL_BUTTON_LEFT
                && gameState == GameState::StartScreen
            )
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                if (mouseX >= startButton.x &&
                    mouseX <= startButton.x + startButton.w &&
                    mouseY >= startButton.y &&
                    mouseY <= startButton.y + startButton.h
                )
                {
                    gameState = GameState::Playing;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN
                && event.button.button == SDL_BUTTON_LEFT
                && gameState == GameState::GameOver
            )
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                if (
                   mouseX >= restartButton.x &&
                   mouseX <= restartButton.x + restartButton.w &&
                   mouseY >= restartButton.y &&
                   mouseY <= restartButton.y + restartButton.h
               )
               {
                   bots.clear();

                   currentWave = 1;
                   botsSpawned = 0;
                   maxBots = 5;

                   spawnTimer = 0.0f;
                   waitingForNextWave = false;
                   waveTimer = 0.0f;

                   gameWavesFinished = false;
                   gameOver = false;
                   gameWon = false;

                   playerMoney = 30;
                   castleHealth = 1000;

                   for (Tower &tower : towers)
                   {
                       tower.built = false;
                       tower.level = 0;
                       tower.range = 0;
                       tower.damage = 0;

                       tower.attackTimer = 0.0f;
                       tower.shooting = false;
                       tower.shootingTimer = 0.0f;
                       tower.targetIndex = -1;
                   }

                   gameState = GameState::Playing;
               }
           }

            if (event.type == SDL_KEYDOWN
                && event.key.keysym.sym == SDLK_SPACE
                && gameState == GameState::Playing
                && !gameOver
                && !gameWon
            )
            {
                for (Bot& bot : bots)
                {
                    if (bot.alive)
                    {
                        bot.health -= 25;
                    }
                }
            }

            if (
                event.type == SDL_MOUSEBUTTONDOWN
                && event.button.button == SDL_BUTTON_LEFT
                && gameState == GameState::Playing
                && !gameOver
                && !gameWon
            )
            {
                HandleTowerClick(
                    towers,
                    event.button.x,
                    event.button.y,
                    playerMoney
                );
            }
        }

        if (gameState == GameState::Playing && !gameOver && !gameWon)
        {
            if (
                botsSpawned < maxBots
                && !waitingForNextWave
                && !gameWavesFinished
            )
            {
                spawnTimer += deltaTime;

                if (spawnTimer >= spawnInterval)
                {
                    bool isBoss =
                        currentWave == 3
                        && botsSpawned == 14;

                    if (isBoss)
                    {
                        bots.push_back({
                            15.0f,
                            635.0f,
                            50,
                            40.0f,
                            300,
                            300,
                            50,
                            125,
                            0,
                            false,
                            true
                        });
                    }
                    else
                    {
                        bots.push_back({
                            15.0f,
                            635.0f,
                            30,
                            50.0f,
                            100,
                            100,
                            10,
                            50,
                            0,
                            false,
                            true
                        });
                    }

                    botsSpawned++;

                    spawnTimer = 0.0f;
                }
            }

            CheckBotDeaths(
                bots,
                playerMoney
            );

            UpdateBots(
                bots,
                path,
                deltaTime
            );

            UpdateTowers(
                towers,
                bots,
                playerMoney,
                deltaTime
            );

            CheckCastleReach(
                bots,
                path,
                castleHealth,
                gameOver
            );

            if (gameOver)
            {
                gameState = GameState::GameOver;
            }

            if (
                botsSpawned >= maxBots
                && !waitingForNextWave
                && !gameWavesFinished
            )
            {
                bool allBotsFinished = true;

                for (const Bot& bot : bots)
                {
                    if (bot.alive)
                    {
                        allBotsFinished = false;
                        break;
                    }
                }

                if (allBotsFinished)
                {
                    if (currentWave < 3)
                    {
                        waitingForNextWave = true;
                        waveTimer = 0.0f;
                    }
                    else
                    {
                        gameWavesFinished = true;
                        gameWon = true;
                    }
                }
            }

            if (
                waitingForNextWave
                && !gameWavesFinished
            )
            {
                waveTimer += deltaTime;

                if (waveTimer >= waveInterval)
                {
                    currentWave++;

                    botsSpawned = 0;

                    spawnTimer = spawnInterval;

                    waitingForNextWave = false;

                    if (currentWave == 2)
                    {
                        maxBots = 8;
                    }
                    else if (currentWave == 3)
                    {
                        maxBots = 15;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(
            renderer,
            34,
            139,
            34,
            255
        );

        SDL_RenderClear(renderer);

        if (gameState == GameState::StartScreen)
        {
            SDL_SetRenderDrawColor(
                renderer,
                50,
                150,
                80,
                255
            );

            SDL_RenderFillRect(
                renderer,
                &startButton
            );

            SDL_Color textColor = {255, 255, 255, 255};

            SDL_Surface *surface = TTF_RenderText_Blended(
                font,
                "START",
                textColor
            );

            if (surface != nullptr)
            {
                SDL_Texture *texture = SDL_CreateTextureFromSurface(
                    renderer,
                    surface
                );

                if (texture != nullptr)
                {
                    SDL_Rect textRect;
                    textRect.w = surface->w;
                    textRect.h = surface->h;
                    textRect.x = startButton.x + (startButton.w - textRect.w) / 2;
                    textRect.y = startButton.y + (startButton.h - textRect.h) / 2;

                    SDL_RenderCopy(
                        renderer,
                        texture,
                        nullptr,
                        &textRect
                    );

                    SDL_DestroyTexture(texture);
                }
                SDL_FreeSurface(surface);
            }
        }
        else if (gameState == GameState::Playing)
        {

            RenderMap(renderer);

            RenderTowers(
                renderer,
                towers
            );

            RenderBots(
                renderer,
                bots
            );

            int aliveEnemies = 0;

            for (const Bot& bot : bots)
            {
                if (bot.alive)
                {
                     aliveEnemies++;
                }
            }

            RenderHUD(
                renderer,
                font,
                playerMoney,
                castleHealth,
                currentWave,
                aliveEnemies
            );
        }

        else if (gameState == GameState::GameOver)
        {
            SDL_SetRenderDrawColor(
                renderer,
                60,
                20,
                20,
                255
            );
            SDL_RenderClear(renderer);

            SDL_Color textColor = {
                255,
                255,
                255,
                255
            };

            DrawText(
                renderer,
                font,
                "GAME OVER",
                860,
                350,
                textColor
            );

            SDL_SetRenderDrawColor(
                renderer,
                180,
                50,
                50,
                255
            );

            SDL_RenderFillRect(
                renderer,
                &restartButton
            );

            DrawText(
                renderer,
                font,
                "RESTART",
                890,
                535,
                textColor
            );
        }

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void Game::Cleanup()
{
}
