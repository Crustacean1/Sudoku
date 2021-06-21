#include "SudokuBoard.h"
#include <string>
#include <iostream>

SudokuBoard::SudokuBoard(Sudoku &sudoku, sf::RenderTexture &texture, float size) : _size(size), _gap(2), _sudoku(sudoku),
                                                                                   _digitSize(texture.getSize().x / (float)(_sudoku.getSize() + 1)),
                                                                                   _transform(sf::Transform::Identity)
{
    createDigits(texture.getTexture());
    _boundingBox.width = _boundingBox.height = _sudoku.getSize() * _size + (_sudoku.getSize() - 1) * _gap + (_sudoku.getRootSize() - 1) * _gap;
    _boundingBox.left = _boundingBox.top = 0;
}

void SudokuBoard::adjustTexture(unsigned int index, unsigned int number)
{
    sf::Vector2f vertices[4] = {sf::Vector2f(0, 0),
                                sf::Vector2f(_digitSize, 0),
                                sf::Vector2f(_digitSize, _digitSize),
                                sf::Vector2f(0, _digitSize)};
    for (int i = 0; i < 4; ++i)
    {
        _digits[index * 4 + i].texCoords = vertices[i] + sf::Vector2f(_digitSize, 0) * (float)number;
    }
}
void SudokuBoard::createDigits(sf::Texture texure)
{
    _digits.resize(_sudoku.getSize() * _sudoku.getSize());
    _digits.setPrimitiveType(sf::Quads);
    sf::Vector2f vertices[4] = {sf::Vector2f(0, 0),
                                sf::Vector2f(_size, 0),
                                sf::Vector2f(_size, _size),
                                sf::Vector2f(0, _size)};
    auto root = _sudoku.getRootSize();
    for (int i = 0, c = 0; i < root; ++i)
    {
        for (int j = 0; j < root; ++j)
        {
            for (int k = 0; k < root; ++k)
            {
                for (int l = 0; l < root; ++l)
                {
                    for (int m = 0; m < 4; ++m, ++c)
                    {
                        _digits[c].position = vertices[m] + sf::Vector2f(root * _size * i + i * _gap + (_size + _gap) * k, root * _size * j + j * _gap + (_size + _gap) * l);
                    }
                    adjustTexture(c / 4, Sudoku::getNumber(_sudoku[i * root + k][j * root + l]));
                }
            }
        }
    }
}

void SudokuBoard::render(sf::RenderWindow &window)
{
    window.draw(_digits);
}
sf::IntRect SudokuBoard::getBoundingBox() const
{
    auto bbox = _digits.getBounds();
    return sf::IntRect(_position.x - bbox.width / 2, _position.y - bbox.height / 2, bbox.width, bbox.height);
}
void SudokuBoard::setPosition(const sf::Vector2f &position)
{
    _position = position;
    _transform = sf::Transform::Identity;
    _transform.translate(_position);
}
sf::Vector2f SudokuBoard::getPosition() const
{
    return _position;
}