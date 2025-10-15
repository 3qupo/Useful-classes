#!/bin/bash
g++ -c main.cpp LongNumber.cpp Matrix.cpp Generator.cpp
g++ -o main main.o LongNumber.o Matrix.o Generator.o -lpthread
./main