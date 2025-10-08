#pragma once

#include <iostream>

using namespace std;

class Number
{
    int* _arr;
    size_t _size;

public:
    Number();
    Number(size_t size);
    Number(const Number& number);
    ~Number();

    void operator = (const Number& other);
    int operator [] (const size_t& other);
    
    void foo();
};