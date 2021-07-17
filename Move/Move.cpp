#include "Move.h"
#include "../Sudoku/Sudoku.h"

unsigned int Move::__counter = 0;

Move::Move(SudokuCoords pos, uint8_t number, Sudoku::SudokuMeta meta) : _prevNumber(0), _meta(meta), _pos(pos), _number(number)
{
    std::cout << "move created: " << __counter++ << std::endl;
}

Move::Move(const Move &move)
{
    _prevNumber = move._prevNumber;
    _meta = move._meta;
    _pos = move._pos;
    _number = move._number;
    std::cout << __counter++ << std::endl;
}

void Move::apply(uint8_t **board)
{
    _prevNumber = board[_pos._row][_pos._column];
    board[_pos._row][_pos._column] = Sudoku::constructCell(_number, _meta);
}
void Move::retract(uint8_t **board) const
{
    board[_pos._row][_pos._column] = _prevNumber;
}
Move::~Move() { __counter--; }