//////////     TODO     ////////////////////////////////////
// Implement the methods of your Home class

#include "cell/Home.hpp"
#include <stdexcept>

Home::Home(Map* map, int row, int col, int targetNumber) : Cell(map, row, col), targetNumber(targetNumber) {
    this->cellType = CellType::HOME;
}

AttrType Home::GetAttr() const {
    if(obj == nullptr) {
        return Terminal::Attr::UNDERLINE | Terminal::Attr::DIM;
    } else {
        return Terminal::Attr::UNDERLINE | obj->GetAttr();
    }
}

ColorPair Home::GetColorPair() const {
    switch(this->Check()) {
        case HomeCheckResult::EMPTY:
            return ColorPair::NORMAL;
        case HomeCheckResult::CORRECT:
            if(obj->GetType() == ObjectType::PLAYER) {
                return ColorPair::PLAYER_CORRECT;
            } else {
                return ColorPair::CORRECT;
            }
        case HomeCheckResult::WRONG:
            if(obj->GetType() == ObjectType::PLAYER) {
                return ColorPair::PLAYER_WRONG;
            } else {
                return ColorPair::WRONG;
            }
        default:
            throw std::runtime_error("Home getcolorpair error");
    }
}

char Home::GetIcon() const {
    if(obj != nullptr) {
        return obj->GetIcon();
    } else {
        return targetNumber + '0';
    }
}

HomeCheckResult Home::Check() const {
    if(obj == nullptr) {
        return HomeCheckResult::EMPTY;
    } else {
        if(obj->GetItem() == nullptr) {
            return HomeCheckResult::WRONG;
        } else {
            if(obj->GetItem()->GetType() != ItemType::NUMBER) {
                return HomeCheckResult::WRONG;
            } else {
                if((obj->GetItem()->GetIcon()-'0') == targetNumber) {
                    return HomeCheckResult::CORRECT;
                } else {
                    return HomeCheckResult::WRONG;
                }
            }
        }
    }
}

//////////   TODO END   ////////////////////////////////////