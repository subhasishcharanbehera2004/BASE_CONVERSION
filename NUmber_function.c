
#include "number.h"

// Function to convert a digit character to its integer value
int val(char c) {
    if (c >= '0' && c <= '9')
        return (int)c - '0';
    else if (c >= 'A' && c <= 'Z')
        return (int)c - 'A' + 10;
    else if (c >= 'a' && c <= 'z')
        return (int)c - 'a' + 10;
    return -1; // Invalid character
}

// Function to convert an integer value to its digit character
char chr(int v) {
    if (v >= 0 && v <= 9)
        return (char)v + '0';
    else if (v >= 10 && v <= 35)
        return (char)v - 10 + 'A';
    return '\0'; // Should not happen for valid bases
}

// Function to convert a number from any base to base 10
long long toDecimal(char *num, int base) {
    long long decimal = 0;
    int len = strlen(num);
    long long power = 1;

    for (int i = len - 1; i >= 0; i--) {
        int digit = val(num[i]);

        if (digit < 0 || digit >= base) {
            fprintf(stderr, "Invalid digit '%c' for base %d\n", num[i], base);
            return -1; // Indicate an error
        }

        decimal += digit * power;
        power *= base;
    }
    return decimal;
}

// Function to convert a base 10 number to any base
char* fromDecimal(long long num, int base, char *result) {
    int index = 0;

    if (num == 0) {
        result[index++] = '0';
        result[index] = '\0';
        return result;
    }

    while (num > 0) {
        result[index++] = chr(num % base);
        num /= base;
    }
    result[index] = '\0';

    // Reverse the result string
    int start = 0;
    int end = index - 1;
    while (start < end) {
        char temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }
    return result;
}


  
         
