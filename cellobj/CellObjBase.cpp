#include "cellobj/CellObjBase.hpp"

#include "Enums.hpp"
#include "Map.hpp"
#include "cell/Cell.hpp"
#include "item/Number.hpp"
#include "item/Operator.hpp"
#include "item/Equal.hpp"

#include <stdexcept>

CellObjBase::CellObjBase(Cell* cell) : parent(cell)
{
}

CellObjBase::~CellObjBase()
{
    //////////     TODO     ////////////////////////////////////
    // Modify destructor if you needed.

    //////////   TODO END   ////////////////////////////////////
}

bool CellObjBase::TryMove(Direction dir)
{
    //////////     TODO     ////////////////////////////////////
    // Try to move and return if it actually moved.
    // 1. Get a neighbor in that direction
    // 2. If that neighbor exists, then check its cell type
    // 3. If the neighbor is not Wall, then get its object
    // 4. If the neighbor didn’t have any object, then
    //    swap between the neighbor and return true
    // 5. If any one of 2 to 4 is false, then return false

    Cell* neighbor = this->parent->GetNeighbor(dir);

    if(neighbor == nullptr) {
        return false;
    } else {
        if(neighbor->cellType == CellType::WALL) {
            return false;
        } else {
            if(neighbor->GetObject() == nullptr) {
                this->parent->SwapObject(neighbor);
                return true;
            } else {
                return false;
            }
        }
    }

    //////////   TODO END   ////////////////////////////////////
}

void CellObjBase::InitItem(char itemIcon)
{
    //////////     TODO     ////////////////////////////////////
    // Create this->item.
    // itemIcon == ‘+’: Create ADD operator.
    // itemIcon == ‘-’: Create SUB operator.
    // itemIcon == ‘*’: Create MUL operator.
    // itemIcon == ‘=‘: Create equal, then push back into map->equals.
    // ‘0’ <= itemIcon <= ‘9’: Create the corresponding number.
    // ‘@’: Do nothing (this indicates an empty player).
    // else: Don’t care (throwing runtime_error is best).

    delete this->item;

    if(itemIcon == '+') {
        this->item = new Operator(this, OpType::ADD);
    } else if(itemIcon == '-') {
        this->item = new Operator(this, OpType::SUB);
    } else if(itemIcon == '*') {
        this->item = new Operator(this, OpType::MUL);
    } else if(itemIcon == '=') {
        this->item = new Equal(this);
        this->parent->parent->equals.push_back((Equal*)this->item);
    } else if(('0' <= itemIcon) && (itemIcon <= '9')) {
        this->item = new Number(this, itemIcon - '0');
    } else {
        throw std::runtime_error("Item initialize error");
    }

    //////////   TODO END   ////////////////////////////////////
}
