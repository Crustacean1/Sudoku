#include "Label.h"

sf::Font Label::defaultFont;
bool Label::defaultFontLoaded = Label::defaultFont.loadFromFile("font.ttf");

Label::Label(Widget &widget) : _widget(widget),_size(20)
{
    _prevContent = _widget.write();
    _text.setCharacterSize(_size);
    _text.setString(_prevContent);
    _text.setFont(defaultFont);
    _text.setFillColor(sf::Color::White);
    _text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
}
void Label::render(sf::RenderWindow &window)
{
    if (_prevContent != _widget.write())
    {
        setText(_widget.write());
    }
    window.draw(_text);
}
void Label::setPosition(const sf::Vector2f &position)
{
    _text.setPosition(position);
}
sf::Vector2f Label::getPosition() const
{
    return _text.getPosition();
}
sf::IntRect Label::getBoundingBox() const
{
    return (sf::IntRect)_text.getGlobalBounds();
}
void Label::setText(const std::string &text)
{
    _prevContent = text;
    _text.setString(text);
    auto bbox = _text.getGlobalBounds();
    _text.setOrigin(bbox.width/2,bbox.height/2);
}