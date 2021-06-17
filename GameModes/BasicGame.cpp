#include "BasicGame.h"
#include "SudokuGenerator/SudokuGenerator.h"
#include "UserInterfaces/UserInterface.h"

BasicGame::BasicGame(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue) : Game(interface, eventQueue, messageQueue), hints(3)
{
}
BasicGame::~BasicGame() {}
void BasicGame::applyMove(Move &move)
{
    _sudoku.applyMove(move);
    _moves.push_back(move);
}
void BasicGame::retractMove()
{
    auto &move = _moves.getRoot()->prev()->_value;
    _sudoku.retractMove(move);
    _moves.pop_back();
}
void BasicGame::askForHint(SudokuCoords coords)
{
}
void BasicGame::init()
{
    SudokuGenerator generator(3);
    std::tie(_filledSudoku, _baseSudoku) = generator.generate();
    _sudoku = _baseSudoku;
    _state = Play;
    _timer.start();
}
void BasicGame::gameLoop()
{
    timer.start();
    while (_state == Game::GameState::Pause || _state == Game::GameState::Play)
    {
        _interface.clear();
        _interface.render(*this);
        _interface.display();
        _interface.input();
        flushEvents(this);
    }
}