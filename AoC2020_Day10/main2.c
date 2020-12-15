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

void initializeBinaryJoltages(int binaryJoltages[], int numLines)
{
    for(int i = 0; i < numLines; i++)
    {
        binaryJoltages[i] = 0;
    }
}

void compareBinaryJoltages(int binaryJoltages[], int joltages[], int numLines)
{
    for(int i = 0; i < numLines; i++)
    {
        binaryJoltages[joltages[i]] = 1;
    }
}

void printArray(int array[], int numLines)
{
    for(int i = 0; i < numLines; i++)
    {
        printf("[%d]", array[i]);
    }
    nl;
}

int main(int argc, const char *argv[])
{
    /*
    if(argc < 2)
    {
        printf("Error: no input file.\n");
        return 1;
    }*/
    //FILE * input = fopen(argv[1], "r");
    FILE * input = fopen("./testinput.txt", "r");
    if(input == NULL)
    {
        printf("Error: invalid file.\n");
        return 1;
    }
    int fileLines = countLines(input);
    fileLines += 2;
    //printf("%d\n", fileLines); // 13
    //int numJoltages = fileLines + 2;
    //printf("%d\n", numJoltages);//13
    int joltages[fileLines];
    populateJoltages(input, joltages, fileLines-2);
    printArray(joltages, fileLines);
    joltages[fileLines - 2] = 0;
    printArray(joltages, fileLines);
    int maxJoltage = getMaxJoltage(joltages, fileLines)+3;
    int binaryJoltages[maxJoltage];
    joltages[fileLines - 1] = maxJoltage;
    printArray(joltages, fileLines);
    qsort(joltages, fileLines, sizeof(int), cmpfunc);
    initializeBinaryJoltages(binaryJoltages, maxJoltage+1);
    compareBinaryJoltages(binaryJoltages, joltages, fileLines+1);
    printArray(joltages, fileLines+1);
    printArray(binaryJoltages, maxJoltage+1);

    for(int i = 3; i < maxJoltage+1; i++)
    {
        if(binaryJoltages[i])
        {
            binaryJoltages[i] = binaryJoltages[i-3]+binaryJoltages[i-2]+binaryJoltages[i-1];
        }
        printf("%d ", binaryJoltages[i]);
    }
    nl; 
    printf("%d\n", binaryJoltages[maxJoltage]);

    return 0;
}
