#include "../include/LongNumber.h"
#include "../include/Matrix.h"
#include "../include/Generator.h"

using namespace std;
using namespace Generator;

int main()
{
    // LongNumber n1("332452345236236232");
    // LongNumber n2("-221532453245234598236598723649587632453");
    // LongNumber res;
    // res = n1 * n2;
    // res.print();

    LongNumber num1 = generateLongNumber(3223);
    num1.print();

    // Matrix A = generateMatrix(5, 5);
    // A.print();
    // size_t result = A.size();
    // cout << result << endl;
    return 0;
}