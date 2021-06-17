#include "MoveEvent.h"

MoveEvent::MoveEvent() : _meta(Sudoku::SudokuMeta::Filled) {}
MoveEvent::MoveEvent(uint8_t row, uint8_t column, uint8_t number, Sudoku::SudokuMeta meta) : _coords(row, column), _number(number), _meta(meta) {}
void MoveEvent::read(std::istream &stream)
{
    _coords._row = readInt(stream);
    _coords._column = readInt(stream);
    _number = readInt(stream);
    if (!stream.eof())
    {
        throw std::runtime_error("Too much arguments");
    }
}
void MoveEvent::run(Game &game)
{
    Move move(_coords, _number, _meta);
    game.applyMove(move);
}