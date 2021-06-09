#include "SudokuGenerator.h"
#include "Sudoku.h"
#include <cstring>
#include <iostream>
#include <chrono>
//Problematic seeds:
//3499681090
//7506718
//2159308445
SudokuGenerator::SudokuGenerator(uint16_t rootSize) : _rootSize(rootSize), _size(_rootSize * _rootSize), _engine(_seed = /*2506892046*/ std::chrono::system_clock::now().time_since_epoch().count()), _sudokuDist(1, _rootSize * _rootSize)
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

    for (unsigned int i = 0; i < _size * _size * 4; ++i)
    {
        header->row->insertBefore((headerJumpTable[i] = new SudokuNode)->row);
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

bool SudokuGenerator::algorithmX(SudokuNode *header, LinkedNode<uint16_t> *solution)
{
    while (header->row->next()->prev() != header->row)
    {
        header = header->row->prev()->next()->_value;
    }
    if (header->row->next() == header->row)
    {
        return true;
    }
    if (header->col->next() == header->col)
    {
        return false;
    }
    auto shift = _sudokuDist(_engine);
    header->col->popOut();
    auto ptr = header->col;
    ptr = ptr->next(shift);
    auto it = ptr;
    do
    {
        LinkedNode<SudokuNode *> *droppedColumns = new LinkedNode<SudokuNode *>(header);

        for (auto rit = it->_value->row->next(); rit != it->_value->row; rit = rit->next())
        {
            droppedColumns->insertAfter(rit->_value->header);
        }
        header->col->popIn();
        droppedColumns->iterateForward(dropColumn);

        solution->insertAfter(it->_value->value);
        if (algorithmX(header->row->next()->_value, solution))
        {
            droppedColumns->iterateBackward(restoreColumn);
            delete droppedColumns;
            return true;
        }
        delete solution->next()->erase();
        droppedColumns->iterateBackward(restoreColumn);
        header->col->popOut();
        it = it->next();

        delete droppedColumns;
    } while (ptr != it);
    header->col->popIn();

    return false;
}
void SudokuGenerator::dropColumn(SudokuNode *header)
{
    for (auto it = header->col->next(); it != header->col; it = it->next())
    {
        for (auto row = it->_value->row->next(); row != it->_value->row; row = row->next())
        {
            row->_value->col->popOut();
        }
    }
    header->row->popOut();
}
void SudokuGenerator::restoreColumn(SudokuNode *header)
{
    header->row->popIn();

    for (auto it = header->col->prev(); it != header->col; it = it->prev())
    {
        for (auto row = it->_value->row->prev(); row != it->_value->row; row = row->prev())
        {
            row->_value->col->popIn();
        }
    }
}

void SudokuGenerator::decode(const uint16_t &value, const uint16_t &size, uint8_t **tab)
{
    tab[value % size][(value / size) % size] = ((value / size) / size) + 1;
}
Sudoku SudokuGenerator::generate()
{
    auto matrix = generateSparseConstraintMatrix();
    LinkedNode<uint16_t> *solution = new LinkedNode<uint16_t>(0);
    if (!algorithmX(matrix, solution))
    {
        throw std::string("solution not found");
    }
    disposeSparseConstraintMatrix(matrix);

    uint8_t **sudoku = new uint8_t *[_rootSize * _rootSize];
    for (auto i = 0; i < _rootSize * _rootSize; ++i)
    {
        sudoku[i] = new uint8_t[_rootSize * _rootSize];
        memset(sudoku[i], 0, _size * sizeof(uint8_t));
    }
    solution = solution->next();
    delete solution->prev()->erase();
    solution->iterateForward(decode, _size, sudoku);
    delete solution;
    return Sudoku(_rootSize, sudoku);
}