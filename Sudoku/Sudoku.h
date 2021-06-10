#ifndef SUDOKU
#define SUDOKU

#include <cstdint>
#include <ostream>

class Move;

class Sudoku;

std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku);

class Sudoku
{
private:
    /* data */
    uint16_t _rootSize;
    uint16_t _size;
    uint8_t **_board;
    friend std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku);

public:
    Sudoku(uint8_t rootSize, uint8_t **board);
    bool isValid();
    bool applyMove(const Move &move);

    ~Sudoku();
};
#endif /*SUDOKU*/