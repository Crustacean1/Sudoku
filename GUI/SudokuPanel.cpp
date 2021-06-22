#include "SudokuPanel.h"
#include "Event/MoveEvent.h"

SudokuPanel::SudokuPanel(sf::RenderWindow &window, Sudoku &sudoku, LinkedList<std::unique_ptr<Event>> &eventQueue) : Layout<Vertical>(sf::IntRect(0, 0, 0, window.getSize().y * 0.75)), _size(50), _eventQueue(eventQueue)
{
    generateDigitTexture(sudoku.getRootSize());
    addChild(std::unique_ptr<SudokuBoard>(new SudokuBoard(sudoku, _digitsTexture)));
    addChild(std::unique_ptr<Selector>(new Selector(sudoku, _digitsTexture)));
}

void SudokuPanel::generateDigitTexture(unsigned char root)
{
    _digitsTexture.create(_size * (root * root + 2), _size);
    _digitsTexture.clear(sf::Color(255, 255, 255, 0));
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text digit;
    digit.setFont(font);
    digit.setCharacterSize(_size / 2);
    digit.setFillColor(sf::Color::White);
    sf::FloatRect bounds;
    for (unsigned int i = 1; i <= root * root; ++i)
    {
        digit.setString(std::to_string(i));
        bounds = digit.getGlobalBounds();
        digit.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
        digit.setPosition(sf::Vector2f(_size * i + _size / 2, _size / 2));
        _digitsTexture.draw(digit);
    }

    sf::RectangleShape background(sf::Vector2f(_size, _size));
    background.setFillColor(sf::Color(35, 35, 35));
    background.setPosition(sf::Vector2f((root * root + 1) * _size,0));
    _digitsTexture.draw(background);
    _digitsTexture.display();
}
bool SudokuPanel::action(const sf::Vector2i &position, const sf::Event &type)
{
    if (type.type != sf::Event::MouseButtonPressed)
    {
        return false;
    }
    auto selectedNumber = static_cast<Selector *>(_children.getRoot()->next()->_value.get())->getNumber(position);
    sf::Vector2i coords = ((SudokuBoard *)_children.getRoot()->_value.get())->selectField(position);
    if (coords.x != -1 && selectedNumber != -1)
    {
        _eventQueue.push_back(std::unique_ptr<Event>(new MoveEvent(coords.y, coords.x, selectedNumber + 1)));
        return true;
    }
    return true;
}