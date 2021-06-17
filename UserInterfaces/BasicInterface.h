#ifndef BASICINTERFACE
#define BASICINTERFACE

#include <memory>
#include <unordered_map>
#include "UserInterface.h"
#include "Event/Event.h"

class BasicInterface : public UserInterface
{
private:
    static char _sudokuTiles[2][25];
    static char _metaMarkers[2][6][8];
    static std::unordered_map<std::string, Event::EventType> _events;
    LinkedList<std::unique_ptr<Event>> &_eventQueue;

    void render(const Timer &timer);
    void render(const Hint &hint);
    void render(const MistakeCounter &counter);
    void render(Sudoku &sudoku, Game::GameState state);
    void renderMessages();

public:
    BasicInterface(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue);

    void initiate();

    void render(Game &game);

    void message(const std::string &msg);

    void clear();

    void display();

    void input();

    ~BasicInterface();
};

#endif /*BASICINTERFACE*/