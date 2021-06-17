#include "Misc.h"

Hint::Hint(unsigned int hintCount) : _hintCount(0), _maxHintCount(hintCount) {}
bool Hint::uncover(SudokuCoords pos, Sudoku &filledSudoku, Sudoku &sudoku)
{
    if (_hintCount == _maxHintCount)
    {
        return false;
    }
    sudoku[pos._row][pos._column] = filledSudoku[pos._row][pos._column];
    ++_hintCount;
    return true;
}
unsigned int Hint::getHintCount() const { return _hintCount; }
unsigned int Hint::getMaxHintCount() const { return _maxHintCount; }

MistakeCounter::MistakeCounter(unsigned int tolerance) : _mistakes(0), _tolerance(tolerance) {}
void MistakeCounter::reset() { _mistakes = 0; }
void MistakeCounter::increment() { _mistakes = std::max(_mistakes + 1, _tolerance); }
bool MistakeCounter::gameOver() const { return _mistakes == _tolerance; };
unsigned int MistakeCounter::getMistakes() const { return _mistakes; }
unsigned int MistakeCounter::getTolerance() const { return _tolerance; }

Timer::Timer(unsigned int timeLimit,TimerMode mode) : _limit(std::chrono::seconds(timeLimit)), _active(false), _mode(mode) {}
unsigned int Timer::asSeconds() const
{
    return (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _beg)).count();
}
void Timer::start()
{
    _active = true;
    _beg = std::chrono::steady_clock::now();
}
unsigned int Timer::limitAsSeconds() const
{
    return _limit.count();
}
bool Timer::isOver() const
{
    return limitAsSeconds() < asSeconds();
}