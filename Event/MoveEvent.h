#ifndef MOVEMENTEVENT
#define MOVEMENTEVENT

#include "Event.h"
#include "Sudoku/Sudoku.h"
#include "GameModes/Game.h"

class MoveEvent : public Event
{

public:
    MoveEvent(Sudoku::SudokuMeta meta = Sudoku::SudokuMeta::Filled);
    MoveEvent(uint8_t row, uint8_t column, uint8_t number, Sudoku::SudokuMeta meta = Sudoku::SudokuMeta::Filled);
    void read(std::istream &stream);
    void run(Game &game);
};

#endif /*MOVEMENTEVENT*/