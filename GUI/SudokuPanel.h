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
    sf::Texture _pauseTexture;
    sf::Texture _undoTexture;
    sf::Texture _hintTexture;

    float _size;
    void generateDigitTexture(unsigned char root);
    void loadTextures();
    LinkedList<std::unique_ptr<Event>> &_eventQueue;

    Event::EventType _eType;

    void pause();
    void undo();
    void hint();

    void postEvent(sf::Vector2i pos,unsigned char numbe);
    void postEvent();

    SudokuBoard * _sudokuBoard;
    Selector * _selector;
    Layout<Horizontal> * _buttonStrip;

    Sudoku &_sudoku;

public:
    SudokuPanel(sf::RenderWindow &window, Sudoku &sudoku, LinkedList<std::unique_ptr<Event>> &eventQueue);
    bool action(const sf::Vector2i &position, const sf::Event &type);
};

#endif /*SUDOKUPANEL*/