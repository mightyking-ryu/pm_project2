//////////     TODO     ////////////////////////////////////
// Declare your Home class

#pragma once
#include "cell/Cell.hpp"

class Home : public Cell
{
public:
    Home(Map* map, int row, int col, int targetNumber);

    int targetNumber;

    AttrType GetAttr() const override;
    ColorPair GetColorPair() const override;
    char GetIcon() const override;

    HomeCheckResult Check() const;
};

//////////   TODO END   ////////////////////////////////////