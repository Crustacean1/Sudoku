#ifndef STATEEVENT
#define STATEEVENT

#include "Event.h"
#include "GameModes/Game.h"
#include <unordered_map>

class StateEvent : public Event
{
private:
    /* data */
    Game::GameState _state;
public:
    StateEvent(Game::GameState newState);
    void read(std::istream & stream);
    void run(Game & game);
    ~StateEvent();
};


#endif /*STATEEVENT*/