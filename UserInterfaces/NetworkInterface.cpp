#include "NetworkInterface.h"
#include <boost/bind.hpp>
#include "GameModes/Game.h"

void NetworkInterface::accept(Game *game, const boost::system::error_code &error)
{
    game->getState() = Game::GameState::Play;
}

NetworkInterface::NetworkInterface(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue, boost::asio::io_context &io) : UserInterface(eventQueue, messageQueue), _io(io), _socket(_io)
{
}

void NetworkInterface::clear() {}
void NetworkInterface::display() {}
void NetworkInterface::render(Game &game) {}

void NetworkInterface::initiate(Game &game)
{
    tcp::acceptor acceptor(_io, tcp::endpoint(tcp::v4(), 2137));
    acceptor.async_accept(_socket, boost::bind(&NetworkInterface::accept, this, &game, boost::asio::placeholders::error));
}
void NetworkInterface::input()
{
}