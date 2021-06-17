#include "Game.h"
#include "Event/Event.h"

Hint Game::getHint() { return _hint; }
Timer Game::getTimer() { return _timer; }
MistakeCounter Game::getCounter() { return _counter; }
Sudoku &Game::getSudoku() { return _sudoku; }
std::string Game::getModeName() { return _modeName; }
Game::GameState Game::getState() { return _state; }

bool Game::callbackPlaceholder(GameState newState) { return true; }
Game::Game(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue,std::string modeName) : _interface(interface), _eventQueue(eventQueue), _messageQueue(messageQueue),
                                                                                                                              _state(Loading),
                                                                                                                              _modeName(modeName),
                                                                                                                              _stateCallbacks{
                                                                                                                                  &Game::callbackPlaceholder,
                                                                                                                                  &Game::callbackPlaceholder,
                                                                                                                                  &Game::callbackPlaceholder,
                                                                                                                                  &Game::callbackPlaceholder,
                                                                                                                                  &Game::callbackPlaceholder,
                                                                                                                                  &Game::callbackPlaceholder,
                                                                                                                              }
{
}

void Game::changeState(GameState newState)
{
    if ((this->*_stateCallbacks[static_cast<unsigned char>(newState)])(newState))
    {
        _state = newState;
    }
}
void Game::flushEvents(Game *game)
{
    game->_eventQueue.iterate([&game](const std::unique_ptr<Event> &event)
                              { event->run(*game); });
    game->_eventQueue.clear();
}