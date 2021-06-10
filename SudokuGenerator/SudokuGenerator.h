#ifndef SUDOKUGENERATOR
#define SUDOKUGENERATOR

#define __DEBUG(x) std::cout << __LINE__ << " : " << #x << " = " << (x) << std::endl;
#define __LOG(x) std::cout << x << std::endl;

#include <cstdint>
#include <random>
#include "../LinkedNode/LinkedNode.h"

class Sudoku;

class SudokuGenerator
{
    struct SudokuNode
    {
        uint16_t value;
        LinkedNode<SudokuNode *> *row;
        LinkedNode<SudokuNode *> *col;
        SudokuNode *header;
        SudokuNode() : value(0), row(new LinkedNode<SudokuNode *>(this)), col(new LinkedNode<SudokuNode *>(this)), header(nullptr) {}
        SudokuNode(uint16_t val) : value(val), row(new LinkedNode<SudokuNode *>(this)), col(new LinkedNode<SudokuNode *>(this)), header(nullptr) {}
        ~SudokuNode()
        {
            delete row->erase();
            delete col->erase();
        }
    };
    friend uint32_t count(LinkedNode<SudokuGenerator::SudokuNode *> *node);

private:
    uint16_t _rootSize;
    uint16_t _size;
    uint32_t _seed;
    std::default_random_engine _engine;
    std::uniform_int_distribution<int> _sudokuDist;

    int global_id = 0;

    SudokuNode **generateHeaders();
    void appendNewRow(unsigned int row, unsigned int column, unsigned int number, SudokuNode **headers);

    SudokuNode *generateSparseConstraintMatrix();
    void disposeSparseConstraintMatrix(SudokuNode *header);

    bool algorithmX(SudokuNode *header, LinkedNode<uint16_t> *solution);

    static void dropColumn(SudokuNode *header);
    static void restoreColumn(SudokuNode *header);

    static void decode(const uint16_t &value, const uint16_t &size, uint8_t **tab);

public:
    SudokuGenerator(uint16_t rootSize);
    Sudoku generate();
    ~SudokuGenerator();
};

#endif /*SUDOKUGENERATOR*/