#include "Misc.h"

Timer::Timer() : _active(false) {}
void Timer::start()
{
    _beg = std::chrono::steady_clock::now();
    _active = true;
}
bool Timer::isActive() const { return _active; }
unsigned int Timer::asSeconds() const { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _beg).count(); }

Hint::Hint(unsigned int hintCount) : _hintCount(0), _maxHintCount(hintCount) {}
bool Hint::uncover(Coordinates pos, Sudoku &filledSudoku, Sudoku &sudoku)
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

CountdownTimer::CountdownTimer(unsigned int timeLimit) : _limit(std::chrono::seconds(timeLimit)), _active(false) {}
unsigned int CountdownTimer::asSeconds() const
{
    return (_limit - std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _beg)).count();
}
void CountdownTimer::start()
{
    _active = true;
    _beg = std::chrono::steady_clock::now();
}
unsigned int CountdownTimer::limitAsSeconds() const
{
    return _limit.count();
}
bool CountdownTimer::isOver() const
{
    return limitAsSeconds() < asSeconds();
}