#pragma once
#include <memory>
#include <deque>

#include "Map.hpp"
#include "Enums.hpp"
#include "cellobj/Player.hpp"

class Game
{
private:
    Map* map = nullptr;

    std::deque<std::deque<std::tuple<std::string, char, int, int>>> mapStack;

    std::string levelName;
    std::string solutionName;

    void Start();
    void Update();
    void End();

    void Load(std::string filename);
    void StartSolve(std::string filename);
    void AskExit();

    void Move(Direction dir);
    void Undo();

    void SaveMap();

public:
    GameState gameState = GameState::GAMEOVER;

    Game(std::string levelName);
    ~Game();

    void Run();
};
