#ifndef MOVE
#define MOVE

#include "../LinkedNode/LinkedNode.h"
#include "../LinkedList/LinkedList.h"
#include "../Sudoku/Sudoku.h"
#include <memory>

/** Class representing single move by player, meant to be able to retrace itself*/
class Move
{
private:
    /** Previous content of the filled cell*/
    uint8_t _prevNumber;
    static unsigned int __counter;

public:
    Move(const Move &move);
    Move(SudokuCoords pos, uint8_t number, Sudoku::SudokuMeta meta);

    Sudoku::SudokuMeta _meta;
    SudokuCoords _pos;
    uint8_t _number;

    void apply(LinkedList<Move> &moves, Sudoku & sudoku);

    ~Move();
};

#endif /*MOVE*/
