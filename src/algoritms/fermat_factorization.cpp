#include <iostream>
#include "../../include/structs/LongNumber.hpp"

LongNumber my_sqrt(LongNumber number)
{
    if (number == LongNumber("0")) return LongNumber("0");
    
    LongNumber x = number;
    LongNumber two("2");
    LongNumber prev;
    
    do {
        prev = x;
        x = (x + number / x) / two;
    } while (x < prev);
    
    return x;
}

void fermat_factorization(LongNumber& number)
{
    if(number % 2 == 0) 
    {
        std::cout << "Число должно быть нечетным для метода факторизации Ферма" << std::endl;
        return;
    }

    LongNumber h = my_sqrt(number);

    if(h * h == number) 
    {
        std::cout << "Факторы: ";
        h.print();
        std::cout << " ";
        h.print();
        return;
    }

    LongNumber Rx = h * 2 + 1;      // check
    LongNumber Ry("1");
    LongNumber two("2");
    LongNumber one("1");
    LongNumber Rxy = h * h - number;
    LongNumber zero("0");

    while(Rxy != zero)
    {
        if(Rxy > zero)
        {
            Rxy = Rxy - Ry;
            Ry = Ry + 2;
        }
        else
        {
            Rxy = Rxy + Rx;
            Rx = Rx + 2;
        }
    }

    LongNumber factor1 = (Rx - Ry) / two;
    LongNumber factor2 = ((Rx + Ry) / two) - 1;

    std::cout << "Факторы: ";
    factor1.print();
    std::cout << " ";
    factor2.print();
}

