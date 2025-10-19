#!/bin/bash
g++ -c main.cpp LongNumber.cpp Matrix.cpp Generator.cpp tests.cpp
g++ -o main main.o LongNumber.o Matrix.o Generator.o tests.o -lpthread
./main