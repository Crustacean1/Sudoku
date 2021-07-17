#ifndef SUDOKUGENERATOR
#define SUDOKUGENERATOR

#define __DEBUG(x) std::cout << __LINE__ << " : " << #x << " = " << (x) << std::endl;
#define __ASSERT(x)                                                  \
    if (!(x))                                                        \
    {                                                                \
        std::cerr << "assertion failed: "                            \
                  << "line: " << __LINE__ << " " << #x << std::endl; \
        exit(-1);                                                    \
    }
#define __LOG(x) std::cout << x << std::endl;

#include <cstdint>
#include <random>
#include "../LinkedNode/LinkedNode.h"
#include <tuple>

class Sudoku;

/** Class responsible for sudoku generation*/
class SudokuGenerator
{
    /** Structure representing node in sparse matrix**/
    struct SudokuNode
    {
        /** encoded position and value on board**/
        uint16_t value;
        /** Linked list containing row**/
        LinkedNode<SudokuNode *> *row;
        /**Linked list containing column**/
        LinkedNode<SudokuNode *> *col;
        /** Pointer to column header**/
        SudokuNode *header;

        uint32_t global_id = 0;

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

    bool algorithmX(SudokuNode *header, LinkedNode<SudokuNode *> *solution);

    void applySolution(LinkedNode<SudokuNode *> *solution);
    void revertSolution(LinkedNode<SudokuNode *> *solution);

    static void dropNode(SudokuNode *node);
    static void restoreNode(SudokuNode *node);

    static void decode(SudokuNode *node, const uint16_t &size, uint8_t **tab);

    Sudoku constructSudoku(LinkedNode<SudokuNode *> *solution);

    Sudoku generateMinimalSudoku(SudokuNode *header, LinkedNode<SudokuNode *> *solution);
    void randomSudokuTrim(Sudoku &sudoku, unsigned int scale);

    bool isSudokuAmbiguous(SudokuNode *header, uint8_t &ambiguity);

public:
    SudokuGenerator(uint16_t rootSize);
    std::tuple<Sudoku, Sudoku> generate();
    ~SudokuGenerator();
};

#endif /*SUDOKUGENERATOR*/