#include "../include/Generator.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

Matrix Generator::generateMatrix(const size_t rows, const size_t columns)
{
    Matrix result(rows, columns);
    
    static bool seeded = false;
    if (!seeded) 
    {
        srand(time(0));
        seeded = true;
    }

    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < columns; j++)
        {
            result.setValue(i, j, rand() % 10);
        }
    }
 
    return result;
}

LongNumber Generator::generateLongNumber(const size_t len)
{
    LongNumber result(len);

    static bool seeded = false;
    if (!seeded) 
    {
        srand(time(0));
        seeded = true;
    }

    result[0] = (rand() % 9) + '1';
    
    for(size_t i = 1; i < len; i++) {
        result[i] = (rand() % 10) + '0';    
    }

    return result;
}