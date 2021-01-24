# Assignment 2

This programs includes five different functions that are a similar to C's libarry functions. 
Using the Taylor series, I was able to create an implemintation of Sin, Cos, Tan, and Exp.
Using Newton's method, I was able to create an implemintation for a Log function. 
Apart from implementing the functions, I compared how accurate my implementation was versus 
the math library's. The goal for this assignment was to get a deeper understanding on how 
functions we use in C work. 


## BUILD 
	$ clang -Wall -Werror -Wextra -Wpedantic -c mathlib-test.c
	$ clang -Wall -Werror -Wextra -Wpedantic -c mathlib.c
	$ clang -o mathlib-test mathlib-test.o  mathlib.o -lm
	

## Runing 
	$./mathlib-test

## Cleaning 
	$ rm -f mathlib-test *.0
