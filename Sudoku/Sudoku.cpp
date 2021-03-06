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
        if (getNumber(_board[row][i]) == number && getMeta(_board[row][i]) != SudokuMeta::Note)
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
        if (getNumber(_board[i][column]) == number && getMeta(_board[i][column]) != SudokuMeta::Note)
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
        for (unsigned int j = 0, cell = _board[rbox * _rootSize + i][cbox * _rootSize]; j < _rootSize; ++j, cell = _board[rbox * _rootSize + i][cbox * _rootSize + j])
        {
            if (getNumber(cell) == number && getMeta(cell) != SudokuMeta::Note)
            {
                return false;
            }
        }
    }
    return true;
}
bool Sudoku::check(uint16_t row, uint16_t column, uint8_t number, SudokuMeta meta) {
  if (meta == SudokuMeta::Note &&
      getMeta(_board[row][column]) == SudokuMeta::Empty) {
    return true;
  }
  return getMeta(_board[row][column]) == SudokuMeta::Empty &&
         checkRow(row, number) && checkColumn(column, number) &&
         checkBox(row / _rootSize, column / _rootSize, number);
}
void Sudoku::applyMove(SudokuCoords &coords, uint8_t cell) {
  _board[coords._row][coords._column] = cell;
}

bool Sudoku::isComplete() const
{
    SudokuMeta meta;
    for (int i = 0; i < _size; ++i)
    {
        for (int j = 0; j < _size; ++j)
        {
            meta = getMeta(_board[i][j]);
            if (meta == SudokuMeta::Empty || meta == SudokuMeta::Note || meta == SudokuMeta::Invalid)
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
