#include "Sudoku.h"
#include "../Move/Move.h"
#include <iomanip>
#include <cstring>

std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku)
{
    for (int i = 0; i < sudoku._size; ++i)
    {
        for (int j = 0; j < sudoku._size; ++j)
        {
            if (sudoku._board[i][j] == 0)
            {
                std::cout << " - ";
                continue;
            }
            stream << std::setw(2) << (int)Sudoku::getNumber(sudoku._board[i][j]) << " ";
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

Sudoku::Sudoku() : _rootSize(0), _size(0), _board(nullptr) {}
Sudoku::~Sudoku()
{
    if (_board == nullptr)
    {
        return;
    }
    for (auto i = 0; i < _size; ++i)
    {
        delete[] _board[i];
    }
    delete[] _board;
}
bool Sudoku::checkRow(uint16_t row, uint8_t number) const
{
    for (auto i = 0; i < _size; ++i)
    {
        if (getNumber(_board[row][i]) == number)
        {
            return false;
        }
    }
    return true;
}
bool Sudoku::checkColumn(uint16_t column, uint8_t number) const
{
    for (auto i = 0; i < _size; ++i)
    {
        if (getNumber(_board[i][column]) == number)
        {
            return false;
        }
    }
    return true;
}
bool Sudoku::checkBox(uint16_t rbox, uint16_t cbox, uint8_t number) const
{
    for (auto i = 0; i < _rootSize; ++i)
    {
        for (auto j = 0; j < _rootSize; ++j)
        {
            if (getNumber(_board[rbox * _rootSize + i][cbox * _rootSize + j]) == number)
            {
                return false;
            }
        }
    }
    return true;
}
bool Sudoku::check(uint16_t row, uint16_t column, uint8_t number)
{
    return checkRow(row, number) &&
           checkColumn(column, number) &&
           checkBox(row / _rootSize, column / _rootSize, number);
}
void Sudoku::applyMove(Move &move)
{
    if (move._number > _size)
    {
        return;
    }
    auto meta = getMeta((*this)[move._pos]);
    if (meta == SudokuMeta::Empty || meta == SudokuMeta::Filled || meta == SudokuMeta::Invalid || meta == SudokuMeta::Note)
    {
        if (!check(move._pos._row, move._pos._column, move._number))
        {
            move._meta = SudokuMeta::Invalid;
        }
        move.apply(_board);
    }
}
void Sudoku::retractMove(const Move &move)
{
    move.retract(_board);
}
bool Sudoku::isComplete() const
{
    for (int i = 0; i < _size; ++i)
    {
        for (int j = 0; j < _size; ++j)
        {
            if (getMeta(_board[i][j]) == SudokuMeta::Empty)
            {
                return false;
            }
        }
    }
    return true;
}
uint16_t Sudoku::getSize() const { return _size; }
uint16_t Sudoku::getRootSize() const { return _rootSize; }

uint8_t &Sudoku::operator[](const SudokuCoords &coords) { return _board[coords._row][coords._column]; }

Sudoku::Sudoku(const Sudoku &sudoku) : _rootSize(sudoku._rootSize), _size(sudoku._size)
{
    _board = new uint8_t *[_size];
    for (int i = 0; i < _size; ++i)
    {
        _board[i] = new uint8_t[_size];
        memcpy(_board[i], sudoku._board[i], sizeof(uint8_t) * _size);
    }
}
Sudoku::Sudoku(Sudoku &&sudoku) : _rootSize(sudoku._rootSize), _size(sudoku._size), _board(sudoku._board)
{
}

Sudoku &Sudoku::operator=(const Sudoku &sudoku)
{
    _size = sudoku._size;
    _rootSize = sudoku._rootSize;
    _board = new uint8_t *[_size];
    for (int i = 0; i < _size; ++i)
    {
        _board[i] = new uint8_t[_size];
        memcpy(_board[i], sudoku._board[i], sizeof(uint8_t) * _size);
    }
    return *this;
}
Sudoku &Sudoku::operator=(Sudoku &&sudoku)
{
    _rootSize = sudoku._rootSize;
    _size = sudoku._size;
    _board = sudoku._board;
    sudoku._board = nullptr;
    return *this;
}
uint8_t Sudoku::getNumber(uint8_t _cell)
{
    return _cell >> 3;
}
Sudoku::SudokuMeta Sudoku::getMeta(uint8_t _cell)
{
    return static_cast<Sudoku::SudokuMeta>(_cell & 7);
}
uint8_t Sudoku::constructCell(uint8_t number, SudokuMeta meta)
{
    return static_cast<uint8_t>(meta) + (number << 3);
}