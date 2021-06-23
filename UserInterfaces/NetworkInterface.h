#ifndef NETWORKINTERFACE
#define NETWORKINTERFACE

#include "UserInterface.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class NetworkInterface : public UserInterface
{
    boost::asio::io_context &_io;
    tcp::socket _socket;
    void accept(Game *game, const boost::system::error_code &error);

public:
    NetworkInterface(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue, boost::asio::io_context &io);
    void initiate(Game &game);
    void clear();
    void render(Game &game);
    void display();
    void input();
};

#endif /*NETWORKINTERFACE*/