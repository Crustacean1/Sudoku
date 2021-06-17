#ifndef HINTEVENT
#define HINTEVENT

#include "Event.h"
#include "GameModes/Game.h"

class HintEvent : public Event
{
    SudokuCoords _coords;

public:
    HintEvent(){}
    HintEvent(SudokuCoords coords) : _coords(coords){}
    void read(std::istream &stream)
    {
        _coords._row = readInt(stream);
        _coords._column = readInt(stream);
    }
    void run(Game &game)
    {
        game.askForHint(_coords);
    }
};

#endif /*HINTEVENT*/