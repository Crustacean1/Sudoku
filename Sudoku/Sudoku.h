#ifndef SUDOKU
#define SUDOKU

#include <cstdint>
#include <ostream>

class Move;

class Sudoku;

std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku);

/** Class representing Sudoku coordinates*/
class SudokuCoords
{
public:
    uint8_t _row;
    uint8_t _column;
    SudokuCoords(uint8_t row = 0, uint8_t column = 0) : _row(row), _column(column) {}
};

/**Class responsible for holding, and manipulating sudoku board*/
class Sudoku
{
public:
    enum class SudokuMeta : unsigned char
    {
        Empty,
        Default,
        Note,
        Filled,
        Occupied,
        Invalid
    };

private:
    /** Sudoku side length can only be squares of natural numbers, hence _rootSize ans _size*/
    uint16_t _rootSize;
    uint16_t _size;
    /** Board representing sudoku fields, missing values are represented as zeros
     * Sudoku fields are represented in format:
     * aaabbbbb
     * where a part is meta information about field
     * and b is numerical value of the field in range <0,63>
    */
    uint8_t **_board;

    friend std::ostream &operator<<(std::ostream &stream, const Sudoku &sudoku);

    /** Checks fro conflicts in row*/
    bool checkRow(uint16_t row, uint8_t number) const;
    /** Checks for conflicts in column*/
    bool checkColumn(uint16_t column, uint8_t number) const;
    /** Check for conflicts in box*/
    bool checkBox(uint16_t rbox, uint16_t cbox, uint8_t number) const;

    bool check(uint16_t row,uint16_t col,uint8_t number);

public:
    Sudoku(uint8_t rootSize, uint8_t **board);
    Sudoku(const Sudoku &sudoku);
    Sudoku(Sudoku &&sudoku);
    Sudoku();

    Sudoku &operator=(const Sudoku &sudoku);
    Sudoku &operator=(Sudoku &&sudoku);

    /** Check if sudoku is filled*/
    bool isComplete() const;

    /** Applies move with no regard for correctness*/
    void applyMove(Move &move);
    /** Undoes a move*/
    void retractMove(const Move &move);

    uint16_t getSize() const;
    uint16_t getRootSize() const;

    uint8_t *operator[](uint16_t row);
    uint8_t &operator[](const SudokuCoords &coords);

    static uint8_t getNumber(uint8_t _cell);
    static SudokuMeta getMeta(uint8_t _cell);

    static uint8_t constructCell(uint8_t number, SudokuMeta meta = SudokuMeta::Filled);

    ~Sudoku();
};
#endif /*SUDOKU*/