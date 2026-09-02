#include <SDL2/SDL.h>
#include <iostream>

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

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
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

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
