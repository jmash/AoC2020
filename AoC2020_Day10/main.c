#include <stdio.h>
#include <stdlib.h>

#define nl printf("\n")

void rewindFile(FILE * input)
{
    fseek(input, 0, SEEK_SET);
}

int max(int a, int b)
{
    return a*(a >= b) + b*(a < b);
}

int cmpfunc (const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
}

int getMaxJoltage(int joltages[], int numLines)
{
    int maxJoltage = 0;
    for(int i = 0; i < numLines; i++)
    {
        maxJoltage = max(maxJoltage, joltages[i]);
    }

    return maxJoltage;
}

int countLines(FILE * input)
{
    char currCh; // our boi :D
    int numLines = 0;
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '\n') numLines++; 
    }
    rewindFile(input);

    return numLines;
}

void populateJoltages(FILE * input, int joltages[], int numLines)
{
    for(int i = 0; i < numLines; i++)
    {
        fscanf(input, "%d\n", &joltages[i]);
    }
}

void printArray(int array[], int numLines)
{
    for(int i = 0; i < numLines+2; i++)
    {
        printf("[%d]", array[i]);
    }
    nl;
}

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Error: no input file.\n");
        return 1;
    }
    FILE * input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Error: invalid file.\n");
        return 1;
    }
    int fileLines = countLines(input);
    //printf("%d\n", fileLines);
    int joltages[fileLines + 2];
    joltages[fileLines] = 0;
    populateJoltages(input, joltages, fileLines);
    int maxJoltage = getMaxJoltage(joltages, fileLines+1)+3;
    int onesAcc = 0;
    int threesAcc = 0;
    joltages[fileLines + 1] = maxJoltage;

    qsort(joltages, fileLines + 2, sizeof(int), cmpfunc);

    for(int i = 0; i < fileLines+2; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            if((joltages[i] + j) == joltages[i+1])
            {
                if(j == 1) onesAcc++;
                if(j == 3) threesAcc++;
                break;
            }
        }
    }

    printf("The answer is: %d\n", onesAcc*threesAcc);
    return 0;
}
