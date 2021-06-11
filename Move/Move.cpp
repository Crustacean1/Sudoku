#include "Move.h"
#include "../Sudoku/Sudoku.h"

Move::Move(Coordinates pos, uint8_t number) : _prevNumber(0), _pos(pos), _number(number)
{
}
void Move::apply(uint8_t **board)
{
    _prevNumber = board[_pos._row][_pos._column];
    board[_pos._row][_pos._column] = _number;
}
void Move::retract(uint8_t **board) const
{
    board[_pos._row][_pos._column] = _prevNumber;
}