#pragma once

#include "../include/LongNumber.h"
#include "../include/Matrix.h"
#include "../include/Graph.h"
#include "../include/BinarySearchTree.h"

namespace Generator
{
    Matrix generateMatrix(const size_t rows, const size_t columns);
    LongNumber generateLongNumber(const size_t len);
}

