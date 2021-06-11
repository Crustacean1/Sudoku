#ifndef USERINTERFACE
#define USERINTERFACE

#include "GameModes/Game.h"
#include <unordered_map>

class Sudoku;
class EventQueue;

class Hint;
class Timer;
class MistakeCounter;
class CountdownTimer;

class UserInterface
{
private:
    EventQueue & _eventQueue;

public:
    UserInterface(EventQueue & eventQueue) : _eventQueue(eventQueue);

    virtual void initiate() = 0;

    virtual void render(Sudoku &sudoku) = 0;
    virtual void render(Timer &timer) = 0;
    virtual void render(Hint &hint) = 0;
    virtual void render(MistakeCounter &mistakeCounter) = 0;
    virtual void render(CountdownTimer &countdownTimer) = 0;

    virtual void message(const std::string &msg) = 0;

    virtual void display() = 0;

    virtual void input() = 0;

    virtual ~UserInterface() = 0;
};

#endif /*INTERFACE*/