#!/bin/sh
ecpg main.pgc
gcc -I/usr/include/postgresql -c main.c
gcc -o main main.o -L/usr/lib -lecpg
./main