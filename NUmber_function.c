// to to convert form one base to another
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
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

int main() {
    FILE *inputFile, *outputFile;
    char inputFileName[100], outputFileName[100];
    char num[100];
    int fromBase, toBase;
    char result[100];

    printf("Enter the input file name: ");
    scanf("%s", inputFileName);

    printf("Enter the output file name: ");
    scanf("%s", outputFileName);

    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    // Read input from the file line by line (assuming each line contains: number fromBase toBase)
    
    while (fscanf(inputFile, "%s %d %d", num, &fromBase, &toBase) ==3) {
        printf("Processing: Number = %s, From Base = %d, To Base = %d\n", num, fromBase, toBase);

        if (fromBase < 2 || fromBase > 36 || toBase < 2 || toBase > 36) {
            fprintf(outputFile, "Error: Invalid base(s) for number %s. Bases must be between 2 and 36.\n", num);
            continue; // Move to the next line in the input file
        }

        long long decimalNum = toDecimal(num, fromBase);

        if (decimalNum == -1) {
            fprintf(outputFile, "Error: Invalid number '%s' for base %d.\n", num, fromBase);
            continue; // Move to the next line in the input file
        }

        fromDecimal(decimalNum, toBase, result);

        fprintf(outputFile, "%s (base %d) = %s (base %d)\n", num, fromBase, result, toBase);
    }

    if (!feof(inputFile)) {
        fprintf(stderr, "Error reading input file. Input format should be: number fromBase toBase\n");
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Conversion complete. Results written to %s\n", outputFileName);

    return 0;
}
