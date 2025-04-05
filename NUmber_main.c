// to to convert form one base to another
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
#include "number.h"
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
