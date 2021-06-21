#ifndef SUDOKUPANEL
#define SUDOKUPANEL

#include "SudokuBoard.h"
#include "Selector.h"
#include "Sudoku/Sudoku.h"
#include "../Layout.h"

class SudokuPanel : public Layout<Vertical>
{
    sf::RenderTexture _digitsTexture;
    float _size;
    void generateDigitTexture(unsigned char root);

    public:
    SudokuPanel(sf::RenderWindow & window,Sudoku & sudoku);
};

#endif /*SUDOKUPANEL*/