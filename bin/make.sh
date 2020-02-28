#!/bin/bash

echo "starting..."

g++ -c ../source/date_from_cnab.cpp -I .. -o libdate_from_cnab.o
ar rcs libdate_from_cnab.a libdate_from_cnab.o
g++ -c ../source/main.cpp -I .. -o main.o
g++ -o main.exe main.o -I . -L . -l date_from_cnab
