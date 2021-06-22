#include "StateEvent.h"

StateEvent::StateEvent(Game::GameState newState){_data.state._state = newState;}

void StateEvent::read(std::istream &stream){}

void StateEvent::run(Game & game)
{
    game.changeState(_data.state._state);
}