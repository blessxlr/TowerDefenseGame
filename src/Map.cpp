#include "Map.h"

void RenderMap(SDL_Renderer* renderer)
{
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

    SDL_RenderFillRect(
        renderer,
        &sandMidlestUpper
    );

    SDL_SetRenderDrawColor(
        renderer,
        80,
        40,
        0,
        255
    );

    SDL_Rect bridgeUpper = {
        680,
        130,
        110,
        80
    };

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

    SDL_RenderFillRect(
        renderer,
        &bridgeLowerRight
    );

    SDL_SetRenderDrawColor(
        renderer,
        145,
        142,
        133,
        255
    );

    SDL_Rect roadFirst = {0, 600, 580, 70};
    SDL_Rect roadSecond = {510, 135, 70, 480};
    SDL_Rect roadThird = {510, 135, 170, 70};
    SDL_Rect roadFourth = {790, 135, 190, 70};
    SDL_Rect roadFive = {980, 135, 70, 495};
    SDL_Rect roadSix = {980, 740, 70, 100};
    SDL_Rect roadSeven = {980, 770, 425, 70};
    SDL_Rect roadEight = {1405, 740, 70, 100};
    SDL_Rect roadNine = {1405, 440, 70, 190};
    SDL_Rect roadTen = {1405, 370, 515, 70};

    SDL_RenderFillRect(renderer, &roadFirst);
    SDL_RenderFillRect(renderer, &roadSecond);
    SDL_RenderFillRect(renderer, &roadThird);
    SDL_RenderFillRect(renderer, &roadFourth);
    SDL_RenderFillRect(renderer, &roadFive);
    SDL_RenderFillRect(renderer, &roadSix);
    SDL_RenderFillRect(renderer, &roadSeven);
    SDL_RenderFillRect(renderer, &roadEight);
    SDL_RenderFillRect(renderer, &roadNine);
    SDL_RenderFillRect(renderer, &roadTen);

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
}
