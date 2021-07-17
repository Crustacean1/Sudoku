#ifndef SELECTOR
#define SELECTOR

#include "GUI/Drawable.h"
#include "SudokuBoard.h"
#include "Sudoku/Sudoku.h"
#include "GUI/Layout.h"
#include "Event/Event.h"

class BasicGui;

class Selector : public Drawable
{
    sf::VertexArray _digits;
    sf::RenderStates _renderState;

    Sudoku &_sudoku;
    float _size;
    float _texSize;
    float _gap;
    char _prev;

    void createDigits(unsigned char root);
    void assignTexture(unsigned int index, unsigned char number);

public:
    Selector(Sudoku &sudoku, sf::RenderTexture &digits);

    void render(sf::RenderWindow &window);
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &position);
    sf::IntRect getBoundingBox() const;

    char getNumber(const sf::Vector2i &position,Event::EventType & event);
    ~Selector();
};

#endif /*SELECTOR*/