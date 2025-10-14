#include "../include/Matrix.h"
#include <iostream>
#include <cstddef>

using namespace std;

Matrix::Matrix()
{
    _rows = 0;
    _columns = 0;
    _data = nullptr;
}

Matrix::Matrix(size_t rows, size_t columns)
{
    _rows = rows;
    _columns = columns;
    _data = nullptr;
    allocateMemory();
}

Matrix::Matrix(const Matrix& other)
{
    _rows = other._rows;
    _columns = other._columns;
    allocateMemory();
    for(size_t i = 0; i < _rows; i++)
    {
        for(size_t j = 0; j < _columns; j++)
        {
            _data[i][j] = other._data[i][j];
        }
    }
}

Matrix::~Matrix()
{
    deallocateMemory();
}

// Matrix& Matrix::operator = (const Matrix& other)
// {
//     if(_data != nullptr)
//     {
//         for(int i = 0; i < )
//     }
// }

void Matrix::allocateMemory()
{
    if(_rows > 0 && _columns > 0)
    {
        _data = new int*[_rows];
        for(size_t i = 0; i < _rows; i++) {
            _data[i] = new int[_columns];
        }
    }
    else _data = nullptr;
}

void Matrix::deallocateMemory()
{
    if(_data != nullptr)
    {
        for(size_t i = 0; i < _rows; i++) {
            delete[] _data[i];
        }
        delete[] _data;
        _data = nullptr;
    }
    _rows = 0;
    _columns = 0;
}

// need to check
size_t Matrix::size() const
{
    size_t size = 0;
    for(size_t i = 0; i < _rows; i++)
    {
        for(size_t j = 0; j < _columns; j++)
        {
            ++size;
        }
    }
}