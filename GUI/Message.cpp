#include "Message.h"
#include "Button.h"

Text::Text(const std::string &str)
{
    _text.setString(str);
}
void Text::setString(const std::string &str)
{
    _text.setString(str);
    auto bbox = _text.getLocalBounds();
    _text.setOrigin(sf::Vector2f(bbox.width, bbox.height) / 2.f);
}
std::string Text::getString()
{
    return _text.getString();
}

void Text::render(sf::RenderWindow &window)
{
    window.draw(_text);
}
void Text::setPosition(const sf::Vector2f &position)
{
    _text.setPosition(position);
}
sf::Vector2f Text::getPosition() const
{
    return _text.getPosition();
}
sf::IntRect Text::getBoundingBox() const
{
    return static_cast<sf::IntRect>(_text.getGlobalBounds());
}

Message::Message(LinkedList<std::string> &messageQueue, sf::IntRect size) : Layout<Vertical>(size, std::unique_ptr<Drawable>(new Text(messageQueue.getRoot()->_value)),
                                                                                             std::unique_ptr<BaseButton>(new Button(sf::IntRect(0, 0, 100, 50), (_buttonTexture.loadFromFile("OKbutton.png"), _buttonTexture), this, &Message::popQueue))),
                                                                            _messageQueue(messageQueue)
{
    auto bbox = getBoundingBox();
    bbox.width *= 1.25;
    bbox.height *= 1.25;
    _outerBoundingBox = bbox;
    computeInnerBounds();
    adjustPosition();

    _background.setSize(sf::Vector2f(bbox.width, bbox.height));
    _background.setOrigin(sf::Vector2f(bbox.width, bbox.height) / 2.f);
    _background.setPosition(getPosition());
}
void Message::popQueue()
{
    _messageQueue.pop_front();
}
void Message::render(sf::RenderWindow &window)
{
    window.draw(_background);
    Layout<Vertical>::render(window);
}