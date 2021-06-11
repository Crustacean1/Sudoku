#ifndef MOVE
#define MOVE

#include "../LinkedNode/LinkedNode.h"
#include "../Sudoku/Sudoku.h"

class Move
{
private:
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