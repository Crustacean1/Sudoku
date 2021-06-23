#include "Misc.h"
#include <iostream>
#include "Move/Move.h"

Hint::Hint(unsigned int hintCount) : _hintCount(0), _maxHintCount(hintCount) {}
bool Hint::uncover(SudokuCoords pos, Sudoku &filledSudoku, Sudoku &sudoku)
{
    std::cout << _hintCount << std::endl;
    if (_hintCount == _maxHintCount)
    {
        std::cout << "???" << std::endl;
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
std::string Hint::write() const
{
    if (_maxHintCount == 0)
    {
        return "";
    }
    //std::cout<<std::to_string(_maxHintCount - _hintCount)<<std::endl;
    return "Hints left: " + std::to_string(_maxHintCount - _hintCount) + "/" + std::to_string(_maxHintCount);
}

MistakeCounter::MistakeCounter(unsigned int tolerance) : _mistakes(0), _tolerance(tolerance) {}
void MistakeCounter::reset() { _mistakes = 0; }

bool MistakeCounter::check(Sudoku &sudoku, Move &move)
{
    if (move._meta == Sudoku::SudokuMeta::Note || move._meta == Sudoku::SudokuMeta::Retract)
    {
        return true;
    }
    if (Sudoku::getNumber(sudoku[move._pos._row][move._pos._column]) != move._number && move._meta != Sudoku::SudokuMeta::Note)
    {
        _mistakes = std::min(_mistakes + 1, _tolerance);
        move._meta = Sudoku::SudokuMeta::Invalid;
        return false;
    }
    return true;
}
bool MistakeCounter::gameOver() const { return (_mistakes == _tolerance && _tolerance != 0); };
unsigned int MistakeCounter::getMistakes() const { return _mistakes; }
unsigned int MistakeCounter::getTolerance() const { return _tolerance; }
void MistakeCounter::setTolerance(unsigned int limit)
{
    _tolerance = limit;
    _mistakes = 0;
}
std::string MistakeCounter::write() const
{
    if (_tolerance == 0)
    {
        return "";
    }
    return "Mistakes: " + std::to_string(_mistakes) + "/" + std::to_string(_tolerance);
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
    return ((_mode == Clock) || limitAsSeconds() < asSeconds());
}
std::string Timer::write() const
{
    auto time1 = asSeconds();
    auto time2 = limitAsSeconds();
    switch (_mode)
    {
    case Countdown:
        return "Time left: " + std::to_string((time2 - time1) / 60) + ":" + std::to_string((time2 - time1) % 60) + "/" + std::to_string(time2 / 60) + ":" + std::to_string(time2 % 60);
    case Clock:
        return "Time: " + std::to_string(time1 / 60) + ":" + std::to_string(time1 % 60);
    }
    return "";
}
void Timer::setLimit(unsigned int seconds)
{
    _limit = std::chrono::seconds(seconds);
}
