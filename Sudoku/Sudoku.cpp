#include "Sudoku.h"
#include <iomanip>
std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku)
{
    for (int i = 0; i < sudoku._size; ++i)
    {
        for (int j = 0; j < sudoku._size; ++j)
        {
            stream<<std::setw(2)<<(int)sudoku._board[i][j]<<" ";
        }
        stream<<"\n";
    }
    return stream;
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
