#pragma once

#include <iostream>
#include <cstring>

using namespace std;

class LongNumber
{
private:
    char* _digits;
    size_t _size;
    
public:
    LongNumber();
    LongNumber(const size_t size);
    LongNumber(const char* array);
    LongNumber(const LongNumber& other);
    ~LongNumber();

    LongNumber& operator = (const LongNumber& other);
    char& operator [] (const size_t index);
    LongNumber operator + (const LongNumber& other) const;
    LongNumber operator - (const LongNumber& other) const;
    LongNumber operator * (const LongNumber& other) const;
    LongNumber operator / (const LongNumber& other) const;
    LongNumber operator % (const LongNumber& other) const;

    LongNumber operator + (const int& other) const;
    LongNumber operator - (const int& other) const;
    LongNumber operator * (const int& other) const;
    LongNumber operator / (const int& other) const;
    LongNumber operator % (const int& other) const;

    bool operator == (const LongNumber& other) const;
    bool operator != (const LongNumber& other) const;
    bool operator > (const LongNumber& other) const;
    bool operator >= (const LongNumber& other) const;
    bool operator < (const LongNumber& other) const;
    bool operator <= (const LongNumber& other) const;

    bool operator == (const int& other) const;
    bool operator != (const int& other) const;
    bool operator > (const int& other) const;
    bool operator >= (const int& other) const;
    bool operator < (const int& other) const;
    bool operator <= (const int& other) const;

    size_t getSize() const;
    LongNumber& RemovingLeadingZeros();
    const LongNumber resize(const size_t& size) const;
    int length(int number) const;
    const LongNumber& findMax(const LongNumber& first, const LongNumber& second);
    void print(); 
};