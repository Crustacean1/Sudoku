#ifndef UNDOEVENT
#define UNDOEVENT

#include "Event.h"
#include "GameModes/Game.h"

class UndoEvent : public Event
{
    public:
    UndoEvent(){}
    void read(std::istream & stream);
    void run(Game & game);
};

#endif /*UNDOEVENT*/