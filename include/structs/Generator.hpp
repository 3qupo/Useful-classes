#pragma once

#include "LongNumber.hpp"
#include "Matrix.hpp"
#include "Graph.hpp"
#include "BinarySearchTree.hpp"

namespace Generator
{
    Matrix generateMatrix(const size_t rows, const size_t columns);
    LongNumber generateLongNumber(const size_t len);
}

