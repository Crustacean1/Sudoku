#ifndef SELECTOR
#define SELECTOR

#include "Drawable.h"
#include "SudokuBoard.h"
#include "HorizontalLayout.h"

class BasicGui;

class Selector : public HorizontalLayout
{
public:
    Selector(sf::Vector2f dimensions, sf::RectangleShape *digits, unsigned char count);
};

#endif /*SELECTOR*/