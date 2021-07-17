#include "MoveEvent.h"

MoveEvent::MoveEvent(Sudoku::SudokuMeta meta)
{
    _data.move._meta = meta;
    activate();
}
MoveEvent::MoveEvent(uint8_t row, uint8_t column, uint8_t number, Sudoku::SudokuMeta meta)
{
    _data.move._coords = SudokuCoords(row, column);
    _data.move._number = number;
    _data.move._meta = meta;
    activate();
    if (_data.move._number == 0)
    {
        deactivate();
    }
}
void MoveEvent::read(std::istream &stream)
{
    _data.move._coords._row = readInt(stream);
    _data.move._coords._column = readInt(stream);
    _data.move._number = readInt(stream);
    if (!stream.eof())
    {
        throw std::runtime_error("Too much arguments");
    }
    activate();
    if (_data.move._number == 0)
    {
        deactivate();
    }
}
void MoveEvent::run(Game &game)
{
    if (active())
    {
        Move move(_data.move._coords, _data.move._number, _data.move._meta);
        game.applyMove(move);
        deactivate();
    }
}
