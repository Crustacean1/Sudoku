#include "Rectangle.h"
#include <random>

std::default_random_engine Rectangle::__engine(2137);

Rectangle::Rectangle(sf::Vector2f position, sf::Vector2f size) : _shape(size)
{

    _shape.setPosition(position);

    _shape.setOrigin(sf::Vector2f(_shape.getGlobalBounds().width / 2, _shape.getGlobalBounds().height / 2));
    std::uniform_int_distribution<unsigned int> dist(0, 255);
    _shape.setFillColor(sf::Color(dist(__engine), dist(__engine), dist(__engine)));
}

Rectangle::Rectangle(const sf::RectangleShape &shape)
{
    _shape = shape;
}
sf::IntRect Rectangle::getBoundingBox() const
{
    return (sf::IntRect)_shape.getLocalBounds();
}
void Rectangle::setPosition(const sf::Vector2f &position)
{
    _shape.setPosition(position);
}
sf::Vector2f Rectangle::getPosition() const { return _shape.getPosition(); }

void Rectangle::render(sf::RenderWindow &window)
{
    window.draw(_shape);
}