#ifndef HINTEVENT
#define HINTEVENT

#include "Event.h"
#include "GameModes/Game.h"

class HintEvent : public Event
{
public:
    HintEvent();
    HintEvent(SudokuCoords coords);
    void read(std::istream &stream);
    void run(Game &game);
};

#endif /*HINTEVENT*/