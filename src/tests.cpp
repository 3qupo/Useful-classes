#include <iostream>
#include <cassert>

#include "../include/LongNumber.h"  
#include "../include/Matrix.h"
#include "../include/tests.h"

// \u274C ❌
// \u2705 ✅

using namespace std;

// ------------------------ LongNumber ------------------------

void testsLongNumber::testAssignmentOperator() 
{
    cout << "Testing assignment operator..." << endl;
    
    LongNumber num1("12345");
    LongNumber num2("-67890");
    LongNumber num3("0");
    
    // Присваивание положительного числа
    LongNumber test1;
    test1 = num1;
    assert(test1 == num1);
    
    // Присваивание отрицательного числа
    LongNumber test2;
    test2 = num2;
    assert(test2 == num2);
    
    // Присваивание нуля
    LongNumber test3;
    test3 = num3;
    assert(test3 == num3);
    
    // Самоприсваивание
    test1 = test1;
    assert(test1 == num1);
    
    cout << "Assignment operator tests passed!" << endl;
}

void testsLongNumber::testIndexOperator() 
{
    cout << "Testing index operator..." << endl;
    
    LongNumber num("12345");
    
    // Проверка доступа к цифрам
    assert(num[0] == '1');
    assert(num[1] == '2');
    assert(num[4] == '5');
    
    // Проверка изменения через индекс
    num[0] = '9';
    assert(num[0] == '9');
    assert(num == LongNumber("92345"));
    
    // Восстановление исходного значения
    num[0] = '1';
    
    cout << "Index operator tests passed!" << endl;
}

void testsLongNumber::testArithmeticOperatorsWithLongNumber() 
{
    cout << "Testing arithmetic operators with LongNumber..." << endl;
    
    LongNumber a("123");
    LongNumber b("45");
    LongNumber c("-67");
    LongNumber d("-8");
    
    // Сложение
    assert(a + b == LongNumber("168"));
    assert(a + c == LongNumber("56"));
    assert(c + a == LongNumber("56"));
    assert(c + d == LongNumber("-75"));
    
    // Вычитание
    assert(a - b == LongNumber("78"));
    assert(a - c == LongNumber("190"));
    assert(c - a == LongNumber("-190"));
    assert(c - d == LongNumber("-59"));
    
    // Умножение
    assert(a * b == LongNumber("5535"));  // 123 * 45 = 5535
    assert(a * c == LongNumber("-8241")); // 123 * (-67) = -8241
    assert(c * d == LongNumber("536"));   // (-67) * (-8) = 536
    
    // Деление и остаток (только для положительных)
    LongNumber e("100");
    LongNumber f("3");
    assert(e / f == LongNumber("33"));
    assert(e % f == LongNumber("1"));
    
    cout << "Arithmetic operators with LongNumber tests passed!" << endl;
}

void testsLongNumber::testArithmeticOperatorsWithInt() 
{
    cout << "Testing arithmetic operators with int..." << endl;
    
    LongNumber a("123");
    LongNumber b("-45");
    
    // Сложение с int
    assert(a + 10 == LongNumber("133"));
    assert(b + 10 == LongNumber("-35"));
    assert(a + (-10) == LongNumber("113"));
    
    // Вычитание с int
    assert(a - 10 == LongNumber("113"));
    assert(b - 10 == LongNumber("-55"));
    assert(a - (-10) == LongNumber("133"));
    
    // Умножение с int
    assert(a * 2 == LongNumber("246"));
    assert(b * 2 == LongNumber("-90"));
    assert(a * (-2) == LongNumber("-246"));
    
    // Деление и остаток с int
    assert(a / 2 == LongNumber("61"));
    assert(a % 2 == LongNumber("1"));
    
    cout << "Arithmetic operators with int tests passed!" << endl;
}

void testsLongNumber::testComparisonOperatorsWithLongNumber() 
{
    cout << "Testing comparison operators with LongNumber..." << endl;
    
    LongNumber a("100");
    LongNumber b("200");
    LongNumber c("-100");
    LongNumber d("-200");
    LongNumber e("100");
    
    // Равенство
    assert(a == e);
    assert(a != b);
    assert(a != c);
    
    // Больше
    assert(b > a);
    assert(a > c);
    assert(c > d);
    assert(a > d);
    
    // Больше или равно
    assert(a >= e);
    assert(b >= a);
    assert(a >= c);
    
    // Меньше
    assert(a < b);
    assert(c < a);
    assert(d < c);
    assert(d < a);
    
    // Меньше или равно
    assert(a <= e);
    assert(a <= b);
    assert(c <= a);
    
    cout << "Comparison operators with LongNumber tests passed!" << endl;
}

void testsLongNumber::testComparisonOperatorsWithInt() 
{
    cout << "Testing comparison operators with int..." << endl;
    
    LongNumber a("100");
    LongNumber b("-50");
    
    // Равенство
    assert(a == 100);
    assert(a != 50);
    assert(b == -50);
    assert(b != 50);
    
    // Больше
    assert(a > 50);
    assert(a > -100);
    assert(b > -100);
    
    // Больше или равно
    assert(a >= 100);
    assert(a >= 50);
    assert(b >= -50);
    assert(b >= -100);
    
    // Меньше
    assert(a < 200);
    assert(b < 0);
    assert(b < 50);
    
    // Меньше или равно
    assert(a <= 100);
    assert(a <= 200);
    assert(b <= -50);
    assert(b <= 0);
    
    cout << "Comparison operators with int tests passed!" << endl;
}

void testsLongNumber::testEdgeCases() 
{
    cout << "Testing edge cases..." << endl;
    
    // Нули
    LongNumber zero1("0");
    LongNumber zero2("0");
    
    assert(zero1 == zero2);
    assert(zero1 + zero2 == LongNumber("0"));
    assert(zero1 - zero2 == LongNumber("0"));
    assert(zero1 * zero2 == LongNumber("0"));
    
    // Большие числа
    LongNumber big1("12345678901234567890");
    LongNumber big2("98765432109876543210");
    
    assert(big1 < big2);
    assert(big1 + big2 == LongNumber("111111111011111111100"));
    
    // Отрицательные операции
    LongNumber neg("-123");
    LongNumber pos("456");
    
    assert(neg + pos == LongNumber("333"));
    assert(neg - pos == LongNumber("-579"));
    assert(pos - neg == LongNumber("579"));
    
    cout << "Edge cases tests passed!" << endl;
}

void testsLongNumber::testMixedOperations() 
{
    cout << "Testing mixed operations..." << endl;
    
    LongNumber a("15");
    LongNumber b("3");
    LongNumber c("-5");
    
    // Комбинированные арифметические операции
    assert(a + b - c == LongNumber("23"));  // 15 + 3 - (-5) = 23
    assert(a * b + c == LongNumber("40"));  // 15*3 + (-5) = 40
    assert((a + b) * c == LongNumber("-90")); // (15+3) * (-5) = -90
    
    // Комбинированные сравнения
    assert(a + b > c);
    assert(a * b >= LongNumber("45"));
    assert(c * b < a);
    
    cout << "Mixed operations tests passed!" << endl;
}

// ----------------------- Matrix -----------------------

void testMatrix::testCreateMatrix()
{
    return;   
}

void testMatrix::testAssignmentOperator()
{
    return;
}

void testMatrix::testArithmeticOperatorsWithMatrix()
{
    return;
}

void testMatrix::testArithmeticOperatorsWithInt()
{
    return;
}

void testMatrix::testEdgeCases()
{
    return;
}