#include "SudokuBoard.h"
#include <string>
#include <iostream>

sf::RenderTexture SudokuBoard::__digitTexture;
sf::RectangleShape SudokuBoard::__digits[__root*__root*__root*__root+1];
float SudokuBoard::__size = 50;

SudokuBoard::SudokuBoard(Sudoku &sudoku, sf::Vector2f position, float size) : _size(size), _gap(2), _position(position), _sudoku(sudoku)
{
    _boundingBox.width = _boundingBox.height = _sudoku.getSize() * _size + (_sudoku.getSize() - 1) * _gap;
    _boundingBox.left = _position.x - _boundingBox.width / 2;
    _boundingBox.top = _position.y - _boundingBox.height / 2;
}

void SudokuBoard::createTexture()
{
    __digitTexture.create(__size * (__root * __root + 1), __size);
    __digitTexture.clear(sf::Color::Green);
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text digit;
    digit.setFont(font);
    digit.setCharacterSize(__size / 2);
    sf::FloatRect bounds;
    for (unsigned int i = 1; i <= __root * __root; ++i)
    {
        digit.setString(std::to_string(i));
        bounds = digit.getGlobalBounds();
        digit.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
        digit.setPosition(sf::Vector2f(__size * i + __size / 2, __size / 2));
        __digitTexture.draw(digit);
    }
    __digitTexture.display();
}
void SudokuBoard::createDigits()
{
    auto count = __root * __root * __root * __root;
    for (unsigned int i = 0; i <= count; ++i)
    {
        __digits[i].setTexture(&__digitTexture.getTexture());
        __digits[i].setTextureRect(sf::IntRect(i * __size, 0, __size, __size));
        __digits[i].setSize(sf::Vector2f(__size, __size));
        __digits[i].setOrigin(sf::Vector2f(__size / 2, __size / 2));
    }
}

void SudokuBoard::init()
{
    createTexture();
    createDigits();
}
sf::RectangleShape *SudokuBoard::getDigits()
{
    return __digits;
}
void SudokuBoard::render(sf::RenderWindow &window)
{
    auto root = _sudoku.getRootSize();
    auto pos = _position - sf::Vector2f(_boundingBox.width / 2 - _size / 2, _boundingBox.height / 2 - _size / 2);
    sf::RectangleShape *cell = __digits;
    auto scale = sf::Vector2f(1,1) * (_size/__size);
    for (int i = 0; i < root; ++i)
    {
        for (int j = 0; j < root; ++j)
        {
            for (int k = 0; k < root; ++k)
            {
                for (int l = 0; l < root; ++l)
                {
                    cell = __digits + Sudoku::getNumber(_sudoku[j * root + l][i * root + k]);
                    cell->setPosition(sf::Vector2f(i * root + k, j * root + l) * (_size + _gap) + pos);
                    cell->setScale(scale);
                    window.draw(*cell);
                }
            }
        }
    }
}
sf::IntRect SudokuBoard::getBoundingBox() const
{
    return _boundingBox;
}
void SudokuBoard::setPosition(const sf::Vector2f &position)
{
    _position = position;
    _boundingBox.left = _position.x - _boundingBox.width / 2;
    _boundingBox.top = _position.y - _boundingBox.height / 2;
}
sf::Vector2f SudokuBoard::getPosition() const
{
    return _position;
}