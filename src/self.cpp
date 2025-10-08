#include "../include/self.h"

using namespace std;

Number::Number() {
  this->_arr = nullptr;
  this->_size = 0;
}

Number::Number(size_t size) {
  this->_size = size;
  this->_arr = new int[size]{0};
}

int Number::operator[](const size_t &other) { return _arr[other]; }

void Number::operator=(const Number &other) {
  if (this == &other)
    return;

  this->_size = other._size;
  delete[] this->_arr;
  this->_arr = new int[_size];

  for (int i = 0; i < _size; i++) {
    this->_arr[i] = other._arr[i];
  }
}

void Number::foo() {
  for (int i = 0; i < _size; i++)
    _arr[i] = i;
}

Number::Number(const Number &other) {
  this->_size = other._size;
  this->_arr = new int[_size];
  for (int i = 0; i < _size; i++) {
    this->_arr[i] = other._arr[i];
  }
}

Number::~Number() {
  this->_size = 0;
  delete[] _arr;
  this->_arr = nullptr;
}
