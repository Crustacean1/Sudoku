#ifndef NETWORKMODULE
#define NETWORKMODULE

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include "Move/Move.h"
#include "Sudoku/Sudoku.h"
#include <chrono>
#include <thread>

using boost::asio::ip::tcp;

class NetworkClient
{
    tcp::resolver::results_type _endpoints;

public:
    NetworkClient(boost::asio::io_context &io, std::string ip)
    {
        tcp::resolver resolver(io);
        _endpoints = resolver.resolve(ip, "7312");
    }
    void connect(tcp::socket &socket)
    {
        boost::asio::connect(socket, _endpoints);
    }
};
template <typename T>
class NetworkServer
{
    typedef void (T::*Callback)(const boost::system::error_code &);
    Callback _callback;
    T *_t;
    boost::asio::io_context &_io;

public:
    NetworkServer(boost::asio::io_context &io, T *t, Callback callback) : _callback(callback), _t(t), _io(io)
    {
    }
    void connect(tcp::socket &socket)
    {
        tcp::acceptor acceptor(_io, tcp::endpoint(tcp::v4(), 7312));
        acceptor.accept(socket);
    }
};

class NetworkModule
{
    tcp::socket _socket;
    union Buffer
    {
        Move move;
        unsigned char raw[sizeof(Move)];
        Buffer() : move(SudokuCoords(0, 0), 0, Sudoku::SudokuMeta::Empty) {}
        ~Buffer() {}
    };
    Buffer _buffer;

public:
    template <typename T>
    NetworkModule(boost::asio::io_context &io, T *t) : _socket(io)
    {
        t->connect(_socket);
    }
    void sendMove(Move &move)
    {
        boost::asio::async_write(_socket, boost::asio::buffer(_buffer.raw, sizeof(Move)), boost::bind(&NetworkModule::sendPlaceholder, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    template <typename T>
    void setMoveCallback(T *t, void (T::*f)(Move &))
    {
        boost::asio::async_read(_socket, boost::asio::buffer(_buffer.raw, sizeof(Move)), boost::bind(&NetworkModule::receiveMove<T>, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, t, f));
    }
    template <typename T>
    void receiveMove(const boost::system::error_code &code, uint32_t bytes_transferred, T *t, void (T::*f)(Move &))
    {
        if (!code)
        {
            if (bytes_transferred != sizeof(Move))
            {
                std::cerr << "invalid packet size" << std::endl;
            }
            ((t)->*(f))(_buffer.move);
        }
    }
    static void sendPlaceholder(const boost::system::error_code &code, uint32_t bytes_transffered)
    {
    }
};

#endif /*NETWORKMODULE*/