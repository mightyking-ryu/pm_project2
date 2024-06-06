//////////     TODO     ////////////////////////////////////
// Declare your Equal class

#pragma once
#include <string>
#include "item/ItemBase.hpp"

class Equal : public ItemBase
{
public:

    Cell* parentCell;

    Equal(CellObjBase* obj, Cell* parentCell);

    ItemType GetType() const;
    char GetIcon() const;

    std::string GetExpression(Direction dir) const;

};

//////////   TODO END   ////////////////////////////////////
