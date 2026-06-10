#!/bin/bash
g++ -c networks/database/EchoDatabase.cpp networks/database/Database.cpp ../main.cpp 
g++ -o ../main EchoDatabase.o Database.o main.o -lpthread -lpq
../main
