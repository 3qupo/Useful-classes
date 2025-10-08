#include "../include/LongNumber.h"

using namespace std;

// чем new отличается от malloc и free от delete?

// TODO: Почему сравнивается только LongNumber с int, но не наоборот
int main() {
  LongNumber number1("0000092342895793824570932874509823740597823049578032455000");
  LongNumber number2("13434221238034598702394857029386450983245098732445");
  LongNumber res;
  res = number1;
  res.RemovingLeadingZeros().print();

  return 0;
}
