#include "Sudoku.h"
#include "../Move/Move.h"
#include <iomanip>

std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku)
{
    for (int i = 0; i < sudoku._size; ++i)
    {
        for (int j = 0; j < sudoku._size; ++j)
        {
            stream << std::setw(2) << (int)sudoku._board[i][j] << " ";
        }
        stream << "\n";
    }
    return stream;
}

uint8_t *Sudoku::operator[](uint16_t row)
{
    return _board[row];
}

Sudoku::Sudoku(uint8_t rootSize, uint8_t **board) : _rootSize(rootSize), _size(_rootSize * _rootSize), _board(board)
{
}

Sudoku::~Sudoku()
{
    for (auto i = 0; i < _size; ++i)
    {
        delete[] _board[i];
    }
    delete[] _board;
}
bool Sudoku::checkRow(uint16_t row, uint8_t number)
{
    for (auto i = 0; i < _size; ++i)
    {
        if (_board[row][i] == number)
        {
            return false;
        }
    }
    return true;
}
bool Sudoku::checkColumn(uint16_t column, uint8_t number)
{
    for (auto i = 0; i < _size; ++i)
    {
        if (_board[i][column] == number)
        {
            return false;
        }
    }
    return true;
}
bool Sudoku::checkBox(uint16_t rbox, uint16_t cbox, uint8_t number)
{
    for (auto i = 0; i < _rootSize; ++i)
    {
        for (auto j = 0; j < _rootSize; ++j)
        {
            if (_board[rbox + i][cbox + j] == number)
            {
                return false;
            }
        }
    }
    return true;
}
bool Sudoku::applyMove(Move &move)
{
    if (checkRow(move._pos._row, move._number) &&
        checkColumn(move._pos._column, move._number) &&
        checkBox(move._pos._row / _rootSize, move._pos._column / _rootSize, move._number))
    {
        move.apply(_board);
        return true;
    }
    return false;
}
void Sudoku::retractMove(const Move &move)
{
    move.retract(_board);
}
bool Sudoku::isComplete()
{
    for (int i = 0; i < _size; ++i)
    {
        for (int j = 0; j < _size; ++j)
        {
            if (_board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}