#pragma once
#include "cell/Cell.hpp"

class Wall : public Cell
{
public:
    Wall(Map* map, int row, int col);

    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from Cell.
    // You don't have to override them if you want to keep using the Cell functions.

    // Implement Wall::GetAttr.
    // Default attr is REVERSE, but if this cell has an object, then OR(|) with the object's attr.
    AttrType GetAttr() const override;

    //////////   TODO END   ////////////////////////////////////
};
