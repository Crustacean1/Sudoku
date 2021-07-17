#include "Message.h"
#include "Button.h"
#include <iostream>
sf::Font Text::getFont(const std::string& fname)
{
    sf::Font font;
    font.loadFromFile(fname);
    return font;
}
sf::Font Text::__defaultFont = Text::getFont("font.ttf");

Text::Text(const std::string &str)
{
    _text.setFont(__defaultFont);
    _text.setCharacterSize(20);
    setString(str);
}
void Text::setString(const std::string &str)
{
    _text.setString(str);
    auto bbox = _text.getGlobalBounds();
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
Text::~Text()
{}
Message::Message(const std::string &content, sf::RenderWindow &window) : Layout<Vertical>(sf::IntRect(0,0,0,0), std::unique_ptr<Drawable>(new Text(content)),
                                                                                          std::unique_ptr<BaseButton>(new Button(sf::IntRect(0, 0, 100, 50), (_buttonTexture.loadFromFile("OKbutton.png"), _buttonTexture), this, &Message::accept))),
                                                                         _accepted(false)
{
    auto bbox = _innerBoundingBox;
    bbox.width *= 1.5;
    bbox.height *= 1.5;
    _outerBoundingBox = bbox;
    computeInnerBounds();
    adjustPosition();

    setPosition((sf::Vector2f)(window.getSize()/2u));


    _background.setSize(sf::Vector2f(bbox.width, bbox.height));
    _background.setOrigin(sf::Vector2f(bbox.width, bbox.height) / 2.f);
    _background.setFillColor(sf::Color(100,100,100));
    _background.setPosition(getPosition());

    _buttonTexture.loadFromFile("OKbutton.png");
}
void Message::render(sf::RenderWindow &window)
{
    window.draw(_background);
    Layout<Vertical>::render(window);
}
void Message::accept()
{
    _accepted = true;
}
bool Message::isAccepted() { return _accepted; }