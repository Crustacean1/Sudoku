#ifndef SUDOKUPANEL
#define SUDOKUPANEL

#include "SudokuBoard.h"
#include "Selector.h"
#include "Sudoku/Sudoku.h"
#include "Layout.h"
#include "Event/Event.h"

class SudokuPanel : public Layout<Vertical>
{
    sf::RenderTexture _digitsTexture;
    float _size;
    void generateDigitTexture(unsigned char root);
    LinkedList<std::unique_ptr<Event>> & _eventQueue;

    public:
    SudokuPanel(sf::RenderWindow & window,Sudoku & sudoku,LinkedList<std::unique_ptr<Event>> &eventQueue);
    bool action(const sf::Vector2i &position, const sf::Event &type);
};

#endif /*SUDOKUPANEL*/