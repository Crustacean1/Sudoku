#include "SudokuPanel.h"

SudokuPanel::SudokuPanel(sf::RenderWindow &window, Sudoku &sudoku) : Layout<Vertical>(sf::IntRect(sf::Vector2i(0, 0), (sf::Vector2i)window.getSize())), _size(50)
{
    addChild(std::unique_ptr<SudokuBoard>(new SudokuBoard(sudoku, _digitsTexture)));
    addChild(std::unique_ptr<Selector>(new Selector(sudoku, _digitsTexture)));
}

void SudokuPanel::generateDigitTexture(unsigned char root)
{
    _digitsTexture.create(_size * (root * root + 1), _size);
    _digitsTexture.clear(sf::Color::Green);
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text digit;
    digit.setFont(font);
    digit.setCharacterSize(_size / 2);
    sf::FloatRect bounds;
    for (unsigned int i = 1; i <= _size * root; ++i)
    {
        digit.setString(std::to_string(i));
        bounds = digit.getGlobalBounds();
        digit.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
        digit.setPosition(sf::Vector2f(_size * i + _size / 2, _size / 2));
        _digitsTexture.draw(digit);
    }
    _digitsTexture.display();
}