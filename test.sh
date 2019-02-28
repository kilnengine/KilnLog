#!/bin/bash
cmake .
make
clang -o test test.c -I. -L. -lkilnlog
./test