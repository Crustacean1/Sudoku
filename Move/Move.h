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
    Move(SudokuCoords pos, uint8_t number, Sudoku::SudokuMeta meta, bool remote = false);

    Sudoku::SudokuMeta _meta;
    SudokuCoords _pos;
    uint8_t _number;
    bool _remote;

    void apply(uint8_t **board);
    void retract(uint8_t **board) const;

    bool compare(Move &move);

    ~Move();
};

#endif /*MOVE*/