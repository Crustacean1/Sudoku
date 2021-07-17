#ifndef SUDOKUPANEL
#define SUDOKUPANEL

#include "SudokuBoard.h"
#include "Selector.h"
#include "Sudoku/Sudoku.h"
#include "Layout.h"
#include "Event/Event.h"

class SudokuPanel : public Layout<Vertical>
{
    void generateDigitTexture(unsigned char root);
    void loadTextures();

    void pause();
    void undo();
    void hint();

    void postEvent(sf::Vector2i pos, unsigned char numbe);
    void postEvent();

    sf::RenderTexture _digitsTexture;
    sf::Texture _pauseTexture;
    sf::Texture _resumeTexture;
    sf::Texture _undoTexture;
    sf::Texture _hintTexture;

    float _size;

    LinkedList<std::unique_ptr<Event>> &_eventQueue;
    LinkedList<std::string> &_messageQueue;

    Event::EventType _eType;

    SudokuBoard *_sudokuBoard;
    Selector *_selector;
    Layout<Horizontal> *_buttonStrip;

    Sudoku &_sudoku;
    Game::GameState &_state;

    char _selectedNumber;

public:
    SudokuPanel(sf::RenderWindow &window, Sudoku &sudoku, Game::GameState &state, LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue);
    bool action(const sf::Vector2i &position, const sf::Event &type);
    ~SudokuPanel();
};

#endif /*SUDOKUPANEL*/