#include "CoOp.h"

using boost::asio::ip::tcp;

CoOpGame::CoOpGame(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue) : Game(interface, eventQueue, messageQueue, "Co Op")
{
    _hint.setMaxHintCount(0);
    _counter.setTolerance(0);
}
void CoOpGame::init()
{
    std::cout << "input other players ip: " << std::endl;
    std::string ip;
    std::cin >> ip;

    auto client = new NetworkClient(_io, ip);
    _networkModule = new NetworkModule(_io, client);
    delete client;
    _stateCallbacks[static_cast<unsigned int>(GameState::Pause)] = (StateCallback)&BasicGame::stopTimer;
    _stateCallbacks[static_cast<unsigned int>(GameState::Play)] = (StateCallback)&BasicGame::restartTimer;
    
}
void CoOpGame::applyMove(Move &move)
{
    if (_state == Pause)
    {
        return;
    }
    _counter.check(_filledSudoku, move);
    _sudoku.applyMove(move);
    _moves.push_back(move);
}
void CoOpGame::retractMove()
{
    if (_state == Pause)
    {
        return;
    }
    if (_moves.getRoot() == nullptr)
    {
        return;
    }
    auto &move = _moves.getRoot()->prev()->_value;

    _sudoku.retractMove(move);
    _moves.pop_back();
}
void CoOpGame::askForHint(SudokuCoords coords)
{
    _messageQueue.push_back("maximum hint count exceeded");
}
void CoOpGame::gameLoop()
{
    _messageQueue.push_back("game can't be paused in multiplayer mode");
}