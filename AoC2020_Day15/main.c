#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "./aoc2020.h"

#define MAX_LENGTH 2020
#define LINE_MAX 100

void populateInitialAges(FILE * input, uint64_t * ages)
{
    char currCh; // VALIANT RETURN
    size_t currInx = 0;

    while((currCh = fgetc(input)) != EOF)
    {
        if(isdigit(currCh))
        {
            ungetc(currCh, input);
            fscanf(input, "%lu,", &ages[currInx]);
            currInx++;
        }
    }

    fseek(input, 0, SEEK_SET); //be kind, rewind
}


int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Error: No input file specified.\n");
        return 1;
    }
    FILE * input = fopen(argv[1], "r");
    INPUT_NULL_CHECK;

    size_t numCommas = countCharacterInFile(input, ',');

    uint64_t * ages = malloc(sizeof(uint64_t)*MAX_LENGTH);
    int currTurn = numCommas+1;
    memset(ages, 0, sizeof(int)*MAX_LENGTH);

    populateInitialAges(input, ages);

    for(size_t i = numCommas; i < MAX_LENGTH; i++)
    {
        uint64_t currAge = ages[i]; 
        for(int j = i-1; j >= 0; j--)
        {
            if(ages[j] == currAge)
            {
                ages[i+1] = currTurn - (j+1);
                break;
            }
        }
        currTurn++;
    }

    // 0,3,6,0,3,3,1,0,4,0
    for(size_t i = 0; i < MAX_LENGTH; i++)
    {
        printf("[%lu]", ages[i]);
    }
    printf("\n");

    free(ages);
    
    return 0;
}
