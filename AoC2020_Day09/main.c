#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define nl printf("\n")

/*
   [35   35   35
    20  [20   20
    15   15  [15
    25   25   25
    47]  47   47
    (40) 40]  40
    62   (62) 62]
    55   ...  (55)
    65        ...
    95
    102
    117
    150
    182
    127
    219
    299
    277
    309
    576 
*/

void rewindFile(FILE * input)
{
    fseek(input, 0, SEEK_SET);
}

int readLines(FILE * input)
{
    int numLines = 0;
    char currCh; // hi Currch :)
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '\n') numLines++;
    }
    rewindFile(input);
    return numLines;
}

void populateNumbers(FILE * input, long long unsigned int numbers[], int numLines)
{
    for(int i = 0; i < numLines; i++)
    {
        fscanf(input, "%lld", &numbers[i]);
    }

    rewindFile(input);
}

void printArray(long long unsigned int array[], int numLines)
{
    for(int i = 0; i < numLines; i++)
    {
        printf("[%lld]", array[i]);
    }
    nl;
}

int main(int argc, const char *argv[])
{
    if(!(argc >= 3)) 
    {
        printf("ERROR: Too few arguments (must have preamble size and file input.)\n");
        return 1;
    }
    FILE * input = fopen(argv[2], "r");
    int fileLines = readLines(input); 
    int preambleLength = atoi(argv[1]);
    long long unsigned int numbers[fileLines];
    long long unsigned int special = 0;
    int matchFlag = false;
    int i = 0, j = 1, k = 2;

    // Grab all numbers from file and place them into numbers array
    populateNumbers(input, numbers, fileLines);
    // show the numbers array
    printArray(numbers, fileLines);
    
    for(i = 0; i < fileLines - preambleLength; i++)
    {
        matchFlag = false;
        for(j = i; j < (preambleLength) + i; j++)
        {
            for(k = j + 1; k < (preambleLength) + i; k++)
            {
                if(numbers[j] + numbers[k] == numbers[i+preambleLength])
                {
                    matchFlag = true;
                }
            } 
        }
        if(!matchFlag) break;
    }

    printf("%lld\n", numbers[i+preambleLength]);
    return 0;
}
