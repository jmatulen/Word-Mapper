#!/bin/sh
clang++ -Wall -std=c++11 maps2.cpp -o temp
./temp
cat single_digits.txt double_digits.txt triple_digits.txt quad_digits.txt > word_mappings.txt
rm single_digits.txt double_digits.txt triple_digits.txt quad_digits.txt temp
