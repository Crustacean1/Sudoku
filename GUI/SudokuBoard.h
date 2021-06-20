#ifndef SUDOKUBOARD
#define SUDOKUBOARD

#include "Drawable.h"
#include "Sudoku/Sudoku.h"

class SudokuBoard : public Drawable
{
    static constexpr unsigned int __root =6;
    static sf::RenderTexture __digitTexture;
    static sf::RectangleShape __digits[__root*__root*__root*__root+1];
    static float __size;

    static void createTexture();
    static void createDigits();

    float _size;
    float _gap;
    sf::Vector2f _position;
    sf::IntRect _boundingBox;

    Sudoku & _sudoku;
public:
    SudokuBoard(Sudoku &sudoku,sf::Vector2f position  = sf::Vector2f(0,0),float size = 50);
    void render(sf::RenderWindow &window);
    sf::IntRect getBoundingBox() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &position);

    static void init();
    static sf::RectangleShape * getDigits();
};

#endif /*SUDOKUBOARD*/