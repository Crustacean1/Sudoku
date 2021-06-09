#include <iostream>
#include "LinkedList.h"
#include "SudokuGenerator.h"
#include "Sudoku.h"
#include <chrono>

int main(int argc, char **argv)
{
    int a = (argc > 1 && argv[1][0] > '0' && argv[1][0] < '9') ? (argv[1][0] - '0') : 3;
    SudokuGenerator generator(a);
    try
    {
        auto sudoku = generator.generate();
        std::cout << sudoku << std::endl;
    }
    catch (const std::string &e)
    {
        std::cerr << e << '\n';
    }
}