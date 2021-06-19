#include "Rectangle.h"
#include <random>
using namespace GUI;

std::default_random_engine Rectangle::__engine(2137);

Rectangle::Rectangle(sf::Vector2f position, sf::Vector2f size) : _shape(size), _localPosition(position), _globalPosition(sf::Vector2f(0, 0))
{
    _shape.setPosition(_localPosition + _globalPosition);
    _shape.setOrigin(size/2.f);
    std::uniform_int_distribution<unsigned int> dist(0,255);
    _shape.setFillColor(sf::Color(dist(__engine),dist(__engine),dist(__engine)));
}
sf::IntRect Rectangle::getBoundingBox()
{
    return (sf::IntRect)_shape.getLocalBounds();
}
void Rectangle::setLocalPosition(sf::Vector2f position)
{
    _localPosition = position;
    _shape.setPosition(_localPosition + _globalPosition);
}
void Rectangle::setGlobalPosition(sf::Vector2f position)
{
    _globalPosition = position;
    _shape.setPosition(_localPosition + _globalPosition);
}
void Rectangle::render(sf::RenderWindow &window)
{
    window.draw(_shape);
}