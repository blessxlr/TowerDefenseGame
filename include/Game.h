#pragma once

enum class GameState
{
    StartScreen,
    Playing,
    GameOver
};

class Game
{
private:
    GameState gameState;

public:
    Game();

    bool Init();

    void Run();

    void Cleanup();
};
