#!/bin/bash
for t in 1 2 4 8 12 16 20 24 32
do
  for n in 1 10 100 1000 10000 100000 500000 1000000
  do
     g++   proj1.cpp  -DNUMT=$t -DNUMTRIALS=$n  -o proj  -lm  -fopenmp
    ./proj
  done
done
