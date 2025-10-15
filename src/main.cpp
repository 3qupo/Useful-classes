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

    Matrix A = generateMatrix(5, 5);
    Matrix B = generateMatrix(5, 5);
    int other = 0;
    Matrix result = A - B;
    A.print();
    cout << endl;
    B.print();
    cout << endl;
    result.print();

    return 0;
}