#ifndef GAMEMODE
#define GAMEMODE

#include "Sudoku/Sudoku.h"
#include "LinkedList/LinkedList.h"
#include "Misc.h"
#include "Move/Move.h"
#include <memory>

class UserInterface;
class Event;
class Move;
class Leaderboard;

/**
 * Abstract class representing game mode
 * It's responsible for modyfing sudoku board and controling game state
 */
class Game
{
public:
    /**
     * Enum representing state of game
    */
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
    /**
     * Pointer to interface used by game mode
     */
    UserInterface& _interface;

    GameState _state;

    /**
     * Generated sudoku, with gaps
     */
    Sudoku _baseSudoku;
    /** Sudoku in progress*/
    Sudoku _sudoku;
    /** Generated filled sudoku*/
    Sudoku _filledSudoku;

    /** List of moves */
    LinkedList<Move> _moves;

    Hint _hint;
    Timer _timer;
    MistakeCounter _counter;
    CountdownTimer _countdownTimer;

public:
    template <typename T>
    Game(UserInterface &interface, LinkedList<T> &eventQueue) : _interface(interface), _state(Loading) {}

    /** Applies move to sudoku*/
    virtual void applyMove(Move &move) = 0;
    /** Undoes a last move*/
    virtual void retractMove() = 0;
    /** Reveals one hidden cell*/
    virtual void askForHint(Coordinates coords) = 0;

    Hint getHint() { return _hint; }
    Timer getTimer() { return _timer; }
    MistakeCounter getCounter() { return _counter; }
    CountdownTimer getCountdownTimer() { return _countdownTimer; }
    Sudoku &getSudoku() { return _sudoku; }

    virtual void init() = 0;
    virtual void gameLoop() = 0;
    virtual ~Game() {}
};

#endif /*GAMEMODE*/