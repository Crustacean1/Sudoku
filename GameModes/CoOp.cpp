#include "CoOp.h"
#include "UserInterfaces/UserInterface.h"
#include "SudokuGenerator/SudokuGenerator.h"
using boost::asio::ip::tcp;

CoOpGame::CoOpGame(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue) : Game(interface, eventQueue, messageQueue, "Co Op")
{
    _hint.setMaxHintCount(0);
    _counter.setTolerance(6);
    _timer._mode = Timer::TimerMode::Countdown;
    _timer.setLimit(600);
}
void CoOpGame::init()
{
    SudokuGenerator generator(3);
    std::tie(_filledSudoku, _baseSudoku) = generator.generate();
    _sudoku = _baseSudoku;
    _state = Play;
    _timer.start();

    std::cout << "input role and ip: " << std::endl;
    std::string ip, connection;
    std::cin >> connection >> ip;

    if (connection == "client")
    {
        auto client = new NetworkClient(_io, ip);
        _networkModule = new NetworkModule(_io, client);
    }
    else if (connection == "host")
    {
        auto server = new NetworkServer(_io, this, &CoOpGame::waitForConnection);
        _networkModule = new NetworkModule(_io, server);
    }

    _networkInterface = new NetworkInterface(_eventQueue, _messageQueue, *_networkModule);
    _networkInterface->initiate(*this);

    _interface.initiate(*this);

    _stateCallbacks[static_cast<unsigned int>(GameState::Pause)] = (StateCallback)&CoOpGame::pause;
    _stateCallbacks[static_cast<unsigned int>(GameState::Play)] = (StateCallback)&CoOpGame::pause;
}
void CoOpGame::waitForConnection(const boost::system::error_code &code)
{
}
void CoOpGame::applyMove(Move &move)
{
    if (_state == Pause)
    {
        return;
    }
    _counter.check(_filledSudoku, move);
    if (move._meta == Sudoku::SudokuMeta::Invalid)
    {
        return;
    }
    if (move._meta == Sudoku::SudokuMeta::Retract && !_moves.empty())
    {
        move = _moves.getRoot()->prev()->_value;
        move._meta = Sudoku::SudokuMeta::Retract;
    }
    _sudoku.applyMove(move);
    if (!move._remote)
    {
        _networkModule->sendMove(move);
    }
    if (move._meta == Sudoku::SudokuMeta::Retract)
    {
        if (_moves.empty())
        {
            return;
        }
        _moves.pop_back();
        return;
    }
    _moves.push_back(move);
}
void CoOpGame::retractMove()
{
}
void CoOpGame::askForHint(SudokuCoords coords)
{
    _messageQueue.push_back("maximum hint count exceeded");
}
void CoOpGame::pause(GameState newState)
{
    _messageQueue.push_back("game can't be paused in multiplayer mode");
}
void CoOpGame::checkExitConditions()
{
    if (_sudoku.isComplete() || _counter.gameOver())
    {
        changeState(GameState::GameOver);
    }
}
void CoOpGame::gameLoop()
{
    _timer.start();
    while (_state == Game::GameState::Pause || _state == Game::GameState::Play)
    {
        _interface.clear();
        _interface.render(*this);
        _interface.display();
        _interface.input();
        flushEvents(this);
        checkExitConditions();
    }
}