#ifndef SELECTOR
#define SELECTOR

#include "GUI/Drawable.h"
#include "SudokuBoard.h"
#include "Sudoku/Sudoku.h"
#include "GUI/Layout.h"

class BasicGui;

class Selector : public Drawable
{
public:
    Selector(Sudoku &sudoku, sf::RenderTexture&digits);

    void render(sf::RenderWindow & window);
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f & position);
    sf::IntRect getBoundingBox() const;
};

#endif /*SELECTOR*/