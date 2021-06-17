#include "Misc.h"

Hint::Hint(unsigned int hintCount) : _hintCount(0), _maxHintCount(hintCount) {}
bool Hint::uncover(SudokuCoords pos, Sudoku &filledSudoku, Sudoku &sudoku)
{
    if (_hintCount == _maxHintCount)
    {
        return false;
    }
    sudoku[pos._row][pos._column] = Sudoku::constructCell(Sudoku::getNumber(filledSudoku[pos._row][pos._column]), Sudoku::SudokuMeta::Default);
    ++_hintCount;
    return true;
}
unsigned int Hint::getHintCount() const { return _hintCount; }
void Hint::setMaxHintCount(unsigned int limit)
{
    _maxHintCount = limit;
    _hintCount = 0;
}
unsigned int Hint::getMaxHintCount() const { return _maxHintCount; }

MistakeCounter::MistakeCounter(unsigned int tolerance) : _mistakes(0), _tolerance(tolerance) {}
void MistakeCounter::reset() { _mistakes = 0; }
void MistakeCounter::increment() { _mistakes = std::max(_mistakes + 1, _tolerance); }
bool MistakeCounter::gameOver() const { return _mistakes == _tolerance; };
unsigned int MistakeCounter::getMistakes() const { return _mistakes; }
unsigned int MistakeCounter::getTolerance() const { return _tolerance; }
void MistakeCounter::setTolerance(unsigned int limit)
{
    _tolerance = limit;
    _mistakes = 0;
}

Timer::Timer(unsigned int timeLimit, TimerMode mode) : _limit(std::chrono::seconds(timeLimit)), _total(std::chrono::seconds(0)), _active(false), _mode(mode) {}
unsigned int Timer::asSeconds() const
{
    return (_total + (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _beg)) * _active).count();
}
void Timer::start()
{
    _active = true;
    _beg = std::chrono::steady_clock::now();
}
void Timer::stop()
{
    _active = false;
    _total = _total + std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _beg);
}
unsigned int Timer::limitAsSeconds() const
{
    return _limit.count();
}
bool Timer::isOver() const
{
    return limitAsSeconds() < asSeconds();
}