#ifndef INTERFACE
#define INTERFACE

#include "GameMode.h"

class Action;
class Sudoku;

class Interface
{
private:
public:
    Interface();
    virtual void display(Sudoku & sudoku,GameMode::GameState & gameState) = 0;
    virtual bool input(Action & move) = 0;

    virtual ~Interface() =0;
};



#endif /*INTERFACE*/