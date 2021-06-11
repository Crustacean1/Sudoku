#ifndef EVENT
#define EVENT

class Game;

class Event
{
private:
    Event(const Event&) = delete;
    Event & operator=(const Event&) = delete;
public:
    Event(){}
    virtual void run(Game & game) = 0;
    virtual ~Event() = 0;
};

#endif /*EVENT*/