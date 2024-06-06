#include "cellobj/Box.hpp"

Box::Box(Cell* cell) : CellObjBase(cell)
{
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Box.hpp.

ObjectType Box::GetType() const {
    return ObjectType::BOX;
}

AttrType Box::GetAttr() const {
    return Terminal::Attr::NORMAL;
}

char Box::GetIcon() const {
    return this->item->GetIcon();
}

//////////   TODO END   ////////////////////////////////////
