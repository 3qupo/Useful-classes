#pragma once

#include "../include/LongNumber.h"
#include "../include/Matrix.h"

namespace testsLongNumber
{
    void testAssignmentOperatorLongNumber();
    void testIndexOperatorLongNumber();
    void testArithmeticOperatorsWithLongNumber();
    void testArithmeticOperatorsLongNumberWithInt();
    void testComparisonOperatorsWithLongNumber();
    void testComparisonOperatorsLongNumberWithInt();
    void testEdgeCasesLongNumber();
    void testMixedOperationsLongNumber();
}

namespace testMatrix
{
    void testCreateMatrix();
    void testAssignmentOperatorMatrix();
    void testArithmeticOperatorsWithMatrix();
    void testArithmeticOperatorsMatrixWithInt();
    void testEdgeCasesMatrix();
}