#ifndef BASICGAME
#define BASICGAME

#include "Game.h"
#include "Event/Event.h"
#include "GameModes/Misc.h"
#include <memory>

class BasicGame : public Game
{
    bool stopTimer(GameState state);
    bool restartTimer(GameState state);
    void checkExitConditions();

public:
    BasicGame(UserInterface &interface, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue);
    void init();
    void applyMove(Move &move);
    void retractMove();
    void askForHint(SudokuCoords coords);

    void gameLoop();
    void updateLeaderboard(Leaderboard &leaderboard) {}
    ~BasicGame();
};

#endif /*BASICGAME*/