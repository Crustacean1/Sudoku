#include "Button.h"

BaseButton::BaseButton(sf::IntRect size, sf::Texture &texture) : _shape(sf::Vector2f(size.width, size.height))
{
    _shape.setPosition(sf::Vector2f(size.left, size.top));
    _shape.setOrigin(sf::Vector2f(size.width, size.height) / 2.f);
    _shape.setTexture(&texture);
}
void BaseButton::render(sf::RenderWindow &window)
{
    window.draw(_shape);
}
void BaseButton::setPosition(const sf::Vector2f &position)
{
    _shape.setPosition(position);
}
sf::Vector2f BaseButton::getPosition() const
{
    return _shape.getPosition();
}
sf::IntRect BaseButton::getBoundingBox() const
{
    return static_cast<sf::IntRect>(_shape.getGlobalBounds());
}
bool BaseButton::action(const sf::Vector2i &position, const sf::Event &type)
{
    if (getBoundingBox().contains(position) && type.type == sf::Event::EventType::MouseButtonPressed)
    {
        execute();
        return true;
    }
    return false;
}
void BaseButton::setTexture(sf::Texture &tex)
{
    _shape.setTexture(&tex);
}