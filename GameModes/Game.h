#ifndef GAMEMODE
#define GAMEMODE

#include "Sudoku/Sudoku.h"
#include "LinkedNode/LinkedNode.h"
#include "Move/Move.h"

class Interface;
class EventQueue;
class Move;
class Leaderboard;

class Game
{
public:
    enum GameState
    {
        Loading,
        Play,
        Pause,
        TimeOut,      //Game Over - Time run out
        FinalMistake, //Game Over - Mistake limit exceeded
        GameOver      //Game Over - Other reason, ex. user requested so
    };

private:
protected:
    //typedef void (Game::*stateCallback)(GameState &newState);
    //stateCallback stateCallbacks[6] = {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};

    Interface &_interface;
    EventQueue & _eventQueue;

    GameState _state;

    Sudoku _baseSudoku;
    Sudoku _sudoku;
    Sudoku _filledSudoku;

    LinkedNode<Move> moves;

    Game(Interface &interface,EventQueue & eventQueue);

public:
    virtual void applyMove(Move &move) = 0;
    virtual void retractMove() = 0;
    virtual void askForHint(Coordinates coords) = 0;

    void changeState(GameState & newState);

    virtual void gameLoop();
    virtual void updateLeaderboard(Leaderboard &leaderboard);
    virtual ~Game();
};

#endif /*GAMEMODE*/