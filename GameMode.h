#ifndef GAMEMODE
#define GAMEMODE

class Interface;
class Leaderboard;

class GameMode
{
public:
    enum GameState
    {
        Play,
        Pause,
        Victory,
        GameOver,
    };

private:
protected:
    Interface &_interface;

    GameState _state;

    GameMode(Interface &interface);

public:
    virtual void gameLoop();
    virtual void updateLeaderboard(Leaderboard &leaderboard);
    virtual ~GameMode();
};

#endif /*GAMEMODE*/