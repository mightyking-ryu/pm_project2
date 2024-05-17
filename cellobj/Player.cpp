#include "cellobj/Player.hpp"

#include "Map.hpp"
#include "cell/Cell.hpp"

Player::Player(Cell* cell) : CellObjBase(cell)
{
}

bool Player::TryPush(Direction dir)
{
    //////////     TODO     ////////////////////////////////////
    // Try to push other object and return if it actually pushed.
    // 1. Get a neighbor in that direction.
    // 2. If that neighbor exists, then check its cell type.
    // 3. If the neighbor is not Wall, then get its object.
    // 4. If the neighbor had an object, then try to move that object in that direction and return the result.
    // 5. If any one of 2 to 4 is false, then return false.






    //////////   TODO END   ////////////////////////////////////
}

//////////     TODO     ////////////////////////////////////
// Define overrided functions from Player.hpp.





//////////   TODO END   ////////////////////////////////////
