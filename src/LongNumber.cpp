#include "../include/LongNumber.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>

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

    this->RemovingLeadingZeros();
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
    if(_isNegative && other._isNegative)
    {
        LongNumber result = addAbsolute(other);
        result._isNegative = true;
        return result;
    }

    if(_isNegative && !other._isNegative) 
    {
        int cmp = compareAbsolute(other);

        // -5 + +3
        if(cmp == 1)
        {
            LongNumber result = substractAbsolute(other);
            result._isNegative = true;
            return result;
        }

        // -3 + +5
        if(cmp == -1) 
        {
            LongNumber result = other.substractAbsolute(*this);
            return result;
        }
    }

    if(!_isNegative && other._isNegative)
    {
        int cmp = compareAbsolute(other);

        // 5 + -3
        if(cmp == 1) 
        {
            LongNumber result = substractAbsolute(other);
            return result;
        }
        

        // 3 + -5
        if(cmp == -1)
        {
            LongNumber result = other.substractAbsolute(*this);
            result._isNegative = true;
            return result;
        }
    }

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

    for(int i = result_size - 1; i >= 0; i--)
    {
        sum = shift;

        if(j >= 0) sum += _digits[j] - '0';
        if(k >= 0) sum += other._digits[k] - '0';

        result._digits[i] = (sum % 10) + '0';
        shift = sum / 10;

        j--; k--;
    }

    result.RemovingLeadingZeros();
    return result;
}

LongNumber LongNumber::operator - (const LongNumber &other) const
{
    if(*this == other) return LongNumber("0");

    if (!_isNegative && !other._isNegative)
    {
        int cmp = compareAbsolute(other);
        if(cmp >= 0) return substractAbsolute(other);
        else  
        {
            LongNumber result = other.substractAbsolute(*this);
            result._isNegative = true;
            return result;
        }
    }

    if(!_isNegative && other._isNegative) return this->addAbsolute(other);

    if(_isNegative && !other._isNegative) 
    {
        LongNumber result = this->addAbsolute(other);
        result._isNegative = true;
        return result;
    }

    if(_isNegative && other._isNegative)
    {
        LongNumber tempA = *this;
        LongNumber tempB = other;
        tempA._isNegative = false;
        tempB._isNegative = false;

        return tempB - tempA;
    }
    

    return LongNumber("0");
}

LongNumber LongNumber::substractAbsolute(const LongNumber& other) const
{
    int borrow = 0;
    int sub = 0;
    int i = _size - 1;
    int j = other._size - 1;
    LongNumber result(_size);   

    while(i >= 0)
    {
        int a = _digits[i] - '0';
        int b = (j >= 0) ? (other._digits[j] - '0') : 0;
        int diff = a - b - borrow;

        if(diff < 0)
        {
            diff += 10;
            borrow = 1;
        } else borrow = 0;

        result._digits[i] = diff + '0';
        i--; j--;
    }

    return result.RemovingLeadingZeros();
}


LongNumber LongNumber::operator * (const LongNumber &other) const 
{
    if ((_size == 1 && _digits[0] == '0') || (other._size == 1 && other._digits[0] == '0')) 
        return LongNumber("0");

    size_t result_size = _size + other._size;
    LongNumber result(result_size);
    result._isNegative = _isNegative ^ other._isNegative;

    for (int i = _size - 1; i >= 0; i--) 
    {
        int getThis = _digits[i] - '0';
        int carry = 0;

        for (int j = other._size - 1; j >= 0; j--) 
        {
            int getOther = other._digits[j] - '0';
            int pos = i + j + 1;

            int sum = (result._digits[pos] - '0') + getThis * getOther + carry;
            result._digits[pos] = (sum % 10) + '0';
            carry = sum / 10;
        }

        result._digits[i] = ((result._digits[i] - '0') + carry) + '0';
    }

    result = result.RemovingLeadingZeros();

    return result;
}

LongNumber LongNumber::operator / (const LongNumber& other) const
{
    if(other._size == 1 && other._digits[0] == '0') 
        throw std::invalid_argument("division by 0 is not possible!\n");

    if(_size == 1 && _digits[0] == '0') 
        return LongNumber("0");

    if(compareAbsolute(other) == -1) return LongNumber("0");

    if(compareAbsolute(other) == 0)
    {
        bool isNegative = _isNegative ^ other._isNegative;
        return isNegative ? LongNumber("-1") : LongNumber("1");
    }

    LongNumber dividend = *this;
    LongNumber divisor = other;
    LongNumber result;

    dividend._isNegative = false;
    divisor._isNegative = false;
    result._isNegative = _isNegative ^ other._isNegative;

    LongNumber remainder("0");   // остаток

    for(size_t i = 0; i < dividend.getSize(); i++)
    {
        remainder = remainder * 10 + LongNumber(std::string(1, dividend._digits[i]).c_str());

        int digit = 0;
        LongNumber product;

        for(int d = 9; d >= 0; d--)
        {
            LongNumber temp = divisor * LongNumber(std::to_string(d).c_str());
            if(temp.compareAbsolute(remainder) != 1)
            {
                digit = d;
                product = temp;
                break;
            }
        }

        result = result * 10 + LongNumber(std::to_string(digit).c_str());

        remainder = remainder - product;
    }

    result.RemovingLeadingZeros();
    
    return result;
}

LongNumber LongNumber::operator % (const LongNumber& other) const
{
    if(other.getSize() == 1 && other._digits[0] == '0') 
        throw std::invalid_argument("module by zero\n");
    if(*this == 0) return LongNumber("0");
    return *this - (other * (*this / other));
}

// TODO: you need to change      it
LongNumber LongNumber::operator + (const int& other) const
{
    LongNumber temp = LongNumber(std::to_string(other).c_str());

    return *this + temp;
}

LongNumber LongNumber::operator - (const int& other) const
{
    LongNumber temp = LongNumber(std::to_string(other).c_str());

    return *this - temp;
}

LongNumber LongNumber::operator * (const int& other) const
{
    LongNumber temp(std::to_string(other).c_str());
    return *this * temp;
}

LongNumber LongNumber::operator / (const int& other) const
{
    if (other == 0) throw std::invalid_argument("division by zero");
    LongNumber temp(std::to_string(other).c_str());
    return *this / temp;
}

LongNumber LongNumber::operator % (const int& other) const
{
    if (other == 0) throw std::invalid_argument("modulo by zero");
    LongNumber temp(std::to_string(other).c_str());
    return *this % temp;
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

    while(start < _size && _digits[start] == '0') start++;

    if(start > 0 && start < _size)
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

    else if(start == _size) 
    {
        delete[] _digits;
        _digits = new char[2];
        _digits[0] = '0';
        _digits[1] = '\0';
        _size = 1;
        _isNegative = false;
        return *this;
    }

    if(_size == 1 && _digits[0] == '0') _isNegative = false;

    return *this;
}

int LongNumber::compareAbsolute(const LongNumber& other) const
{
    if (_size > other._size) return 1;
    else if (_size < other._size) return -1;
    else if (_size == other._size)
    {
        for(int i = 0; i < _size; i++)
        {
            if(_digits[i] > other._digits[i]) return 1;
            if(_digits[i] < other._digits[i]) return -1;
        }
    }
    return 0;
}