#include "Event.h"
#include "MoveEvent.h"
#include "HintEvent.h"
#include "UndoEvent.h"
#include "StateEvent.h"
#include <sstream>

uint8_t Event::readInt(std::istream &stream)
{
    unsigned int integer;
    stream >> integer;
    if (stream.fail())
    {
        throw std::runtime_error("Invalid character");
        stream.clear();
    }
    return integer;
}
void Event::activate()
{
    _active = true;
}
void Event::deactivate()
{
    _active = false;
}
bool Event::active()
{
    return _active;
}
Event::~Event() {}

Event *Event::createEvent(EventType eventType)
{
    switch (eventType)
    {
    case EventType::MoveEvent:
        return new MoveEvent(Sudoku::SudokuMeta::Filled);
        break;
    case EventType::NoteEvent:
        return new MoveEvent(Sudoku::SudokuMeta::Note);
        break;
    case EventType::HintEvent:
        return new HintEvent();
        break;
    case EventType::UndoEvent:
        return new UndoEvent();
    case EventType::PauseEvent:
        return new StateEvent(Game::GameState::Pause);
        break;
    case EventType::ResumeEvent:
        return new StateEvent(Game::GameState::Play);
        break;
    case EventType::ExitEvent:
        return new StateEvent(Game::GameState::GameOver);
    default:
        return nullptr;
    }
}