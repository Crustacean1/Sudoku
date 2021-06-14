#include "BasicGame.h"
#include "SudokuGenerator/SudokuGenerator.h"
#include "UserInterfaces/UserInterface.h"

BasicGame::BasicGame(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &queue) : Game(interface, queue), hints(3), _eventQueue(queue)
{
}
BasicGame::~BasicGame() {}
void BasicGame::applyMove(Move &move)
{
    if (_baseSudoku[move._pos] == 0)
    {
        return;
    }
    _sudoku.applyMove(move);
    _moves.push_back(move);
}
void BasicGame::retractMove()
{
    auto &move = _moves.getRoot()->prev()->_value;
    _sudoku.retractMove(move);
    _moves.pop_back();
}
void BasicGame::askForHint(Coordinates coords)
{
}
void BasicGame::init()
{
    SudokuGenerator generator(2);
    _baseSudoku = _sudoku = _filledSudoku = generator.generate();
    _state = Play;
    std::cout << "done" << std::endl;
}
void BasicGame::gameLoop()
{
    timer.start();
    while (_state == Game::GameState::Pause || _state == Game::GameState::Play)
    {
        _interface.input();
        _interface.clear();
        _interface.render(*this);
        _interface.display();
    }
}