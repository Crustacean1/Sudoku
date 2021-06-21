#ifndef SUDOKUBOARD
#define SUDOKUBOARD

#include "GUI/Drawable.h"
#include "Sudoku/Sudoku.h"

class SudokuBoard : public Drawable
{
    sf::VertexArray _digits;
    void createDigits(sf::Texture texure);
    void adjustTexture(unsigned int index, unsigned int number);

    float _size;
    float _gap;
    sf::IntRect _boundingBox;

    Sudoku &_sudoku;
    float _digitSize;
    sf::Vector2f _position;
    sf::Transform _transform;

public:
    SudokuBoard(Sudoku &sudoku, sf::RenderTexture &texture, float size = 50);
    void render(sf::RenderWindow &window);
    sf::IntRect getBoundingBox() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &position);

    static sf::RectangleShape *getDigits();
};

#endif /*SUDOKUBOARD*/