#ifndef COOP
#define COOP

#include "Game.h"
#include <boost/asio.hpp>
#include "NetworkModule.h"
#include "UserInterfaces/NetworkInterface.h"

using boost::asio::ip::tcp;

class CoOpGame : public Game
{
    boost::asio::io_context _io;
    NetworkModule *_networkModule;
    void pause(GameState state);
    void checkExitConditions();
    void waitForConnection(const boost::system::error_code &code);
    NetworkInterface *_networkInterface;

public:
    CoOpGame(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue);
    void applyMove(Move &move);
    void retractMove();
    void askForHint(SudokuCoords coords);
    void init();
    void gameLoop();
};

#endif /*COOP*/