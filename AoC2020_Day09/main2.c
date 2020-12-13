#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define nl printf("\n")

void rewindFile(FILE * input)
{
    fseek(input, 0, SEEK_SET);
}

long long unsigned int min(long long unsigned int a, long long unsigned int b)
{
    return a*(a < b) + b*(a >= b);
}


long long unsigned int max(long long unsigned int a, long long unsigned int b)
{
    return a*(a >= b) + b*(a < b);
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
    long long unsigned int answer;
    long long unsigned int compare;
    long long unsigned int compareMin = INT_MAX;
    long long unsigned int compareMax;
    int matchFlag = false;
    int i = 0, j = 1, k = 2;

    // Grab all numbers from file and place them into numbers array
    populateNumbers(input, numbers, fileLines);
    // show the numbers array
    // printArray(numbers, fileLines);
    
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

    answer = numbers[i+preambleLength];
    matchFlag = false;

    for(i = 0; i < fileLines; i++)
    {
        if(matchFlag) break;
        compare = 0;     
        compareMin = ULLONG_MAX;
        compareMax = 0;
        for(j = i; j < fileLines; j++)
        {
            compare += numbers[j];
            if(compare == answer) 
            {    
                matchFlag = true;
                //printf("Answer is %d\n", numbers[i] + numbers[j]);
                for(k = i; k <= j; k++)
                {
                    compareMin = min(compareMin, numbers[k]);
                    compareMax = max(compareMax, numbers[k]);
                }
                printf("The answer is: %lld\n", compareMin + compareMax);
            }                
        }
    }

    return 0;
}
