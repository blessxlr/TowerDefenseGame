#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    float x;
    float y;
};

struct Bot {
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

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Tower Defense",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1920,
        1080,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (renderer == nullptr)
    {
        std::cerr << "Ошибка создания renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    SDL_Event event;
    bool running = true;

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

    int currentWave = 1;

    int botsSpawned = 0;
    int maxBots = 5;

    float spawnTimer = 2.0f;
    float spawnInterval = 2.0f;

    bool waitingForNextWave = false;
    float waveTimer = 0.0f;
    float waveInterval = 5.0f;
    bool gameWavesFinished = false;

    int playerMoney = 0;
    int castleHealth = 1000;
    int castleMaxHealth = 1000;

    bool gameOver = false;
    bool gameWon = false;

    Uint64 previousTime = SDL_GetTicks64();

    while (running)
    {
        Uint64 currentTime = SDL_GetTicks64();
        float deltaTime = (currentTime - previousTime) / 1000.0f;
        previousTime = currentTime;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE && !gameOver && !gameWon)
            {
                for (Bot &bot : bots)
                    {
                        if (bot.alive)
                        {
                            bot.health -= 25;
                            std::cout << "Bot has a damage. HP: " << bot.health << std::endl;
                        }
                    }
             }
        }

        if (!gameOver && !gameWon)
        {

            if (botsSpawned < maxBots && !waitingForNextWave && !gameWavesFinished)
            {
                spawnTimer += deltaTime;
                if (spawnTimer >= spawnInterval)
                {
                    bool isBoss = currentWave == 3 && botsSpawned == 14;
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
                    std::cout << "BOSS" << std::endl;
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
                std::cout << "RECRUIT" << std::endl;
                }
                botsSpawned++;
                spawnTimer = 0.0f;
                }
            }

            for (Bot &bot : bots)
            {
                if (bot.health <= 0 && bot.alive)
                {
                    bot.health = 0;
                    bot.alive = false;
                    std::cout << "Bot died" << std::endl;

                    playerMoney += bot.reward;
                    std::cout << "Reward " << bot.reward << " Player Money: " << playerMoney << std::endl;
                }
            }
            for (Bot &bot : bots)
            {
                if (bot.alive && !bot.reachedCastle && bot.currentPoint < static_cast<int>(path.size()))
                    {
                        Point target = path[bot.currentPoint];
                        float dx = target.x - bot.x;
                        float dy = target.y - bot.y;
                        float distance = std::sqrt(dx*dx + dy*dy);
                        float movement = bot.speed * deltaTime;

                        if (distance <= movement) {
                            bot.x = target.x;
                            bot.y = target.y;
                            bot.currentPoint++;
                        }
                        else {
                            bot.x += (dx/distance) * movement;
                            bot.y += (dy/distance) * movement;
                        }
                 }
            }

            for (Bot &bot : bots)
            {
                if (bot.currentPoint >= static_cast<int>(path.size()) && bot.alive && !bot.reachedCastle)
                    {
                        bot.reachedCastle = true;
                        bot.alive = false;

                        castleHealth -= bot.castleDamage;
                        if (castleHealth <= 0)
                        {
                            castleHealth = 0;
                            gameOver = true;

                            std::cout << "Catle is crshed" << std::endl;
                            std::cout << "GAME OVER" << std::endl;
                        }

                        std::cout << "Бот достиг крепости" << std::endl;
                        std::cout << "Крепость получила " << bot.castleDamage << "урона. Осталось HP: "
                        << castleHealth << std::endl;
                }
            }

            if (botsSpawned >= maxBots && !waitingForNextWave && !gameWavesFinished)
            {
                bool allBotsFinished = true;
                for (const Bot &bot : bots)
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
                        std::cout << "Wave " << currentWave << " is complete." << std::endl;
                    }
                    else
                    {
                        gameWavesFinished = true;
                        gameWon = true;
                        std::cout << "All waves are complete" << std::endl;
                        std::cout << "WIN" << std::endl;
                    }
                }
            }

            if (waitingForNextWave && !gameWavesFinished)
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
                    std::cout << "Wave №" << currentWave << std::endl;
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

        SDL_Rect riverUpper = {
            700,
            0,
            70,
            650
        };

        SDL_SetRenderDrawColor(
            renderer,
            0,
            150,
            255,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &riverUpper
        );

        SDL_Rect riverMidlest = {
            700,
            650,
            1220,
            70
        };

        SDL_SetRenderDrawColor(
            renderer,
            0,
            150,
            255,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &riverMidlest
        );

        SDL_Rect sandUpperLeft = {
            660,
            0,
            40,
            720
        };

        SDL_SetRenderDrawColor(
            renderer,
            253,
            234,
            168,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &sandUpperLeft
        );

        SDL_Rect sandUpperRight = {
            770,
            0,
            40,
            650
        };

        SDL_SetRenderDrawColor(
            renderer,
            253,
            234,
            168,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &sandUpperRight
        );

        SDL_Rect sandMidlestLower = {
            660,
            720,
            1260,
            40
        };

        SDL_SetRenderDrawColor(
            renderer,
            253,
            234,
            168,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &sandMidlestLower
        );

        SDL_Rect sandMidlestUpper = {
            810,
            610,
            1110,
            40
        };

        SDL_SetRenderDrawColor(
            renderer,
            253,
            234,
            168,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &sandMidlestUpper
        );

        SDL_Rect bridgeUpper = {
            680,
            130,
            110,
            80
        };

        SDL_SetRenderDrawColor(
            renderer,
            80,
            40,
            0,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &bridgeUpper
        );

        SDL_Rect bridgeLowerLeft = {
            975,
            630,
            80,
            110
        };

        SDL_SetRenderDrawColor(
            renderer,
            80,
            40,
            0,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &bridgeLowerLeft
        );

        SDL_Rect bridgeLowerRight = {
            1400,
            630,
            80,
            110
        };

        SDL_SetRenderDrawColor(
            renderer,
            80,
            40,
            0,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &bridgeLowerRight
        );

        SDL_Rect roadFirst = {
            0,
            600,
            580,
            70
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadFirst
        );

        SDL_Rect roadSecond = {
            510,
            135,
            70,
            480
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadSecond
        );

        SDL_Rect roadThird = {
            510,
            135,
            170,
            70
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadThird
        );

        SDL_Rect roadFourth = {
            790,
            135,
            190,
            70
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadFourth
        );

        SDL_Rect roadFive = {
            980,
            135,
            70,
            495
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadFive
        );

        SDL_Rect roadSix = {
            980,
            740,
            70,
            100
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadSix
        );

        SDL_Rect roadSeven = {
            980,
            770,
            425,
            70
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadSeven
        );

        SDL_Rect roadEight = {
            1405,
            740,
            70,
            100
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadEight
        );

        SDL_Rect roadNine = {
            1405,
            440,
            70,
            190
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadNine
        );

        SDL_Rect roadTen = {
            1405,
            370,
            515,
            70
        };

        SDL_SetRenderDrawColor(
            renderer,
            145,
            142,
            133,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &roadTen
        );

        SDL_Rect castle = {
            1700,
            205,
            220,
            615
        };

        SDL_SetRenderDrawColor(
            renderer,
            41,
            49,
            51,
            255
        );

        SDL_RenderFillRect(
            renderer,
            &castle
        );

        for (const Bot &bot : bots)
        {
            if (bot.alive && !bot.reachedCastle) {
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

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
