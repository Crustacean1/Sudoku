#ifndef SUDOKU
#define SUDOKU

#include <cstdint>
#include <ostream>

class Move;

class Sudoku;

std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku);

class Coordinates
{
public:
    uint8_t _row;
    uint8_t _column;
    Coordinates(uint8_t row = 0, uint8_t column = 0) : _row(row), _column(column) {}
};

class Sudoku
{
private:
    /* data */
    uint16_t _rootSize;
    uint16_t _size;
    uint8_t **_board;
    friend std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku);
    bool checkRow(uint16_t row, uint8_t number);
    bool checkColumn(uint16_t column, uint8_t number);
    bool checkBox(uint16_t rbox, uint16_t cbox, uint8_t number);

public:
    Sudoku(uint8_t rootSize, uint8_t **board);
    bool isComplete();

    bool applyMove(Move &move);
    void retractMove(const Move &move);

    uint8_t *operator[](uint16_t row);
    ~Sudoku();
};
#endif /*SUDOKU*/