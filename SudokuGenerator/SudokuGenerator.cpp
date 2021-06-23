#include "../SudokuGenerator/SudokuGenerator.h"
#include "../Sudoku/Sudoku.h"
#include "LinkedList/LinkedList.h"
#include <cstring>
#include <iostream>
#include <chrono>
//Problematic seeds:
//3499681090
//7506718
//2159308445
// 3976840948
// 4082856991 for 5
SudokuGenerator::SudokuGenerator(uint16_t rootSize) : _rootSize(rootSize), _size(_rootSize * _rootSize),
                                                      _seed(1 ? std::chrono::system_clock::now().time_since_epoch().count() : 2165206914),
                                                      _engine(_seed), _sudokuDist(1, _rootSize * _rootSize)
{
    std::cout << "seed: " << _seed << std::endl;
}

SudokuGenerator::~SudokuGenerator()
{
}

SudokuGenerator::SudokuNode **SudokuGenerator::generateHeaders()
{
    SudokuNode *header = new SudokuNode;

    SudokuNode **headerJumpTable = new SudokuNode *[_size * _size * 4];
    headerJumpTable[0] = header;
    header->header = nullptr;
    header->value = 0;

    for (unsigned int i = 1; i < _size * _size * 4; ++i)
    {
        header->row->insertBefore((headerJumpTable[i] = new SudokuNode)->row);
        headerJumpTable[i]->header = nullptr;
        headerJumpTable[i]->value = 1;
    }
    return headerJumpTable;
}

void SudokuGenerator::appendNewRow(unsigned int row, unsigned int column, unsigned int number, SudokuNode **headers)
{
    SudokuNode *sudokuRow = new SudokuNode;
    uint32_t positions[4] = {
        row * _size + column,                                                                         //Row - Column
        _size * _size + row * _size + number,                                                         //Row - Number
        2 * _size * _size + column * _size + number,                                                  //Column - Number
        3 * _size * _size + ((row / _rootSize) + (column / _rootSize) * _rootSize) * _size + number}; //Box - Number

    for (int i = 0; i < 4 - 1; i++)
    {
        sudokuRow->row->insertBefore((new SudokuNode)->row);
    }

    for (unsigned int i = 0; i < 4; ++i, sudokuRow = sudokuRow->row->next()->_value)
    {
        sudokuRow->header = headers[positions[i]];
        sudokuRow->header->col->insertBefore(sudokuRow->col);
        sudokuRow->header->value += 1;

        sudokuRow->value = row + _size * (column + _size * number);
    }
}

SudokuGenerator::SudokuNode *SudokuGenerator::generateSparseConstraintMatrix()
{
    auto headerJumpTable = generateHeaders();

    for (unsigned int row = 0; row < _size; ++row)
    {
        for (unsigned int column = 0; column < _size; ++column)
        {
            for (unsigned int number = 0; number < _size; ++number)
            {
                appendNewRow(row, column, number, headerJumpTable);
            }
        }
    }
    auto header = headerJumpTable[0];
    delete[] headerJumpTable;
    return header;
}

void SudokuGenerator::disposeSparseConstraintMatrix(SudokuNode *header)
{
    auto head = header->row;
    auto cell = head->_value;
    bool a = true;
    while (a)
    {
        a = head->next() != head;

        auto colHead = head->_value->col;
        auto col = colHead->next();
        while (col != colHead)
        {
            cell = col->_value;
            col = col->next();
            delete cell;
        }
        cell = head->_value;
        head = head->next();
        delete cell;
    }
}

bool SudokuGenerator::algorithmX(SudokuNode *header, LinkedNode<SudokuNode *> *solution)
{
    while (header->row->next()->prev() != header->row)
    {
        header = header->row->prev()->next()->_value;
    }

    //Get column with least nodes
    header = header->row->select([](SudokuNode *node)
                                 { return -node->value; })
                 ->_value;

    if (header->row->next() == header->row)
    {
        return true;
    }
    if (header->col->next() == header->col)
    {
        return false;
    }

    //Iterate over column with random element
    auto shift = std::uniform_int_distribution<uint16_t>(1, header->value)(_engine);

    header->col->popOut();
    auto ptr = header->col;
    ptr = ptr->next(shift);
    auto it = ptr;
    do
    {
        header->col->popIn();
        dropNode(it->_value);

        solution->insertBefore(it->_value);

        if (algorithmX(header, solution)) // No tail recursion for you...
        {
            restoreNode(it->_value);
            return true;
        }

        restoreNode(it->_value);

        header->col->popOut();
        it = it->next();

        delete solution->prev()->erase();

    } while (ptr != it);
    header->col->popIn();

    return false;
}
void SudokuGenerator::dropNode(SudokuNode *node)
{
    __ASSERT(node->header != nullptr)
    auto outer = node->row;
    do
    {
        outer->_value->header->row->popOut();
        for (auto colIt = outer->_value->header->col->next(); colIt != outer->_value->header->col; colIt = colIt->next())
        {
            for (auto rowIt = colIt->_value->row->next(); rowIt != colIt->_value->row; rowIt = rowIt->next())
            {
                rowIt->_value->col->popOut();
                rowIt->_value->header->value -= 1;
            }
        }
        outer = outer->next();
    } while (outer != node->row);
}
void SudokuGenerator::restoreNode(SudokuNode *node)
{
    __ASSERT(node->header != nullptr)
    auto outer = node->row->prev();
    do
    {
        for (auto colIt = outer->_value->header->col->prev(); colIt != outer->_value->header->col; colIt = colIt->prev())
        {
            for (auto rowIt = colIt->_value->row->prev(); rowIt != colIt->_value->row; rowIt = rowIt->prev())
            {
                rowIt->_value->col->popIn();
                rowIt->_value->header->value += 1;
            }
        }
        outer->_value->header->row->popIn();
        outer = outer->prev();
    } while (outer != node->row->prev());
}

void SudokuGenerator::decode(SudokuNode *node, const uint16_t &size, uint8_t **tab)
{
    tab[node->value % size][(node->value / size) % size] = Sudoku::constructCell(((node->value / size) / size) + 1, Sudoku::SudokuMeta::Default);
}

Sudoku SudokuGenerator::constructSudoku(LinkedNode<SudokuNode *> *solution)
{
    uint8_t **sudoku = new uint8_t *[_rootSize * _rootSize];
    for (auto i = 0; i < _rootSize * _rootSize; ++i)
    {
        sudoku[i] = new uint8_t[_rootSize * _rootSize];
        memset(sudoku[i], 0, _size * sizeof(uint8_t));
    }
    solution->iterateForward(decode, _size, sudoku);
    Sudoku s(_rootSize, sudoku);
    return s;
}

std::tuple<Sudoku, Sudoku> SudokuGenerator::generate()
{
    auto matrix = generateSparseConstraintMatrix();
    LinkedNode<SudokuNode *> *solution = new LinkedNode<SudokuNode *>(new SudokuNode);
    if (!algorithmX(matrix, solution))
    {
        throw std::string("solution not found");
    }

    //removing fake root
    solution = solution->next();
    delete solution->prev()->_value;
    delete solution->prev()->erase();

    Sudoku src(constructSudoku(solution));
    Sudoku sudoku;
    if (_rootSize < 5)
    {
        sudoku = (generateMinimalSudoku(matrix, solution));
    }
    else
    {
        sudoku = src;
        randomSudokuTrim(sudoku, sudoku.getSize() * sudoku.getSize() * 0.4); // 0.4 correlates to difficulty
    }

    //cleaning up
    disposeSparseConstraintMatrix(matrix);

    return std::tie(src, sudoku);
}

bool SudokuGenerator::isSudokuAmbiguous(SudokuNode *header, uint8_t &ambiguity)
{

    while (header->row->next()->prev() != header->row)
    {
        header = header->row->next()->_value;
    }

    header = header->row->select([](SudokuNode *node)
                                 { return -node->value; })
                 ->_value;
    if (header->row->next() == header->row)
    {
        return (++ambiguity) > 1;
    }
    if (header->col->next() == header->col)
    {
        return false;
    }

    header->col->popOut();
    auto colIt = header->col->next();
    auto end = colIt;

    do
    {
        header->col->popIn();

        __ASSERT(colIt->_value->header != nullptr);
        dropNode(colIt->_value);
        if (isSudokuAmbiguous(header, ambiguity))
        {
            restoreNode(colIt->_value);
            return true;
        }
        restoreNode(colIt->_value);

        header->col->popOut();
        colIt = colIt->next();

    } while (colIt != end);

    header->col->popIn();
    return false;
}

void SudokuGenerator::applySolution(LinkedNode<SudokuNode *> *solution)
{
    solution->iterateForward([](SudokuNode *node)
                             { dropNode(node); });
}
void SudokuGenerator::revertSolution(LinkedNode<SudokuNode *> *solution)
{
    solution->iterateBackward([](SudokuNode *node)
                              { restoreNode(node); });
}

Sudoku SudokuGenerator::generateMinimalSudoku(SudokuNode *matrix, LinkedNode<SudokuNode *> *solutions)
{
    uint8_t ambiguity = 0;

    bool filled = false;
    LinkedNode<SudokuNode *> *it, *end;
    auto shift = std::uniform_int_distribution<int>(0, solutions->count())(_engine);
    LinkedList<LinkedNode<SudokuNode *> *> deletedNodes;

    it = end = solutions->next(shift);
    while (!filled)
    {
        filled = true;
        end = it->prev();

        do
        {
            it->popOut();
            applySolution(it->next());
            ambiguity = 0;
            if (isSudokuAmbiguous(matrix, ambiguity))
            {
                revertSolution(it->next());
                it->popIn();
            }
            else
            {
                deletedNodes.push_back(it);
                filled = false;
                revertSolution(it->next());
            }
            it = it->next();
        } while (it != end->next());
    }

    Sudoku sudoku(constructSudoku(it));

    deletedNodes.getRoot()->iterateForward([](LinkedNode<SudokuNode *> *node)
                                           { delete node->erase(); });
    delete it;

    return sudoku;
}
void SudokuGenerator::randomSudokuTrim(Sudoku &sudoku, unsigned int scale)
{
    std::uniform_int_distribution<uint16_t> dist(0, sudoku.getSize() - 1);
    for (int i = 0; i < sudoku.getSize(); ++i)
    {
        for (int j = 0; j < sudoku.getSize() && scale != 0; ++j, --scale)
        {
            sudoku[dist(_engine)][dist(_engine)] = Sudoku::constructCell(0, Sudoku::SudokuMeta::Empty);
        }
    }
}