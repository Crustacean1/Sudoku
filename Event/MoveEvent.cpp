#include "MoveEvent.h"

MoveEvent::MoveEvent(Sudoku::SudokuMeta meta) : _meta(meta) {}
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
    activate();
    if (_number == 0)
    {
        deactivate();
    }
}
void MoveEvent::run(Game &game)
{
    if (active())
    {
        Move move(_coords, _number, _meta);
        game.applyMove(move);
        deactivate();
    }
}