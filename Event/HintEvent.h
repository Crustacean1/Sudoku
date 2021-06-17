#ifndef HINTEVENT
#define HINTEVENT

#include "Event.h"
#include "GameModes/Game.h"

class HintEvent : public Event
{
    SudokuCoords _coords;

public:
    HintEvent();
    HintEvent(SudokuCoords coords);
    void read(std::istream &stream);
    void run(Game &game);
};

#endif /*HINTEVENT*/