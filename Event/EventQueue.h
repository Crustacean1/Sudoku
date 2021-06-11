#ifndef EVENTQUEUE
#define EVENTQUEUE

#include "Event.h"
#include "LinkedList/LinkedList.h"
#include <memory>

class Game;

class EventQueue
{
private:
    LinkedList<std::unique_ptr<Event>> _eventQueue; 
public:
    EventQueue();

    void push_back(std::unique_ptr<Event> &&event);
    void pop(Game & game);

    void run(Game & game);
    void clear();

    unsigned int size();

    ~EventQueue();
};


#endif /*EVENTQUEUE*/