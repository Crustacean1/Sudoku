#include "Move.h"
#include "../Sudoku/Sudoku.h"

unsigned int Move::__counter = 0;

Move::Move(SudokuCoords pos, uint8_t number, Sudoku::SudokuMeta meta)
    : _prevNumber(0), _meta(meta), _pos(pos), _number(number) {
  std::cout << "move created: " << __counter++ << std::endl;
}

Move::Move(const Move &move) {
  _prevNumber = move._prevNumber;
  _meta = move._meta;
  _pos = move._pos;
  _number = move._number;
  std::cout << __counter++ << std::endl;
}

void Move::apply(LinkedList<Move> &moves, Sudoku &sudoku) {
  uint8_t newCell = Sudoku::constructCell(_number, _meta);
  _prevNumber = sudoku[_pos];
  std::cerr<<"moving: "<<static_cast<unsigned int>(_meta)<<static_cast<unsigned int>(Sudoku::SudokuMeta::Occupied)<<static_cast<unsigned int>(Sudoku::SudokuMeta::Filled)<<std::endl;
  if (_meta == Sudoku::SudokuMeta::Occupied) {
    if (moves.empty()) {
      std::cerr<<"queue is empty"<<std::endl;
      return;
    }
    newCell = moves.getRoot()->prev()->_value._prevNumber;
    _pos = moves.getRoot()->prev()->_value._pos;
    std::cerr<<"undoing of man: "<<_pos._row<<" "<<_pos._column<<std::endl;

  } else {
    std::cerr<<"move pushed to queue"<<std::endl;
    moves.push_back(*this);
  }
  sudoku.applyMove(_pos, newCell);
}
Move::~Move() { __counter--; }
