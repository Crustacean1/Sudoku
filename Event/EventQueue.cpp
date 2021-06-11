#include "EventQueue.h"

EventQueue::EventQueue() {}

void EventQueue::push_back(std::unique_ptr<Event> &&event)
{
    _eventQueue.push_back(std::move(event));
}
void EventQueue::pop(Game &game)
{
    _eventQueue.getRoot()->_value->run(game);
    _eventQueue.pop_front();
}
void EventQueue::run(Game &game)
{
    while (_eventQueue.getRoot() != nullptr)
    {
        _eventQueue.getRoot()->_value->run(game);
        _eventQueue.pop_front();
    }
}
void EventQueue::clear()
{
    while (_eventQueue.getRoot() != nullptr)
    {
        _eventQueue.pop_front();
    }
}
unsigned int EventQueue::size()
{
    if (_eventQueue.getRoot() == nullptr)
    {
        return 0;
    }
    return _eventQueue.getRoot()->count();
}