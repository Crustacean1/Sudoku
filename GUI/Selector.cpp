#include "Selector.h"
#include "Rectangle.h"

Selector::Selector(sf::Vector2f dimensions, sf::RectangleShape *digits, unsigned char count) : HorizontalLayout(sf::IntRect(0, 0, dimensions.x, 0))
{
    
    for (int i = 1; i < count; ++i)
    {
        addChild(std::unique_ptr<Drawable>(new Rectangle(digits[i])));
    }
}