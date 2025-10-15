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

Matrix& Matrix::operator = (const Matrix& other)
{
    if(this == &other) return *this;

    deallocateMemory();
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

    return *this;
}

Matrix Matrix::operator + (const Matrix& other) const
{
    if(_rows != other._rows || _columns != other._columns) throw invalid_argument("Matrix dimensions must match for addition\n");

    Matrix result(_rows, _columns);
    for(size_t i = 0; i < _rows; i++)
    {
        for(size_t j = 0; j < _columns; j++) {
            result.setValue(i, j, getValue(i, j) + other.getValue(i, j));   // инкапсуляция
        }
    }
    return result;
}

Matrix Matrix::operator - (const Matrix& other) const
{
    if(_rows != other._rows || _columns != other._columns) throw invalid_argument("Matrix dimensions must match for subtraction\n");

    Matrix result(_rows, _columns);

    for(size_t i = 0; i < _rows; i++)
    {
        for(size_t j = 0; j < _columns; j++) {
            result.setValue(i, j, getValue(i, j) - other.getValue(i, j));
        }
    }
    return result;
}

// Matrix Matrix::operator * (const Matrix& other) const
// {
//     if(_rows != other._columns) throw invalid_argument("The row length must be equal to the column length\n");

//     Matrix result(_rows, other._columns);

//     for(size_t i = 0; i < _rows; i++)
//     {
//         for(size_t j = 0; j < _columns; j++) {
//             result.setValue()
//         }
//     }
//     return *this;
// }

Matrix Matrix::operator * (int other) const
{
    Matrix result(_rows, _columns);

    for(size_t i = 0; i < _rows; i++)
    {
        for(size_t j = 0; j < _columns; j++) {
            result.setValue(i, j, getValue(i, j) * other);
        }
    }
    return result;
}

// Matrix Matrix::operator * (LongNumber other) const
// {
//     Matrix result(_rows, _columns);

//     for(size_t i = 0; i < _rows; i++)
//     {
//         for(size_t j = 0; j < _columns; j++) {
//             result.setValue(i, j, number * other);
//         }
//     }
//     return *this;
// }

Matrix Matrix::transposition()
{
    return *this;
}

Matrix Matrix::inverseMatrix()
{
    return *this;
}

int Matrix::determinant()
{
    return 0;
}

void Matrix::allocateMemory()
{
    if(_rows > 0 && _columns > 0)
    {
        _data = new int*[_rows];
        for(size_t i = 0; i < _rows; i++) {
            _data[i] = new int[_columns];
        }

        for(size_t i = 0; i < _rows; i++)
        {
            for(size_t j = 0; j < _columns; j++)
            {
                _data[i][j] = 0;
            }
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

size_t Matrix::size() const {
    return _rows * _columns;
}

void Matrix::setValue(size_t rows, size_t columns, int value)
{
    if(rows >= _rows || columns >= _columns) throw out_of_range("Matrix index out of range\n");
    _data[rows][columns] = value;
}

int Matrix::getValue(size_t rows, size_t columns) const
{
    if(rows >= _rows || columns >= _columns) throw out_of_range("Matrix index out of range\n");
    return _data[rows][columns];
}

size_t Matrix::getRows() const
{
    return _rows;
}

size_t Matrix::getColumns() const
{
    return _columns;
}

void Matrix::print() const
{
    for(size_t i = 0; i < _rows; i++)
    {
        for(size_t j = 0; j < _columns; j++)
        {
            cout << _data[i][j] << '\t';
        }
        cout << "\n";
    }
    return;
}