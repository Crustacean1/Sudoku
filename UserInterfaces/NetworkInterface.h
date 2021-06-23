#ifndef NETWORKINTERFACE
#define NETWORKINTERFACE

#include "UserInterface.h"
#include "GameModes/NetworkModule.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class NetworkInterface : public UserInterface
{
    NetworkModule &_networkModule;
    void receiveMoves(Move & move);
public:
    NetworkInterface(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue,NetworkModule & module);
    void initiate(Game &game);
    void clear();
    void render(Game &game);
    void display();
    void input();
};

#endif /*NETWORKINTERFACE*/