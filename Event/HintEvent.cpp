#include "HintEvent.h"

HintEvent::HintEvent() {activate();}
HintEvent::HintEvent(SudokuCoords coords) { _data.move._coords = coords;activate(); }
void HintEvent::read(std::istream &stream)
{
    _data.move._coords._row = readInt(stream);
    _data.move._coords._column = readInt(stream);
    activate();
}
void HintEvent::run(Game &game)
{
    if (active())
    {
        game.askForHint(_data.move._coords);
        deactivate();
    }
}