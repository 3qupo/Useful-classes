#!/bin/bash
g++ -c networks/database/EchoDatabase.cpp networks/database/Database.cpp ../main.cpp structs/LongNumber.cpp structs/Matrix.cpp structs/Generator.cpp tests.cpp algoritms/fermat_factorization.cpp
g++ -o ../main EchoDatabase.o Database.o main.o LongNumber.o Matrix.o Generator.o tests.o fermat_factorization.o -lpthread -lpq
../main
