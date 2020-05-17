#!/bin/bash

echo "starting..."

g++ -c ../source/data_from_cnab.cpp -I .. -o libdata_from_cnab.o
g++ -c ../source/read_from_config.cpp -I .. -o libread_from_config.o
g++ -c ../lib/utility.cpp -I .. -o libutility.o
ar rcs libutility.a libutility.o
ar rcs libdata_from_cnab.a libdata_from_cnab.o
ar rcs libread_from_config.a libread_from_config.o
g++ -c ../source/main.cpp -I .. -o main.o
g++ -o main.exe main.o -I .. -L . -lread_from_config -lutility -ldata_from_cnab
