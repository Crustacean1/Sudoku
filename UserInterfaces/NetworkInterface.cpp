#include "NetworkInterface.h"
#include <boost/bind.hpp>
#include "GameModes/Game.h"
#include "Event/MoveEvent.h"
#include "GameModes/NetworkModule.h"
NetworkInterface::NetworkInterface(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue, NetworkModule &module) : UserInterface(eventQueue, messageQueue), _networkModule(module)
{
}

void NetworkInterface::clear() {}
void NetworkInterface::display() {}
void NetworkInterface::render(Game &game) {}

void NetworkInterface::initiate(Game &game)
{
    _networkModule.setMoveCallback(this, &NetworkInterface::receiveMoves);
}
void NetworkInterface::input()
{
}
void NetworkInterface::receiveMoves(Move &move)
{
    move._remote = true;
    _eventQueue.push_back(std::unique_ptr<Event>(new MoveEvent(move._pos._row, move._pos._column, move._number, move._meta)));
}