#include "../include/Generator.h"
#include "../include/Matrix.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

Matrix Generator::generateMatrix(const size_t rows, const size_t columns)
{
    Matrix result(rows, columns);
    
    srand(time(0));
    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < columns; j++)
        {
            result.setValue(i, j, rand() % 10);
        }
    }

    return result;
}

// LongNumber Generator::generateLongNumber(const size_t len)
// {

// }