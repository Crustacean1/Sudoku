#ifndef COOP
#define COOP

#include "Game.h"
#include <boost/asio.hpp>
//UserInterface &interface
//UserInterface&interface
using boost::asio::ip::tcp;

class CoOpGame : public Game
{
    boost::asio::io_context _io;
    tcp::socket _socket;
public:
    CoOpGame(UserInterface&interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue);
    void applyMove(Move &move);
    void retractMove();
    void askForHint(SudokuCoords coords);
    void init();
    void gameLoop();
};

#endif /*COOP*/