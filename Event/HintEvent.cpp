#include "HintEvent.h"

HintEvent::HintEvent() {}
HintEvent::HintEvent(SudokuCoords coords) : _coords(coords) {}
void HintEvent::read(std::istream &stream)
{
    _coords._row = readInt(stream);
    _coords._column = readInt(stream);
    activate();
}
void HintEvent::run(Game &game)
{
    if (active())
    {
        game.askForHint(_coords);
        deactivate();
    }
}