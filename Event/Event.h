#ifndef EVENT
#define EVENT

#include <iostream>
class Game;

/** Base class , instances are meant to have varying constructors and act as lambda captures*/
class Event
{
private:
    bool _active;
    Event(const Event &) = delete;
    Event &operator=(const Event &) = delete;
protected:
    uint8_t readInt(std::istream &stream);
    void activate();
    void deactivate();

public:
    enum class EventType:unsigned char
    {
        MoveEvent,
        NoteEvent,
        UndoEvent,
        HintEvent,
        PauseEvent,
        ResumeEvent,
        ExitEvent
    };
    Event() : _active(false) {}

    /** virtual method, reads parameters from stream*/
    virtual void read(std::istream &stream) =0;
    /** virtual method, executes class specific action on Game object*/
    virtual void run(Game &game) = 0;
    /**_active getter*/
    bool active();
    /***/
    static Event * createEvent(EventType eventType);

    ~Event();
};

#endif /*EVENT*/