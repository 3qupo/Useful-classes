#pragma once

#include <cstddef>
#include "../include/LongNumber.h"

class Matrix
{
private:
    size_t _rows;        // строки
    size_t _columns;     // столбцы
    int** _data;  

public:
    Matrix();
    Matrix(size_t rows, size_t columns);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator = (const Matrix& other);
    Matrix operator + (const Matrix& other) const;
    Matrix operator - (const Matrix& other) const;
    Matrix operator * (const Matrix& other) const;
    Matrix operator * (int other) const;

    Matrix transposition();
    Matrix inverseMatrix();
    int determinant();
    size_t size() const;                    // Получение общего количества элементов
    size_t getRows() const;
    size_t getColumns() const;
    int getValue(size_t rows, size_t columns) const;
    void setValue(size_t rows, size_t columns, int value);
    void print() const;
    void allocateMemory();
    void deallocateMemory();
};