//////////     TODO     ////////////////////////////////////
// Implement the methods of your Equal class
#pragma once
#include "cell/Cell.hpp"
#include "item/Equal.hpp"

Equal::Equal(CellObjBase* obj, Cell* parentCell) : ItemBase(obj), parentCell(obj->parent)
{
}

ItemType Equal::GetType() const {
    return ItemType::EQUALS;
}

char Equal::GetIcon() const {
    return '=';
}

std::string Equal::GetExpression(Direction dir) const {
    std::string expression = "";
    Cell* currentCell = this->parentCell;
    while(true) {
        Cell* nextCell = currentCell->GetNeighbor(dir);
        if(nextCell == nullptr) {
            break;
        } else {
            if(nextCell->GetObject() == nullptr) {
                break;
            } else {
                char icon = nextCell->GetObject()->GetIcon();
                if((icon == '+') || (icon == '-') || (icon == '*')) {
                    expression = icon + expression;
                } else if (('0' <= icon) && (icon <= '9')) {
                    expression = icon + expression;
                } else {
                    break;
                }
            }
        }
        currentCell = nextCell;
    }
    return expression;
}

//////////   TODO END   ////////////////////////////////////
