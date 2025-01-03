#pragma once
#include "Enums.hpp"
#include "cellobj/CellObjBase.hpp"

class Player : public CellObjBase
{
public:
    Player(Cell* cell);

    bool TryPush(Direction dir);

    //////////     TODO     ////////////////////////////////////
    // Override virtual functions from CellObjBase.
    // You don't have to override them if you want to keep using the CellObjBase functions.

    // Implement Player::GetType that returns PLAYER.
    ObjectType GetType() const override;

    // Implement Player::GetAttr that returns NORMAL.
    AttrType GetAttr() const override;

    // Implement Player::GetIcon.
    // Default icon is ' ', but if the player has an item, then return the item's icon.
    char GetIcon() const override;

    //////////   TODO END   ////////////////////////////////////
};
