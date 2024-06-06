#include "cell/Wall.hpp"

Wall::Wall(Map* map, int row, int col) : Cell(map, row, col)
{
    this->cellType = CellType::WALL;
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Wall.hpp.

AttrType Wall::GetAttr() const {
    if(obj != nullptr) {
        return Terminal::Attr::REVERSE | obj->GetAttr();
    } else {
        return Terminal::Attr::REVERSE;
    }
}

//////////   TODO END   ////////////////////////////////////
