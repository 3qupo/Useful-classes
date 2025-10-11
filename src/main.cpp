#include "../include/LongNumber.h"

using namespace std;

int main()
{
    LongNumber n1("14");
    LongNumber n2("23");
    LongNumber res;
    res = n1 * n2;
    res.print();

    return 0;
}