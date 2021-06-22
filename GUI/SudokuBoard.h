#ifndef SUDOKUBOARD
#define SUDOKUBOARD

#include "GUI/Drawable.h"
#include "Sudoku/Sudoku.h"

class SudokuBoard : public Drawable
{
    sf::VertexArray _tiles;
    sf::VertexArray _background;
    sf::RenderStates _renderState;

    void createTiles();
    void adjustTile(unsigned int index, unsigned int number);
    void setColor(unsigned int index,sf::Color color);

    float _size;
    float _gap;
    sf::IntRect _boundingBox;

    uint8_t **_board;

    Sudoku &_sudoku;
    float _digitSize;
    unsigned int _highlight;
    sf::Vector2f _position;

    void copyBoard();
    void updateTiles();
    void resetTiles();

    static sf::Color __colors[6];

public:
    SudokuBoard(Sudoku &sudoku, sf::RenderTexture &texture, float size = 50);
    void render(sf::RenderWindow &window);
    sf::IntRect getBoundingBox() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &position);

    sf::Vector2i selectField(const sf::Vector2i &position);
    void setHighlight(unsigned char _highlight);
    ~SudokuBoard();
};

#endif /*SUDOKUBOARD*/