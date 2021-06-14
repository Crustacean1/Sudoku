#ifndef MISC
#define MISC

#include <chrono>
#include "Sudoku/Sudoku.h"

/** Minor class representing timer*/
class Timer
{
    std::chrono::steady_clock::time_point _beg;
    bool _active;

public:
    Timer();
    void start();
    bool isActive() const;
    unsigned int asSeconds() const;
};
/**Minor class representing hints mechanism*/
class Hint
{
    unsigned int _hintCount;
    unsigned int _maxHintCount;

public:
    Hint(unsigned int hintCount = 0);
    bool uncover(Coordinates pos, Sudoku &filledSudoku, Sudoku &sudoku);
    unsigned int getHintCount() const;
    unsigned int getMaxHintCount() const;
};
/** Minor class representing mistake counter*/
class MistakeCounter
{
    unsigned int _mistakes;
    unsigned int _tolerance;

public:
    MistakeCounter(unsigned int tolerance = 0);
    unsigned int getMistakes() const;
    unsigned int getTolerance() const;
    void reset();
    void increment();
    bool gameOver() const;
};
/** Minor class representing countdown timer*/
class CountdownTimer
{
    std::chrono::steady_clock::time_point _beg;
    std::chrono::duration<int, std::ratio<1>> _limit;
    bool _active;

public:
    CountdownTimer(unsigned int timeLimit = 0);
    void start();
    bool isActive() const;
    bool isOver() const;
    unsigned int limitAsSeconds() const;
    unsigned int asSeconds() const;
};

#endif /*MISC*/