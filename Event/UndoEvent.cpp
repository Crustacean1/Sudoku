#include "UndoEvent.h"
#include "Move/Move.h"
#include "Sudoku/Sudoku.h"
void UndoEvent::read(std::istream &stream) {}
void UndoEvent::run(Game &game) {
  Move move(SudokuCoords(0, 0), 0, Sudoku::SudokuMeta::Occupied);
  game.applyMove(move);
}
