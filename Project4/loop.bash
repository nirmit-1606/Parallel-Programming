#!/bin/bash

#Array Size:
for n in 1024 65536 524288 1048576 2097152 4194304 8388608
do
	g++ -DARRAYSIZE=$n project4.cpp -o proj4 -lm -fopenmp
	./proj4
done
