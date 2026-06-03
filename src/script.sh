#!/bin/bash
g++ -c ../main.cpp LongNumber.cpp Matrix.cpp Generator.cpp tests.cpp fermat_factorization.cpp
g++ -o ../main main.o LongNumber.o Matrix.o Generator.o tests.o fermat_factorization.o -lpthread
../main
