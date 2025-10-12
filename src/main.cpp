#include "../include/LongNumber.h"

using namespace std;

int main()
{
    LongNumber n1("332452345236236232");
    LongNumber n2("-221532453245234598236598723649587632453");
    LongNumber res;
    res = n1 * n2;
    res.print();

    return 0;
}