#pragma once

#include "../include/LongNumber.h"
#include "../include/Matrix.h"

namespace testsLongNumber
{
    void testAssignmentOperator();
    void testIndexOperator();
    void testArithmeticOperatorsWithLongNumber();
    void testArithmeticOperatorsWithInt();
    void testComparisonOperatorsWithLongNumber();
    void testComparisonOperatorsWithInt();
    void testEdgeCases();
    void testMixedOperations();
}

namespace testMatrix
{
    void testCreateMatrix();
    void testAssignmentOperator();
    void testArithmeticOperatorsWithMatrix();
    void testArithmeticOperatorsWithInt();
    void testEdgeCases();
}