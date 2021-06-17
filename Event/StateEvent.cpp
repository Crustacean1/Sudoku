#include "StateEvent.h"

StateEvent::StateEvent(Game::GameState newState) : _state(newState) {}

void StateEvent::read(std::istream &stream){}

void StateEvent::run(Game & game)
{
    game.changeState(_state);
}