#include "include/LongNumber.h"
#include "include/Matrix.h"
#include "include/Generator.h"
#include "include/tests.h"
#include "include/Graph.h"
#include "include/BinarySearchTree.h"

using namespace std;
using namespace Generator;
using namespace testsLongNumber;
using namespace testMatrix;

LongNumber my_sqrt(LongNumber number);
void fermat_factorization(LongNumber& number);

int main() 
{
    LongNumber number("100000007");
    fermat_factorization(number);
    
    return 0;
}