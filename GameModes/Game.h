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
    UserInterface &_interface;

    LinkedList<std::unique_ptr<Event>> &_eventQueue;
    LinkedList<std::string> &_messageQueue;

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
    std::string _modeName;

    bool callbackPlaceholder(GameState);
    typedef bool (Game::*StateCallback)(GameState);
    StateCallback _stateCallbacks[6];

public:
    Game(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue, std::string modeName = "default mode");

    /** Applies move to sudoku*/
    virtual void applyMove(Move &move) = 0;
    /** Undoes a last move*/
    virtual void retractMove() = 0;
    /** Reveals one hidden cell*/
    virtual void askForHint(SudokuCoords coords) = 0;

    Hint &getHint();
    Timer &getTimer();
    MistakeCounter &getCounter();
    Sudoku &getSudoku();
    std::string getModeName();
    GameState &getState();

    void changeState(GameState newState);
    static void flushEvents(Game *game);

    virtual void init() = 0;
    virtual void gameLoop() = 0;
    virtual ~Game() {}
};

#endif /*GAMEMODE*/