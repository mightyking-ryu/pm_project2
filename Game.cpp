#include "Game.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include "utils/Terminal.hpp"

#include "Enums.hpp"
#include "cell/Home.hpp"


Game::Game(std::string levelName)
{
    const std::string sol_ext = ".sol";
    this->levelName = levelName;  // "levels/1-sokoban.txt"
    this->solutionName = levelName + sol_ext;  // "levels/1-sokoban.txt.sol"
}


Game::~Game()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    delete this->map;

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Run the game and start the event loop.
void Game::Run()
{
    Start();
    do
    {
        Update();
    } while (this->gameState != GameState::GAMEOVER);
    End();
}


/// @brief Initialize ncurses environment and load the map.
void Game::Start()
{
    Terminal::InitConsole();
    Load(this->levelName);
    gameState = GameState::PLAYING;
}


/// @brief End the ncurses environment.
void Game::End()
{
    Terminal::EndConsole();
}


/// @brief Run the event loop.
void Game::Update()
{
    Command cmd = Terminal::GetCommand();
    if (this->gameState == GameState::PLAYING)
    {
        switch (cmd)
        {
            case Command::UP:
            case Command::LEFT:
            case Command::DOWN:
            case Command::RIGHT:
                Move((Direction)((int)cmd - (int)Command::UP));
                break;
            case Command::UNDO:
                Undo();
                break;
            case Command::RESTART:
                Load(this->levelName);
                break;
            case Command::SOLVE:
                Load(this->levelName);
                StartSolve(this->solutionName);
                break;
            case Command::EXIT:
                AskExit();
                break;
            default:
                return;
        }
    }
    if (this->gameState == GameState::CLEARED)
    {
        Terminal::PrintMessage(
            "Victory!\n"
            "  q: exit\n"
            "  z: undo\n"
            "  r: restart\n"
        );
        switch (cmd)
        {
            case Command::UNDO:
                Undo();
                this->gameState = GameState::PLAYING;
                Terminal::ClearMessage();
                break;
            case Command::RESTART:
                Load(this->levelName);
                this->gameState = GameState::PLAYING;
                Terminal::ClearMessage();
                break;
            case Command::EXIT:
                this->gameState = GameState::GAMEOVER;
                return;
            default:
                return;
        }
    }
}


/// @brief Load the map from txt file. Also used for resetting the game.
/// @param filename filename of the level file
void Game::Load(std::string filename)
{
    std::ifstream ifs { filename };
    if (!ifs.is_open())
        throw std::runtime_error("Could not open the level file.");

    delete this->map;
    this->map = new Map{ this };

    int rowsize, colsize;
    ifs >> rowsize >> colsize;
    ifs.ignore();  // ignore next '\n' for getline

    this->map->Initialize(rowsize, colsize, ifs);

    // make ghosts
    this->map->SpawnGhosts();
    if (this->map->IsCleared())
        this->gameState = GameState::CLEARED;
    this->map->PrintAll();

    //////////     TODO     ////////////////////////////////////
    // Add undo-related logic if you needed.

    this->mapStack.clear();
    SaveMap();

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Simulate inputs written in the solution file.
/// @param filename filename of the solution file
void Game::StartSolve(std::string filename)
{
    Terminal::PrintMessage(
        "Solving state:\n"
        "  Press any key to continue...\n"
        "  Press Q to stop.\n"
    );
    std::ifstream ifs { filename };
    if (!ifs.is_open())
        throw std::runtime_error("Could not open level file.");
    std::string line;
    std::getline(ifs, line);

    //////////     TODO     ////////////////////////////////////
    // Implement 'solving state'.
    // If every input in the line has been simulated, then the solving state ends.
    // Any keystroke except ‘Q’ will simulate the given input and will progress to next move.
    // If you press ‘Q’, then the solving state ends.
    // When the solving state ends, clear the terminal message.

    int solutionSize = line.length();
    for(int i = 0; i < solutionSize; i++) {
        Command cmd = Terminal::GetCommand();
        if(cmd == Command::EXIT) {
            break;
        } else {
            switch(line[i]) {
                case 'W':
                    this->Move(Direction::UP);
                    break;
                case 'A':
                    this->Move(Direction::LEFT);
                    break;
                case 'S':
                    this->Move(Direction::DOWN);
                    break;
                case 'D':
                    this->Move(Direction::RIGHT);
                    break;
                default:
                    break;
            }
        }
    }
    Terminal::ClearMessage();

    //////////   TODO END   ////////////////////////////////////
}


void Game::AskExit()
{
    Terminal::PrintMessage(
        "Wanna quit?\n"
        "  q: quit\n"
        "  z: resume\n"
    );
    //////////     TODO     ////////////////////////////////////
    // Implement 'exiting state'.
    // Press ‘Q’ again to quit the game.
    // Press ‘Z’ to resume the game and clear the terminal message.

    bool exitingState = false;
    while(!exitingState) {
        Command cmd = Terminal::GetCommand();
        if(cmd == Command::EXIT) {
            this->gameState = GameState::GAMEOVER;
            exitingState = true;
        } else if(cmd == Command::UNDO) {
            exitingState = true;
        }
    }

    Terminal::ClearMessage();

    //////////   TODO END   ////////////////////////////////////
}


void Game::Move(Direction dir)
{
    //////////     TODO     ////////////////////////////////////
    // Implement move.
    // 1. Remove every ghost.
    // 2. Try push and move every player in the given direction.
    // 3. Spawn ghosts.
    // 4. Check if the game’s clear condition is met, and change the game state.
    // 5. Print the map.
    // 6. Push current map state to undo stack.

    this->map->RemoveGhosts();

    // Sort player vector
    switch(dir) {
        case Direction::UP:
            sort(this->map->objects[ObjectType::PLAYER].begin(), this->map->objects[ObjectType::PLAYER].end(), [](CellObjBase* obj1, CellObjBase* obj2) {
                return obj1->parent->row < obj2->parent->row;
            });
            break;
        case Direction::LEFT:
            sort(this->map->objects[ObjectType::PLAYER].begin(), this->map->objects[ObjectType::PLAYER].end(), [](CellObjBase* obj1, CellObjBase* obj2) {
                return obj1->parent->col < obj2->parent->col;
            });
            break;
        case Direction::DOWN:
            sort(this->map->objects[ObjectType::PLAYER].begin(), this->map->objects[ObjectType::PLAYER].end(), [](CellObjBase* obj1, CellObjBase* obj2) {
                return obj1->parent->row > obj2->parent->row;
            });
            break;
        case Direction::RIGHT:
            sort(this->map->objects[ObjectType::PLAYER].begin(), this->map->objects[ObjectType::PLAYER].end(), [](CellObjBase* obj1, CellObjBase* obj2) {
                return obj1->parent->col > obj2->parent->col;
            });
            break;
        default:
            throw std::runtime_error("Move direction error");
    }

    // Try push and move
    for(CellObjBase* playerObj : this->map->objects[ObjectType::PLAYER]) {
        ((Player*) playerObj)->TryPush(dir);
        playerObj->TryMove(dir);
    }

    this->map->SpawnGhosts();
    if(this->map->IsCleared()) {
        this->gameState = GameState::CLEARED;
    }
    this->map->PrintAll();

    // Add current map state to mapStack
    SaveMap();

    //////////   TODO END   ////////////////////////////////////
}


void Game::Undo()
{
    //////////     TODO     ////////////////////////////////////
    // Implement undo feature.
    // 1. Remove every ghost.
    // 2. Pop the undo stack and retrieve previous move information.
    // 3. Change each box position manually.
    // 4. Spawn ghosts.
    // 5. Check if the game’s clear condition is met, and change the game state.
    // 6. Print the map.

    if(this->mapStack.size() <= 1) {
        return;
    }

    this->map->RemoveGhosts();

    this->mapStack.pop_back();

    for(CellObjBase* box : this->map->objects[ObjectType::BOX]) {
        delete box;
    }
    this->map->objects[ObjectType::BOX].clear();

    for(CellObjBase* player : this->map->objects[ObjectType::PLAYER]) {
        delete player;
    }
    this->map->objects[ObjectType::PLAYER].clear();

    this->map->equals.clear();

    for(auto objInfo : this->mapStack.back()) {
        Cell* targetCell = this->map->GetCell(std::get<2>(objInfo), std::get<3>(objInfo));
        targetCell->InitObject(std::get<0>(objInfo));
        targetCell->GetObject()->InitItem(std::get<1>(objInfo));
    }

    this->map->SpawnGhosts();
    if(this->map->IsCleared()) {
        this->gameState = GameState::CLEARED;
    }
    this->map->PrintAll();

    //////////   TODO END   ////////////////////////////////////
}

void Game::SaveMap() {
    std::deque<std::tuple<std::string, char, int, int>> objs;

    for(CellObjBase* box : this->map->objects[ObjectType::BOX]) {
        objs.push_back(std::make_tuple("Box", box->GetIcon(), box->parent->row, box->parent->col));
    }
    for(CellObjBase* player : this->map->objects[ObjectType::PLAYER]) {
        objs.push_back(std::make_tuple("Player", (player->GetIcon() == ' ') ? '@' : player->GetIcon(), player->parent->row, player->parent->col));
    }

    this->mapStack.push_back(objs);
}