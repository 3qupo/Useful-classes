#include "../include/LongNumber.h"

using namespace std;

// чем new отличается от malloc и free от delete?

// TODO: Почему сравнивается только LongNumber с int, но не наоборот
int main() 
{
    LongNumber number1("13582937465928374659823761");
    LongNumber number2("135829374659283746598237615");
    LongNumber res;
    res = number1 - number2;
    res.print();

    return 0;
}
