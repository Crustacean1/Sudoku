#include "SudokuBoard.h"
#include <string>
#include <iostream>
#include <cstring>
#include "GameModes/Game.h"

sf::Color SudokuBoard::__colors[6] = {sf::Color::White,
                                      sf::Color::White,
                                      sf::Color(127, 127, 127),
                                      sf::Color::Green,
                                      sf::Color::Blue,
                                      sf::Color::Red};
SudokuBoard::SudokuBoard(Sudoku &sudoku, Game::GameState &state, sf::RenderTexture &texture, float size) : _renderState(&texture.getTexture()), _size(size), _gap(2), _sudoku(sudoku),
                                                                                                           _digitSize(texture.getSize().x / (float)(_sudoku.getSize() + 2)), _highlight(-1), _state(state)

{
    copyBoard();
    createTiles();
    _boundingBox.width = _boundingBox.height = _sudoku.getSize() * _size + (_sudoku.getSize() - 1) * _gap + (_sudoku.getRootSize() - 1) * _gap;
    _boundingBox.left = _boundingBox.top = 0;
    _renderState.transform = sf::Transform::Identity;
}
void SudokuBoard::copyBoard()
{
    _board = new uint8_t *[_sudoku.getSize()];
    for (int i = 0; i < _sudoku.getSize(); ++i)
    {
        _board[i] = new uint8_t[_sudoku.getSize()];
        memcpy(_board[i], _sudoku[i], sizeof(uint8_t) * _sudoku.getSize());
    }
}
void SudokuBoard::adjustTile(unsigned int index, unsigned int number)
{
    sf::Vector2f vertices[4] = {sf::Vector2f(0, 0),
                                sf::Vector2f(_digitSize, 0),
                                sf::Vector2f(_digitSize, _digitSize),
                                sf::Vector2f(0, _digitSize)};
    for (int i = 0; i < 4; ++i)
    {
        _tiles[index * 4 + i].texCoords = vertices[i] + sf::Vector2f(_digitSize, 0) * (float)Sudoku::getNumber(number);
        _tiles[index * 4 + i].color = __colors[static_cast<unsigned char>(Sudoku::getMeta(number))];
    }
}
void SudokuBoard::setColor(unsigned int index, sf::Color color)
{
    _tiles[index * 4].color = _tiles[index * 4 + 1].color = _tiles[index * 4 + 2].color = _tiles[index * 4 + 3].color = color;
}
void SudokuBoard::createTiles()
{
    _tiles.resize(_sudoku.getSize() * _sudoku.getSize() * 4);
    _tiles.setPrimitiveType(sf::Quads);
    _background = _tiles;

    sf::Vector2f vertices[4] = {sf::Vector2f(0, 0),
                                sf::Vector2f(_size, 0),
                                sf::Vector2f(_size, _size),
                                sf::Vector2f(0, _size)};
    sf::Vector2f backgroundOffset = sf::Vector2f(_digitSize, 0) * ((float)_sudoku.getSize() + 1);
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
                        _background[c].texCoords = backgroundOffset + vertices[m] * (_digitSize / _size);
                        _background[c].position = _tiles[c].position = vertices[m] + sf::Vector2f((root * _size + _gap * (root + 1)) * k + (_size + _gap) * l, (root * _size + _gap * (root + 1)) * i + (_size + _gap) * j);
                    }
                    adjustTile(c / 4 - 1, _sudoku[i * root + j][k * root + l]);
                }
            }
        }
    }
}
void SudokuBoard::render(sf::RenderWindow &window)
{
    updateTiles();
    window.draw(_background, _renderState);
    if (_state!=Game::GameState::Pause)
    {
        window.draw(_tiles, _renderState);
    }
}
sf::IntRect SudokuBoard::getBoundingBox() const
{
    auto bbox = _tiles.getBounds();
    return sf::IntRect(_position.x - bbox.width / 2, _position.y - bbox.height / 2, bbox.width, bbox.height);
}
void SudokuBoard::setPosition(const sf::Vector2f &position)
{
    auto bbox = _tiles.getBounds();
    _position = position;
    _renderState.transform = sf::Transform::Identity;
    _renderState.transform.translate(position - sf::Vector2f(bbox.width, bbox.height) / 2.f);
}
sf::Vector2f SudokuBoard::getPosition() const
{
    return _position;
}
sf::Vector2i SudokuBoard::selectField(const sf::Vector2i &position)
{
    sf::Vector2i realPosition = static_cast<sf::Vector2i>(_renderState.transform.getInverse().transformPoint(static_cast<sf::Vector2f>(position)));
    sf::IntRect rect;
    rect.width = rect.height = _size;
    for (int i = 0, c = 0; i < _sudoku.getSize(); ++i)
    {
        for (int j = 0; j < _sudoku.getSize(); ++j, ++c)
        {
            rect.left = _tiles[c * 4].position.x;
            rect.top = _tiles[c * 4].position.y;
            if (rect.contains(realPosition))
            {
                return sf::Vector2i(j, i);
            }
        }
    }
    return sf::Vector2i(-1, -1);
}
void SudokuBoard::updateTiles()
{
    auto root = _sudoku.getRootSize();
    for (int i = 0; i < _sudoku.getSize(); ++i)
    {
        for (int j = 0; j < _sudoku.getSize(); ++j)
        {
            if (_sudoku[i][j] != _board[i][j])
            {
                adjustTile(i * root * root + j, _sudoku[i][j]);
                _board[i][j] = _sudoku[i][j];
            }
            if (Sudoku::getNumber(_sudoku[i][j]) == _highlight)
            {
                setColor(i * root * root + j, sf::Color(0, 100, 200));
            }
        }
    }
}
void SudokuBoard::resetTiles()
{
    auto root = _sudoku.getRootSize();
    for (int i = 0; i < _sudoku.getSize(); ++i)
    {
        for (int j = 0; j < _sudoku.getSize(); ++j)
        {
            adjustTile(i * root * root + j, _sudoku[i][j]);
        }
    }
}
void SudokuBoard::setHighlight(unsigned char highlight)
{
    if (highlight == _highlight)
    {
        return;
    }
    _highlight = highlight;
    resetTiles();
}
SudokuBoard::~SudokuBoard()
{
    for (int i = 0; i < _sudoku.getSize(); ++i)
    {
        delete[] _board[i];
    }
    delete[] _board;
}