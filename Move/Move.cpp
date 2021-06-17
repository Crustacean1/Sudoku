#include "Move.h"
#include "../Sudoku/Sudoku.h"

Move::Move(SudokuCoords pos, uint8_t number, Sudoku::SudokuMeta meta) : _prevNumber(0), _meta(meta), _pos(pos), _number(number)
{
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
Move::~Move() {}