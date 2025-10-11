#include "../include/LongNumber.h"

using namespace std;

// чем new отличается от malloc и free от delete?

// TODO: Почему сравнивается только LongNumber с int, но не наоборот
int main() 
{
    LongNumber number1("135829374659283746598237645");
    LongNumber number2("922345234523452345234523452345");
    LongNumber res;
    res = number1 - number2;
    res.print();

    return 0;
}
