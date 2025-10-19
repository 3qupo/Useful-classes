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
    _isNegative = false;
}

// параметризованный конструктор
LongNumber::LongNumber(const size_t size) 
{
    _size = size;
    _digits = new char[_size + 1];
    for(int i = 0; i < _size; i++) _digits[i] = '0';
    _digits[_size] = '\0';
    _isNegative = false;
}

LongNumber::LongNumber(const char *array) 
{
    if(array == nullptr || array[0] == '\0')
    {
        _size = 1;
        _digits = new char[2];
        _digits[0] = '0';
        _digits[1] = '\0';
        _isNegative = false;
        return;
    }

    size_t length = 0;
    while (array[length] != '\0') {
        length++;
    }
    
    size_t startIndex = 0;
    if(array[0] == '-')
    {
        _isNegative = true;
        startIndex = 1;
        _size = length - 1;
    }
    else
    {
        _isNegative = false;
        _size = length;
    }

    _digits = new char[_size + 1];

    for(size_t i = 0; i < _size; i++) {
        _digits[i] = array[startIndex + i];
    }

    _digits[_size] = '\0';
}

// конструктор копирования
LongNumber::LongNumber(const LongNumber &other) 
{
    _size = other._size;
    _isNegative = other._isNegative;
    if(_size == 0) _digits = nullptr;
    else
    {
        _digits = new char[_size + 1];
        for(size_t i = 0; i < _size; i++) _digits[i] = other._digits[i];
        _digits[_size] = '\0';
    }
}

// деструктор
LongNumber::~LongNumber() 
{
    delete[] _digits;
    _digits = nullptr;
    _size = 0;
    _isNegative = false;
}

// оператор присваивания
LongNumber &LongNumber::operator = (const LongNumber &other) 
{
    if (this == &other) return *this;

    delete[] _digits;

    _size = other._size;
    _isNegative = other._isNegative;
    if(_size == 0) _digits = nullptr;
    else
    {
        _digits = new char[_size + 1];
        for(size_t i = 0; i < _size; i++) _digits[i] = other._digits[i];
        _digits[_size] = '\0';
    }

    return *this;
}

char& LongNumber::operator [] (const size_t index) 
{   
    if (index >= _size) throw out_of_range("Index out of range\n");
    return _digits[index];
}

LongNumber LongNumber::operator + (const LongNumber &other) const 
{
    if(!_isNegative && !other._isNegative) return addAbsolute(other);
    if(_isNegative && !other._isNegative)
    {
        LongNumber result = addAbsolute(other);
        result._isNegative = true;
        return result;
    }

    if(_isNegative && !other._isNegative) return *this - other;
    if(!_isNegative && other._isNegative) return other - *this;

    return LongNumber("0");
}

LongNumber LongNumber::addAbsolute(const LongNumber& other) const
{
    size_t shift = 0;
    size_t sum = 0;
    size_t result_size = max(_size, other._size) + 1;
    int j = _size - 1; 
    int k = other._size - 1;
    LongNumber result(result_size);

    for(size_t i = result_size - 1; i > 0; i--)
    {
        if(j >= 0) sum += _digits[i] - '0';
        if(k >= 0) sum += other._digits[i] - '0';

        result._digits[i] = (sum % 10) + '0';
        shift = sum / 10;

        j--; k--;
    }

    result.RemovingLeadingZeros();
    return result;
}


LongNumber LongNumber::operator - (const LongNumber &other) const
{
    if(!_isNegative && !other._isNegative)
    {
        LongNumber temp = *this;
        temp._isNegative = false;
        LongNumber result = temp + other;
        result._isNegative = true;
        return result;
    }
    else if(!_isNegative && other._isNegative)
    {
        LongNumber temp = other._isNegative;
        temp._isNegative = false;
        return *this + temp;
    }
    else if(_isNegative && other._isNegative)
    {
        LongNumber temp1 = *this;
        LongNumber temp2 = other;
        temp1._isNegative = false;
        temp2._isNegative = false;
        return temp2 - temp1;
    }

    if(*this == other) return LongNumber("0");

    LongNumber result;

    if (*this > other)
    {
        result._size = _size;
        result._isNegative = _isNegative;
        result._digits = new char[_size + 1];
        result._digits[_size] = '\0';

        int i = _size - 1;
        int j = other._size - 1;
        int borrow = 0;

        while (i > 0)
        {
            int a = _digits[i] - '0';
            int b = (j >= 0) ? (other._digits[j] - '0') : 0;
            int diff = a - b - borrow;

            if(diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else borrow = 0;

            result._digits[i] = diff + '0';
            i--; j--;
        }
    }

    else
    {
        result._size = other._size;
        result._isNegative = other._isNegative;
        result._digits = new char[other._size + 1];
        result._digits[_size] = '\0';

        int i = _size - 1;
        int j = other._size - 1;
        int borrow = 0;

        while (j >= 0)
        {
            int a = (i >= 0) ? (_digits[i] - '0') : 0;
            int b = other._digits[j] - '0';
            int diff = b - a - borrow;

            if(diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else borrow = 0;

            result._digits[i] = diff + '0';
            i--; j--;
        }
    }

    return result.RemovingLeadingZeros();
}

// (-a) × b = -(a × b)
// a × (-b) = -(a × b)
// (-a) × (-b) = a × b
LongNumber LongNumber::operator * (const LongNumber &other) const 
{
    if (_digits[0] == '0' || other._digits[0] == '0') return LongNumber("0");

    bool isNegative = (_digits[0] == '-') ^ (other._digits[0] == '-');
    int start_i = (_digits[0] == '-') ? 1 : 0;
    int start_j = (other._digits[0] == '-') ? 1 : 0;

    size_t new_size = (_size - start_i) + (other._size - start_j) + 1;
    LongNumber result(new_size);

    for (int i = _size - 1; i >= start_i; --i) 
    {
        int getThis = _digits[i] - '0';
        int carry = 0;

        for (int j = other._size - 1; j >= start_j; --j) 
        {
            int getOther = other._digits[j] - '0';
            int pos = (i - start_i) + (j - start_j) + 1;

            int sum = (result._digits[pos] - '0') + getThis * getOther + carry;
            result._digits[pos] = (sum % 10) + '0';
            carry = sum / 10;
        }

        int pos = (i - start_i);
        result._digits[pos] = ((result._digits[pos] - '0') + carry) + '0';
    }

    result = result.RemovingLeadingZeros();

    if (isNegative && result._digits[0] != '0') 
    {
        for (int i = result._size; i > 0; --i) {
            result._digits[i] = result._digits[i - 1];
        }

        result._digits[0] = '-';
    }

    return result;
}


LongNumber LongNumber::operator / (const LongNumber& other) const
{
    LongNumber result;
    
    return result;
}

LongNumber LongNumber::operator % (const LongNumber& other) const
{
    LongNumber result;

    return result;
}

// TODO: you need to check it
LongNumber LongNumber::operator + (const int& other) const
{
    if(other == 0) return *this;
    if(_size == 0) return LongNumber(other);

    size_t shift = 0;
    size_t sum = 0;
    int copy_other = other;
    size_t result_size = max(static_cast<int>(getSize()), length(other)) + 1;
    LongNumber result(result_size);
    size_t j = getSize() - 1;
    size_t k = length(other) - 1;
    size_t index_this = getSize() - 1;

    for(size_t i = result_size - 1; i > 0; i--)
    {
        sum = shift;

        if(index_this < getSize())
        {
            sum += _digits[index_this] - '0';
            if(index_this > 0) index_this--;
        }
        sum += _digits[i] - '0';
        copy_other > 0 ? (sum += copy_other % 10) : sum += 0;

        result._digits[i] = (sum % 10) + '0';
        shift = sum / 10;

        j--; 
        if(copy_other > 0) copy_other /= 10;
    }

    if(shift) result._digits[0] = shift + '0';
    else result.RemovingLeadingZeros();

    return result;
}

LongNumber LongNumber::operator - (const int& other) const
{
    return *this;
}

LongNumber LongNumber::operator * (const int& other) const
{
    return *this;
}

LongNumber LongNumber::operator / (const int& other) const
{
    return *this;
}

LongNumber LongNumber::operator % (const int& other) const
{
    return *this;
}

bool LongNumber::operator == (const LongNumber &other) const 
{
    if (_isNegative != other._isNegative) return false;
    if (_size != other._size) return false;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] != other._digits[i])
        return false;
    }

    return true;
}

bool LongNumber::operator != (const LongNumber &other) const 
{
    if (_isNegative != other._isNegative) return true;
    if (_size != other._size) return true;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] != other._digits[i])
        return true;
    }

    return false;
}

bool LongNumber::operator > (const LongNumber &other) const 
{
    if (_isNegative != other._isNegative) return _isNegative > other._isNegative;
    if (_size != other._size) return _size > other._size;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] < other._digits[i]) return false;
        if (_digits[i] > other._digits[i]) return true;
    }

    return false;
}

bool LongNumber::operator >= (const LongNumber &other) const 
{
    if (_isNegative != other._isNegative) return _isNegative > other._isNegative;
    if (_size != other._size) return _size > other._size;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] < other._digits[i]) return false;
        if (_digits[i] > other._digits[i]) return true;
    }

    return true;
}

bool LongNumber::operator < (const LongNumber &other) const 
{
    if (_isNegative != other._isNegative) return _isNegative;
    if (_size != other._size) return _size < other._size;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] > other._digits[i]) return false;
        if (_digits[i] < other._digits[i]) return true;
    }

    return false;
}

bool LongNumber::operator <= (const LongNumber &other) const 
{
    if (_isNegative != other._isNegative) return _isNegative < other._isNegative;
    if (_size != other._size) return _size < other._size;

    for (int i = 0; i < _size; i++) 
    {
        if (_digits[i] > other._digits[i]) return false;
        if (_digits[i] < other._digits[i]) return true;
    }

    return true;
}

bool LongNumber::operator == (const int &other) const 
{
    if (_isNegative && other > 0) return false;
    if (!_isNegative && other < 0) return false;
    if (_size != length(other)) return false;

    int copy = other;

    for (int i = _size; i > 0; i--) 
    {
        int digit_int = copy % 10;
        if (_digits[i - 1] != digit_int + '0') return false;
        copy /= 10;
    }

    return true;
}

bool LongNumber::operator != (const int &other) const 
{
    if (_isNegative && other > 0) return true;
    if (!_isNegative && other < 0) return true;
    if (_size != length(other)) return true;

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

bool LongNumber::operator < (const int &other) const 
{
    if (_isNegative && other > 0) return false;
    if (!_isNegative && other < 0) return false;
    int lenght_int = length(other);
    if (_size < lenght_int) return true;
    if (_size > lenght_int) return false;

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

bool LongNumber::operator <= (const int &other) const 
{
    if (_isNegative && other > 0) return true;
    if (!_isNegative && other < 0) return true;
    int lenght_int = length(other);
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

bool LongNumber::operator > (const int &other) const 
{
    if (_isNegative && other > 0) return false;
    if (!_isNegative && other < 0) return false;
    int lenght_int = length(other);

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

bool LongNumber::operator >= (const int &other) const 
{
    if (_isNegative && other > 0) return false;
    if (!_isNegative && other < 0) return false;
    int lenght_int = length(other);

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

    return true;
}

int LongNumber::length(int number) const 
{
    if (number == 0) return 1;

    size_t len = 0;
    int temp = abs(number);
    while (temp != 0) 
    {
        number /= 10;
        len++;
    }

    return len;
}

size_t LongNumber::getSize() const {
    return _size;
}

bool LongNumber::getIsNegative() const {
    return _isNegative;
}

void LongNumber::print() 
{
    if (_size == 0 || _digits == nullptr) return;
    if(_isNegative) cout << "-";
    for (int i = 0; i < _size; i++) {
        cout << _digits[i];
    }
    cout << endl;
}

LongNumber &LongNumber::RemovingLeadingZeros() 
{
    if(_size == 0 || _digits == nullptr) return *this;

    int start = 0;                                          // индекс начала значащих цифр

    if(_isNegative) start = 1;

    while(start < _size && _digits[start] == '0') start++;

    if(start > 0)
    {
        size_t newSize = _size - start;
        char* newDigits = new char[newSize + 1];

        for(size_t i = 0; i < newSize; i++) {
            newDigits[i] = _digits[start + i];
        }
        newDigits[newSize] = '\0';

        delete[] _digits;
        _digits = newDigits;
        _size = newSize;
    }

    if(_size == 1 && _digits[0] == '0') _isNegative = false;

    return *this;
}


// trash
// TODO: why do u need it?
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
