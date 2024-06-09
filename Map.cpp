#include "Map.hpp"

#include <istream>
#include <sstream>
#include "utils/Terminal.hpp"
#include <algorithm>

#include "cell/Cell.hpp"
#include "cell/Home.hpp"
#include "cell/Wall.hpp"
#include "cellobj/CellObjBase.hpp"


Map::Map(Game* game) : parent(game), initialized(false)
{
    this->objects[ObjectType::BOX] = std::vector<CellObjBase*>();
    this->objects[ObjectType::PLAYER] = std::vector<CellObjBase*>();
    this->objects[ObjectType::GHOST] = std::vector<CellObjBase*>();
}


Map::~Map()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    int rowSize = this->GetRowsize();
    int colSize = this->GetColsize();

    for(int i = 0; i < rowSize; i++) {
        for(int j = 0; j < colSize; j++) {
            delete this->cells[i][j];
        }
    }

    //////////   TODO END   ////////////////////////////////////
}


/// @brief Initialize this map (only if this has not been initialized yet).
/// @param rowsize number of rows of the level
/// @param colsize number of columns of the level
/// @param ist istream that contains the level information string
/// @note The usage of 'ist' is similar to that of std::cin, since they both inherit std::istream.
void Map::Initialize(int rowsize, int colsize, std::istream& ist)
{
    if (this->initialized) return;
    this->cells.resize(rowsize);

    std::string line;
    //////////     TODO     ////////////////////////////////////
    // 1. Read cell map and construct each cell.
    // 2. Initialize each object and its item.

    for(int i = 0; i < rowsize; i++) {
        std::vector<Cell*> v;
        std::getline(ist, line);
        for(int j = 0; j < colsize; j++) {
            char c = line[j];
            Cell* newCell;

            if(c == ' ') {
                newCell = new Cell(this, i, j);
            } else if(c == '#') {
                newCell = new Wall(this, i, j);
            } else if(('0' <= c) && (c <= '9')) {
                newCell = new Home(this, i, j, c-'0');
                this->homes.push_back(newCell);
            } else {
                throw std::runtime_error("Map initialize error");
            }
            v.push_back(newCell);
        }

        this->cells[i] = v;
    }

    int numberOfObjects;
    ist >> numberOfObjects;
    ist.ignore();

    for(int i = 0; i < numberOfObjects; i++) {
        std::string objType;        
        char icon;
        int objRow;
        int objCol;

        ist >> objType >> icon >> objRow >> objCol;
        ist.ignore();

        Cell* targetCell = this->GetCell(objRow, objCol);
        targetCell->InitObject(objType);
        targetCell->GetObject()->InitItem(icon);
    }

    //////////   TODO END   ////////////////////////////////////
    this->initialized = true;
}


void Map::PrintAll() const
{
    int rowsize = this->GetRowsize();
    int colsize = this->GetColsize();
    for (int r = 0; r < rowsize; r++)
    {
        for (int c = 0; c < colsize; c++)
        {
            this->PrintCell(r, c);
        }
    }
}


void Map::PrintCell(int row, int col) const
{
    this->cells[row][col]->Print();
}


bool Map::IsCleared() const
{
    //////////     TODO     ////////////////////////////////////
    // Check if every home has the correct number.

    bool isCleared = true;
    for(Cell* homeCell : this->homes) {
        if(((Home*) homeCell)->Check() == HomeCheckResult::CORRECT) {
            continue;
        } else {
            isCleared = false;
            break;
        }
    }
    return isCleared;
    //////////   TODO END   ////////////////////////////////////
}

// Validate expression
// return true / false
bool validate(std::string expression) {

    int len = expression.length();

    if(len < 1) {
        return false;
    }

    if(expression[0] == '*') {
        return false;
    }

    for(int i = 1; i < len-1; i++) {
        char current = expression[i];
        char previous = expression[i-1];
        if((current == '+') || (current == '-') || (current == '*')) {
            if((previous == '+') || (previous == '-') || (previous == '*')) {
                return false;
            }
        }
    }

    if((expression[len-1] == '+') || (expression[len-1] == '-') || (expression[len-1] == '*')) {
        return false;
    }

    return true;
}

/// @brief Spawn every ghosts with the correct order.
void Map::SpawnGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Sort this->equals to match spawning order.
    // For every equal, evaluate left/upper expression, get result string, and spawn ghosts.





    //////////   TODO END   ////////////////////////////////////
}


/// @brief Remove every ghosts.
void Map::RemoveGhosts()
{
    //////////     TODO     ////////////////////////////////////
    // Remove every ghosts and clear this->objects[GHOST].

    for(CellObjBase* ghost : this->objects[ObjectType::GHOST]) {
        delete ghost;
    }

    this->objects[ObjectType::GHOST].clear();

    //////////   TODO END   ////////////////////////////////////    
}
