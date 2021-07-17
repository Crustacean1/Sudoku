#include "BasicGame.h"
#include "SudokuGenerator/SudokuGenerator.h"
#include "UserInterfaces/UserInterface.h"
#include "Sudoku/Sudoku.h"
BasicGame::BasicGame(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue) : Game(interface, eventQueue, messageQueue)
{
    _hint.setMaxHintCount(3);
    _counter.setTolerance(3);
}
BasicGame::~BasicGame() {}
void BasicGame::applyMove(Move &move)
{
    if (_state == Pause)
    {
        return;
    }
    //_counter.check(_filledSudoku, move);

    move.apply(_moves,_sudoku);
}
void BasicGame::askForHint(SudokuCoords coords)
{
    if (_state == Pause)
    {
        return;
    }
    if (!_hint.uncover(coords, _filledSudoku, _sudoku))
    {
        _messageQueue.push_back("maximum hint count exceeded");
    }
}
bool BasicGame::stopTimer(GameState state)
{
    if (_state == Pause)
    {
        _messageQueue.push_back("game already paused");
        return false;
    }
    _timer.stop();
    return true;
}
bool BasicGame::restartTimer(GameState state)
{
    if (_state == GameOver || _state == TimeOut || _state == FinalMistake)
    {
        return false;
    }
    _timer.start();
    return true;
}
void BasicGame::checkExitConditions()
{
    if (_sudoku.isComplete() || _counter.gameOver())
    {
        changeState(GameState::GameOver);
    }
}
void BasicGame::init()
{
    SudokuGenerator generator(3);
    std::tie(_filledSudoku, _baseSudoku) = generator.generate();
    _sudoku = _baseSudoku;
    _state = Play;
    _timer.start();
    _stateCallbacks[static_cast<unsigned int>(GameState::Pause)] = (StateCallback)&BasicGame::stopTimer;
    _stateCallbacks[static_cast<unsigned int>(GameState::Play)] = (StateCallback)&BasicGame::restartTimer;
    _interface.initiate(*this);
}
void BasicGame::gameLoop()
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
