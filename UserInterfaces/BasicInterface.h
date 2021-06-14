#ifndef BASICINTERFACE
#define BASICINTERFACE

#include <memory>
#include "UserInterface.h"
#include "Event/Event.h"

class BasicInterface : public UserInterface
{
private:
    LinkedList<std::unique_ptr<Event>> &_eventQueue;

    void render(const Timer &timer);
    void render(const Hint &hint);
    void render(const MistakeCounter &counter);
    void render(const CountdownTimer &countdownTimer);
    void render(Sudoku &sudoku);

public:
    BasicInterface(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue);

    void initiate();

    void render(Game & game);

    void message(const std::string &msg);

    void clear();

    void display();

    void input();

    ~BasicInterface();
};

#endif /*BASICINTERFACE*/