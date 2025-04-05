// to to convert form one base to another
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Function to convert a digit character to its integer value
int val(char c) ;

// Function to convert an integer value to its digit character
char chr(int v) ;


// Function to convert a number from any base to base 10
long long toDecimal(char *num, int base);
char* fromDecimal(long long num, int base, char *result);

