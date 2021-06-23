#include "CoOp.h"

using boost::asio::ip::tcp;

CoOpGame::CoOpGame(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue) : Game(interface, eventQueue, messageQueue, "Co Op"),_socket(_io)
{
    _hint.setMaxHintCount(0);
    _counter.setTolerance(0);
}
void CoOpGame::init()
{
    std::cout<<"input other players ip: "<<std::endl;
    std::string ip;
    std::cin>>ip;
    tcp::resolver resolver(_io);
    tcp::resolver::endpoint_type enpoints = 
    resolver.resolve()
}