#include "UndoEvent.h"

void UndoEvent::read(std::istream &stream)
{
}
void UndoEvent::run(Game &game)
{
    Move move(_data.move._coords, _data.move._number, Sudoku::SudokuMeta::Retract);
    game.applyMove(move);
}