#include "../include/LongNumber.h"
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

// конструктор по умолчанию
LongNumber::LongNumber() 
{
    _digits = nullptr;
    _size = 0;
}

// параметризованный конструктор
LongNumber::LongNumber(size_t size) 
{
    _size = size;
    _digits = new char[_size + 1];
    for(int i = 0; i < _size; i++) _digits[i] = '0';
    _digits[_size] = '\0';
}

LongNumber::LongNumber(const char *array) 
{
    _size = 0;
    _digits = nullptr;
    size_t i = 0;

    while (array[i] != '\0') 
    {
        _size++;
        i++;
    }

    delete[] _digits;
    _digits = new char[_size];

    for (i = 0; i < _size; i++) {
        _digits[i] = array[i];
    }
}

// конструктор копирования
LongNumber::LongNumber(const LongNumber &other) 
{
    _size = other._size;
    if(_size == 0) _digits = nullptr;
    else
    {
        _digits = new char[_size + 1];
        for(int i = 0; i < _size; i++) _digits[i] = other._digits[i];
        _digits[_size] = '\0';
    }
}

// деструктор
LongNumber::~LongNumber() 
{
    delete[] _digits;
    _digits = nullptr;
    _size = 0;
}

// оператор присваивания
LongNumber &LongNumber::operator=(const LongNumber &other) 
{
    if (this == &other) return *this;

    delete[] _digits;

    _size = other._size;
    if(_size == 0) _digits = nullptr;
    else
    {
        _digits = new char[_size + 1];
        for(int i = 0; i < _size; i++) _digits[i] = other._digits[i];
        _digits[_size] = '\0';
    }

    return *this;
}

LongNumber LongNumber::operator+(const LongNumber &other) const 
{
    size_t shift = 0;
    size_t result_size = max(_size, other._size) + 1;
    int j = _size - 1, k = other._size - 1;
    LongNumber result(result_size);

    for (int i = result._size - 1; i > 0; i--) 
    {
        size_t sum = shift;

        if (j >= 0) sum += _digits[j] - '0';
        if (k >= 0) sum += other._digits[k] - '0';

        result._digits[i] = (sum % 10) + '0';
        shift = (sum / 10);
        j--;
        k--;
    }

    if (shift) result._digits[0] = shift;
    else result.RemovingLeadingZeros();

    return result;
}

// TODO: second. Сделать операторы (проблема c отрицательными числами)
LongNumber LongNumber::operator-(const LongNumber &other) const
{
    if (*this == other) return LongNumber("0");

    LongNumber result;
    int borrow = 0;

    // A > B
    if (*this > other)
    {
        result._size = _size;
        result._digits = new char[_size + 1];
        result._digits[_size] = '\0';

        int i = _size - 1;
        int j = other._size - 1;

        while (i >= 0)
        {
            int a = _digits[i] - '0';
            int b = (j >= 0) ? (other._digits[j] - '0') : 0;
            int diff = a - b - borrow;

            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
                borrow = 0;

            result._digits[i] = diff + '0';
            i--; j--;
        }

        return result.RemovingLeadingZeros();
    }

    else
    {
        result._size = other._size + 1;
        result._digits = new char[result._size + 1];
        result._digits[result._size] = '\0';
        result._digits[0] = '-';

        int i = _size - 1;
        int j = other._size - 1;
        int k = result._size - 1;

        while (j >= 0)
        {
            int a = (i >= 0) ? (_digits[i] - '0') : 0;
            int b = other._digits[j] - '0';
            int diff = b - a - borrow;

            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else borrow = 0;

            result._digits[k] = diff + '0';
            i--; j--; k--;
        }

        return result.RemovingLeadingZeros();
    }
}

// (-a) × b = -(a × b)
// a × (-b) = -(a × b)
// (-a) × (-b) = a × b
LongNumber LongNumber::operator * (const LongNumber &other) const
{
    if(_digits[0] == '0' || other._digits[0] == '0') return LongNumber("0");

    bool isNegative = (_digits[0] == '-') ^ (other._digits[0] == '-');
    int start_i = (_digits[0] == '-') ? 1 : 0;
    int start_j = (other._digits[0] == '-') ? 1 : 0;

    int carry = 0;
    int result_index = 0;
    int mul = 0;
    
    size_t new_size = (_size - start_i) + (other._size - start_j) + 1;
    LongNumber result(new_size);

    for(int i = _size - 1; i >= start_i; i--)
    {
        carry = 0;
        for(int j = other._size - 1; j >= start_j; j--)
        {
            result_index = (i - start_i) + (j - start_j);
            mul = (_digits[i] - '0') * (other._digits[j] - '0') + carry;
            result._digits[result_index] = (mul % 10) + '0';            // тут надо перезаписать на инты
            carry = mul / 10;
        }
        result._digits[(i - start_i)] += carry;             // тут надо перезаписать на инты
    }

    if(isNegative) result._digits[0] = '-';

    return result.RemovingLeadingZeros();
}

// LongNumber LongNumber::operator / (const LongNumber& other)
// {

// }

// LongNumber LongNumber::operator % (const LongNumber& other)
// {

// }

bool LongNumber::operator==(const LongNumber &other) const 
{
    if (_size != other._size)
        return false;

    for (int i = 0; i < _size; i++) {
        if (_digits[i] != other._digits[i])
        return false;
    }

    return true;
}

bool LongNumber::operator!=(const LongNumber &other) const 
{
    if (_size != other._size) return true;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] != other._digits[i])
        return true;
    }

    return false;
}

bool LongNumber::operator>(const LongNumber &other) const 
{
    // if(_size > other._size) return true;
    // if(_size < other._size) return false;
    if (_size != other._size) return _size > other._size;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] < other._digits[i]) return false;
        if (_digits[i] > other._digits[i]) return true;
    }

    return false;
}

bool LongNumber::operator>=(const LongNumber &other) const 
{
    // if(_size > other._size) return true;
    // if(_size < other._size) return false;
    if (_size != other._size) return _size > other._size;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] < other._digits[i]) return false;
        if (_digits[i] > other._digits[i]) return true;
    }

    return true;
}

bool LongNumber::operator<(const LongNumber &other) const 
{
    if (_size != other._size) return _size < other._size;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] > other._digits[i]) return false;
        if (_digits[i] < other._digits[i]) return true;
    }

    return false;
}

bool LongNumber::operator<=(const LongNumber &other) const 
{
    if (_size != other._size) return _size < other._size;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] > other._digits[i]) return false;
        if (_digits[i] < other._digits[i]) return true;
    }

    return true;
}

// TODO: first. Сделать все возможные операторы
bool LongNumber::operator==(const int &other) const 
{
    if (_size != lenght(other)) return false;

    int copy = other;

    for (int i = _size; i > 0; i--) 
    {
        int digit_int = copy % 10;
        if (_digits[i - 1] != digit_int + '0') return false;
        copy /= 10;
    }

    return true;
}

bool LongNumber::operator!=(const int &other) const 
{
    if (_size != lenght(other)) return true;

    int copy = other;
    int digit_int = 0;

    for (int i = _size; i > 0; i--) 
    {
        digit_int = copy % 10;
        if (_digits[i - 1] != digit_int + '0') return true;
        copy /= 10;
    }

    return false;
}

bool LongNumber::operator<(const int &other) const 
{
    int lenght_int = lenght(other);
    if (_size < lenght_int) return true;
    else if (_size > lenght_int) return false;

    int divisor = 1;
    int digit_int = 0;
    int copy = other;

    // TODO: вынести в отдельную функцию
    for (int i = copy / 10; i != 0; i /= 10) {
        divisor *= 10;
    }

    for (int i = 0; i < _size; i++) 
    {
        digit_int = (int)(copy / divisor) % 10;
        if (_digits[i] - '0' > digit_int) return false;
        if (_digits[i] - '0' < digit_int) return true;
        copy %= divisor;
        divisor /= 10;
    }

    return false;
}

bool LongNumber::operator<=(const int &other) const 
{
    int lenght_int = lenght(other);
    if (_size < lenght_int) return true;
    else if (_size > lenght_int) return false;

    int divisor = 1;
    int digit_int = 0;
    int copy = other;

    // TODO: вынести в отдельную функцию
    for (int i = copy / 10; i != 0; i /= 10) {
        divisor *= 10;
    }

    for (int i = 0; i < _size; i++) 
    {
        digit_int = (int)(copy / divisor) % 10;
        if (_digits[i] - '0' > digit_int) return false;
        else if (_digits[i] - '0' < digit_int) return true;
        copy %= divisor;
        divisor /= 10;
    }

    return true;
}

bool LongNumber::operator>(const int &other) const 
{
    int lenght_int = lenght(other);

    if (_size > lenght_int) return true;
    else if (_size < lenght_int) return false;

    int divisor = 1;
    int digit_int = 0;
    int copy = other;

    for (int i = copy / 10; i != 0; i /= 10) {
        divisor *= 10;
    }

    for (int i = 0; i < _size; i++) 
    {
        digit_int = (copy / divisor) % 10;
        if (_digits[i] - '0' > digit_int) return true;
        else if (_digits[i] - '0' < digit_int) return false;
        divisor /= 10;
    }

    return false;
}

bool LongNumber::operator>=(const int &other) const 
{
    int lenght_int = lenght(other);

    if (_size > lenght_int)
        return true;
    else if (_size < lenght_int)
        return false;

    int divisor = 1;
    int digit_int = 0;
    int copy = other;

    for (int i = copy / 10; i != 0; i /= 10) {
        divisor *= 10;
    }

    for (int i = 0; i < _size; i++) 
    {
        digit_int = (copy / divisor) % 10;
        if (_digits[i] - '0' > digit_int) return true;
        else if (_digits[i] - '0' < digit_int) return false;
        divisor /= 10;
    }

    return true;
}

int LongNumber::lenght(int number) const 
{
    if (number == 0) return 1;

    int result = 0;
    number = abs(number);

    while (number != 0) 
    {
        number /= 10;
        result++;
    }

    return result;
}

void LongNumber::print() 
{
    if (_size == 0 || _digits == nullptr) return;
    for (int i = 0; i < _size; i++) {
        cout << _digits[i];
    }
    cout << endl;
}

const LongNumber LongNumber::resize(const size_t &size) const 
{
    if (_size == size) return *this;

    char *new_digits = new char[size]();

    for (int i = 0; i < size - _size; i++) {
        new_digits[i] = '0';
    }

    int j = 0;
    for (int i = size - _size; i < size; i++) {
        new_digits[i] = _digits[j++];
    }

    // delete[] _digits;
    // _digits = new_digits;
    // _size = size;

    // return *this;
    return new_digits;
}

const LongNumber &LongNumber::findMax(const LongNumber &first,
                                      const LongNumber &second) {
    if (first._size > second._size) return first;
    else if (first._size < second._size) return second;

    for (int i = 0; i < _size; i++) 
    {
        if (first._digits[i] > second._digits[i]) return first;
        else if (first._digits[i] < second._digits[i]) return second;
    }

    return first;
}

LongNumber &LongNumber::RemovingLeadingZeros() 
{
    if(_size == 0 || _digits == nullptr) return *this;

    int start = 0;                                          // индекс начала значащих цифр

    bool is_negative = false;
    if(_digits[0] == '-')
    {
        is_negative = true;
        start = 1;
    }

    while(start < _size && _digits[start] == '0') start++;

    if(start == _size)
    {
        delete[] _digits;
        _size = 1;
        _digits = new char[_size + 1];
        _digits[0] = '0';
        _digits[1] = '\0';

        return *this;
    }

    int newSize = _size - start - (is_negative ? 1 : 0);
    char* temp = new char[newSize + 1];

    int j = 0;
    if(is_negative) temp[j++] = '-';

    for(int i = start; i < _size; i++) {
        temp[j++] = _digits[i];
    }

    temp[j] = '\0';
    delete[] _digits;
    _digits = temp;
    _size = newSize;

    return *this;
}
