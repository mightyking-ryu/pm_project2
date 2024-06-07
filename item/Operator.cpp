#include "item/Operator.hpp"

Operator::Operator(CellObjBase* obj, OpType op) : ItemBase(obj), op(op)
{
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Number.hpp.

ItemType Operator::GetType() const {
    return ItemType::OPERATOR;
}

char Operator::GetIcon() const {
    switch(this->op) {
        case OpType::ADD:
            return '+';
        case OpType::SUB:
            return '-';
        case OpType::MUL:
            return '*';
        default:
            throw std::runtime_error("Operator geticon error");
    }
}

//////////   TODO END   ////////////////////////////////////
