#include "Selector.h"

Selector::Selector(Sudoku &sudoku, sf::RenderTexture &texture) : _renderState(&texture.getTexture()),
                                                                 _sudoku(sudoku), _size(50),
                                                                 _texSize(texture.getSize().x / (sudoku.getSize() + 2)),
                                                                 _gap(2), _prev(0)
{
    createDigits(sudoku.getRootSize());
    _renderState.transform = sf::Transform::Identity;
}

void Selector::assignTexture(unsigned int index, unsigned char number)
{
    sf::Vector2f vertices[4] = {sf::Vector2f(0, 0),
                                sf::Vector2f(0, 1),
                                sf::Vector2f(1, 1),
                                sf::Vector2f(1, 0)};
    for (int i = 0; i < 4; ++i)
    {
        _digits[index * 4 + i].texCoords = (vertices[i] + sf::Vector2f(number, 0)) * _texSize;
    }
}
void Selector::createDigits(unsigned char root)
{
    _digits.resize(root * root * 4);
    _digits.setPrimitiveType(sf::Quads);
    sf::Vector2f vertices[4] = {sf::Vector2f(0, 0),
                                sf::Vector2f(0, _size),
                                sf::Vector2f(_size, _size),
                                sf::Vector2f(_size, 0)};
    sf::Color vColors[4] =
        {
            sf::Color(255, 255, 255),
            sf::Color(255, 255, 255),
            sf::Color(100, 155, 255),
            sf::Color(255, 255, 255)};
    for (int i = 0, c = 0; i < root * root; ++i)
    {
        for (int k = 0; k < 4; ++k, ++c)
        {
            _digits[c].position = vertices[k] + (_size + _gap) * sf::Vector2f(i, 0);
            _digits[c].color = vColors[k];
        }
        assignTexture(i, i + 1);
    }
}
void Selector::render(sf::RenderWindow &window)
{
    window.draw(_digits, _renderState);
}
sf::Vector2f Selector::getPosition() const
{
    auto bbox = _digits.getBounds();
    return _renderState.transform.transformPoint(sf::Vector2f(bbox.width / 2, bbox.height / 2));
}
void Selector::setPosition(const sf::Vector2f &position)
{
    auto bbox = _digits.getBounds();
    _renderState.transform = sf::Transform::Identity;
    _renderState.transform.translate(position - sf::Vector2f(bbox.width, bbox.height) / 2.f);
}
sf::IntRect Selector::getBoundingBox() const
{
    return (sf::IntRect)_renderState.transform.transformRect(_digits.getBounds());
}

char Selector::getNumber(const sf::Vector2i &position, Event::EventType &event)
{
    sf::Vector2i realPosition = static_cast<sf::Vector2i>(_renderState.transform.getInverse().transformPoint(static_cast<sf::Vector2f>(position)));
    sf::IntRect rect;
    rect.width = rect.height = _size;
    for (unsigned char i = 0; i < _sudoku.getSize(); ++i)
    {
        rect.left = _digits[i * 4].position.x;
        rect.top = _digits[i * 4].position.y;
        if (rect.contains(realPosition))
        {
            event = Event::EventType::MoveEvent;
            return i + 1;
        }
    }
    return 0;
}