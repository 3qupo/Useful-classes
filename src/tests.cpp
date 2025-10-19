#include <iostream>
#include <cassert>

#include "../include/LongNumber.h"  
#include "../include/Matrix.h"
#include "../include/tests.h"

// \u274C ❌
// \u2705 ✅

using namespace std;

// ------------------------ LongNumber ------------------------

void testsLongNumber::testAssignmentOperatorLongNumber() 
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
    
    cout << "Успешно!\u2705" << endl;
}

void testsLongNumber::testIndexOperatorLongNumber() 
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
    
    cout << "Успешно!\u2705" << endl;
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
    
    cout << "Успешно!\u2705" << endl;
}

void testsLongNumber::testArithmeticOperatorsLongNumberWithInt() 
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
    
    cout << "Успешно!\u2705" << endl;
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
    
    cout << "Успешно!\u2705" << endl;
}

void testsLongNumber::testComparisonOperatorsLongNumberWithInt() 
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
    
    cout << "Успешно!\u2705" << endl;
}

void testsLongNumber::testEdgeCasesLongNumber() 
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
    
    cout << "Успешно!\u2705" << endl;
}

void testsLongNumber::testMixedOperationsLongNumber() 
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
    
    cout << "Успешно!\u2705" << endl;
}

// ----------------------- Matrix -----------------------

void testMatrix::testCreateMatrix()
{
    cout << "Тестирование создания матриц началось..." << endl;

    Matrix l;
    assert(l.getColumns() == 0);
    assert(l.getRows() == 0);
    assert(l.size() == 0);
    Matrix m(5, 5);
    assert(m.getRows() == 5);
    assert(m.getColumns() == 5);
    assert(m.getValue(3, 2) == 0);
    assert(m.size() == 25);

    Matrix m4(2, 2);
    m4.setValue(0, 0, 1);
    m4.setValue(0, 1, 2);
    m4.setValue(1, 0, 3);
    m4.setValue(1, 1, 4);
    
    Matrix m5(m4);
    assert(m5.getRows() == 2);
    assert(m5.getColumns() == 2);
    assert(m5.getValue(0, 0) == 1);
    assert(m5.getValue(1, 1) == 4);

    cout << "Успешно!\u2705" << endl;  
}

void testMatrix::testAssignmentOperatorMatrix()
{
    cout << "Тестирование операторов началось..." << endl;

    Matrix m1(2, 3);
    m1.setValue(0, 0, 1);
    m1.setValue(0, 1, 2);
    m1.setValue(0, 2, 3);
    m1.setValue(1, 0, 4);
    m1.setValue(1, 1, 5);
    m1.setValue(1, 2, 6);

    Matrix m2;

    // Присваивание
    m2 = m1;
    
    // Проверка копирования
    assert(m2.getRows() == 2);
    assert(m2.getColumns() == 3);
    assert(m2.getValue(0, 0) == 1);
    assert(m2.getValue(1, 2) == 6);
    
    // Проверка глубокого копирования
    m1.setValue(0, 0, 99);
    assert(m2.getValue(0, 0) == 1); // Копия не изменилась
    
    // Присваивание матриц разных размеров
    Matrix m3(1, 1);
    m3 = m1;
    assert(m3.getRows() == 2);
    assert(m3.getColumns() == 3);
    
    // Самоприсваивание
    m3 = m3;
    assert(m3.getRows() == 2);
    assert(m3.getColumns() == 3);
    assert(m3.getValue(0, 1) == 2);
    
    // Присваивание пустой матрицы
    Matrix m4;
    Matrix m5(3, 3);
    m5 = m4;
    assert(m5.getRows() == 0);
    assert(m5.getColumns() == 0);

    cout << "Успешно!\u2705" << endl;
}

void testMatrix::testArithmeticOperatorsWithMatrix()
{
    cout << "Тестирование математических операций началось..." << endl;

    // Сложение матриц
    Matrix m1(2, 2);
    m1.setValue(0, 0, 1);
    m1.setValue(0, 1, 2);
    m1.setValue(1, 0, 3);
    m1.setValue(1, 1, 4);
    
    Matrix m2(2, 2);
    m2.setValue(0, 0, 5);
    m2.setValue(0, 1, 6);
    m2.setValue(1, 0, 7);
    m2.setValue(1, 1, 8);
    
    Matrix sum = m1 + m2;
    assert(sum.getRows() == 2);
    assert(sum.getColumns() == 2);
    assert(sum.getValue(0, 0) == 6);
    assert(sum.getValue(0, 1) == 8);
    assert(sum.getValue(1, 0) == 10);
    assert(sum.getValue(1, 1) == 12);
    
    // Вычитание матриц
    Matrix diff = m2 - m1;
    assert(diff.getRows() == 2);
    assert(diff.getColumns() == 2);
    assert(diff.getValue(0, 0) == 4);
    assert(diff.getValue(0, 1) == 4);
    assert(diff.getValue(1, 0) == 4);
    assert(diff.getValue(1, 1) == 4);
    
    // Умножение матриц
    Matrix m3(2, 3);
    m3.setValue(0, 0, 1);
    m3.setValue(0, 1, 2);
    m3.setValue(0, 2, 3);
    m3.setValue(1, 0, 4);
    m3.setValue(1, 1, 5);
    m3.setValue(1, 2, 6);
    
    Matrix m4(3, 2);
    m4.setValue(0, 0, 7);
    m4.setValue(0, 1, 8);
    m4.setValue(1, 0, 9);
    m4.setValue(1, 1, 10);
    m4.setValue(2, 0, 11);
    m4.setValue(2, 1, 12);
    
    Matrix mult = m3 * m4;
    assert(mult.getRows() == 2);
    assert(mult.getColumns() == 2);
    assert(mult.getValue(0, 0) == 58);   // 1*7 + 2*9 + 3*11
    assert(mult.getValue(0, 1) == 64);   // 1*8 + 2*10 + 3*12
    assert(mult.getValue(1, 0) == 139);  // 4*7 + 5*9 + 6*11
    assert(mult.getValue(1, 1) == 154);  // 4*8 + 5*10 + 6*12

    cout << "Успешно!\u2705" << endl;
}

void testMatrix::testArithmeticOperatorsMatrixWithInt()
{
    cout << "Тестирование математических операций над матрицей и int началось..." << endl;

    Matrix m1(2, 2);
    m1.setValue(0, 0, 2);
    m1.setValue(0, 1, 4);
    m1.setValue(1, 0, 6);
    m1.setValue(1, 1, 8);
    
    // Умножение матрицы на скаляр (int)
    Matrix mult = m1 * 3;
    assert(mult.getRows() == 2);
    assert(mult.getColumns() == 2);
    assert(mult.getValue(0, 0) == 6);
    assert(mult.getValue(0, 1) == 12);
    assert(mult.getValue(1, 0) == 18);
    assert(mult.getValue(1, 1) == 24);
    
    // Умножение на отрицательный скаляр
    Matrix multNeg = m1 * (-2);
    assert(multNeg.getValue(0, 0) == -4);
    assert(multNeg.getValue(1, 1) == -16);
    
    // Умножение на ноль
    Matrix multZero = m1 * 0;
    assert(multZero.getValue(0, 0) == 0);
    assert(multZero.getValue(1, 1) == 0);

    cout << "Успешно!\u2705" << endl;
}

void testMatrix::testEdgeCasesMatrix()
{
    cout << "Тестирование обращений к элементам матрицы" << endl;

    // Пустая матрица
    Matrix empty;
    assert(empty.getRows() == 0);
    assert(empty.getColumns() == 0);
    assert(empty.size() == 0);
    
    // Матрица 1x1
    Matrix single(1, 1);
    single.setValue(0, 0, 42);
    assert(single.getRows() == 1);
    assert(single.getColumns() == 1);
    assert(single.getValue(0, 0) == 42);
    
    // Прямоугольные матрицы
    Matrix rect1(3, 5);
    assert(rect1.getRows() == 3);
    assert(rect1.getColumns() == 5);
    assert(rect1.size() == 15);
    
    Matrix rect2(5, 3);
    assert(rect2.getRows() == 5);
    assert(rect2.getColumns() == 3);
    assert(rect2.size() == 15);
    
    // Матрица с отрицательными значениями
    Matrix neg(2, 2);
    neg.setValue(0, 0, -1);
    neg.setValue(0, 1, -2);
    neg.setValue(1, 0, -3);
    neg.setValue(1, 1, -4);
    
    assert(neg.getValue(0, 0) == -1);
    assert(neg.getValue(1, 1) == -4);
    
    // Матрица с нулевыми размерами
    Matrix zeroSize(0, 5);
    assert(zeroSize.getRows() == 0);
    assert(zeroSize.getColumns() == 5);
    assert(zeroSize.size() == 0);

    cout << "Успешно!\u2705" << endl;
}