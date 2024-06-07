#include "cell/Cell.hpp"

#include <string>
#include "utils/Terminal.hpp"
#include <stdexcept>

#include "Map.hpp"
#include "cellobj/Box.hpp"
#include "cellobj/Player.hpp"

Cell::Cell(Map* map, int row, int col) : parent(map), row(row), col(col)
{
    this->cellType = CellType::CELL;
}

Cell::~Cell()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    delete obj;

    //////////   TODO END   ////////////////////////////////////
}

void Cell::InitObject(const std::string& objType)
{
    //////////     TODO     ////////////////////////////////////
    // Initialize object.
    // 1. Delete existing object.
    // 2. Check objType and make corresponding object.
    // 3. push_back the object to the corresponding map->objects[].

    delete obj;

    if(objType.compare("Box") == 0) {

        obj = new Box(this);

    } else if (objType.compare("Player") == 0) {

        obj = new Player(this);

    } else if (objType.compare("Ghost") == 0) {

        obj = new Ghost(this);

    } else {

        throw std::runtime_error("Cell initobject error");

    }

    parent->objects.find(obj->GetType())->second.push_back(obj);

    //////////   TODO END   ////////////////////////////////////
}

void Cell::SwapObject(Cell* other)
{
    //////////     TODO     ////////////////////////////////////
    // Implement object swapping.
    // 1. If this->obj exists: change parent of this->obj.
    // 2. If other->obj exists: change parent of other->obj.
    // 3. Swap this->obj and other->obj.

    if(this->obj != nullptr) {

        this->obj->parent = other;

    }

    if(other->obj != nullptr) {

        other->obj->parent = this;

    }

    std::swap(this->obj, other->obj);

    //////////   TODO END   ////////////////////////////////////
}

void Cell::Print() const
{
    Terminal::PrintIconAt(row, col, this->GetIcon(), this->GetAttr(), this->GetColorPair());
}

AttrType Cell::GetAttr() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetAttr.
    // Default attr is NORMAL, but if this cell has an object, then OR(|) with the object's attr.

    if(obj != nullptr) {
        return Terminal::Attr::NORMAL | obj->GetAttr();
    } else {
        return Terminal::Attr::NORMAL;
    }

    //////////   TODO END   ////////////////////////////////////
}

ColorPair Cell::GetColorPair() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetColorPair.
    // Default ColorPair is NORMAL, but if this->object is a player, then return PLAYER_NORMAL.

    if((obj != nullptr) && (obj->GetType() == ObjectType::PLAYER)) {
        return ColorPair::PLAYER_NORMAL;
    } else {
        return ColorPair::NORMAL;
    }

    //////////   TODO END   ////////////////////////////////////
}

char Cell::GetIcon() const
{
    //////////     TODO     ////////////////////////////////////
    // Implement Cell::GetIcon.
    // Default icon is ' ', but if this cell has an object, then return the object's icon.

    if(obj != nullptr) {
        return obj->GetIcon();
    } else {
        return ' ';
    }

    //////////   TODO END   ////////////////////////////////////
}

Cell* Cell::GetNeighbor(Direction dir) const
{
    //////////     TODO     ////////////////////////////////////
    // Get neighbor of that direction.
    // If the cell is placed at the border of the map and the direction is outside the map, return nullptr.
    // Else return the neighbor cell.

    int neighborRow = row;
    int neighborCol = col;

    switch(dir) {
        case Direction::UP:
            neighborRow--;
            break;
        case Direction::DOWN:
            neighborRow++;
            break;
        case Direction::RIGHT:
            neighborCol++;
            break;
        case Direction::LEFT:
            neighborCol--;
            break;
    }

    int rowSize = parent->GetRowsize();
    int colSize = parent->GetColsize();

    if((0 <= neighborRow) && (neighborRow < rowSize) && (0 <= neighborCol) && (neighborCol < colSize)) {
        return parent->GetCell(neighborRow, neighborCol);
    } else {
        return nullptr;
    }

    //////////   TODO END   ////////////////////////////////////
}
