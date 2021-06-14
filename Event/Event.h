#ifndef EVENT
#define EVENT

#include <iostream>
class Game;

/** Base class , instances are meant to have varying constructors and act as lambda captures*/
class Event
{
private:
    Event(const Event &) = delete;
    Event &operator=(const Event &) = delete;

public:
    Event() {}
    /** virtual method, reads parameters from stream*/
    virtual void read(std::ostream &stream);
    /** virtual method, executes class specific action on Game object*/
    virtual void run(Game &game) = 0;
    virtual ~Event() = 0;
};

#endif /*EVENT*/