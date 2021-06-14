#ifndef MOVE
#define MOVE

#include "../LinkedNode/LinkedNode.h"
#include "../Sudoku/Sudoku.h"

/** Class representing single move by player, meant to be able to retrace itself*/
class Move
{
private:
    /** Previous content of the filled cell*/
    uint8_t _prevNumber;

public:
    Move(Coordinates pos, uint8_t number);

    Coordinates _pos;
    uint8_t _number;

    void apply(uint8_t **board);
    void retract(uint8_t **board) const;

    ~Move();
};

#endif /*MOVE*/