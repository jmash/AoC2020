#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define nl printf("\n")

void rewindFile(FILE * input)
{
    fseek(input, 0, SEEK_SET);
}

int countFileLines(FILE * input)
{
    int nlCount = 0;
    char currCh;
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '\n') nlCount++;
    }

    rewindFile(input);
    return nlCount;
}

void initializeBootCode(bool bootCode[], int length)
{
    for(int i = 0; i < length; i++)
    {
        bootCode[i] = 0;
    }
}


void printBootCode(bool bootCode[], int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%d ", bootCode[i]);
    }
    nl;
}

void populateInstructions(FILE * input, int length, char instructions[][4])
{
    for(int i = 0; i < length; i++)
    {
        fscanf(input, "%s %*d\n", instructions[i]);
    }

    rewindFile(input);
}

void printInstructions(char instructions[][4], int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%s\n", instructions[i]);
    }
}

void populateArguments(FILE * input, int length, int arguments[])
{
    for(int i = 0; i < length; i++)
    {
        fscanf(input, "%*s %d\n", &arguments[i]); 
    }
    rewindFile(input);
}

void printArguments(int arguments[], int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%d\n", arguments[i]);
    }
}

int main(int argc, const char *argv[])
{
    FILE * input = fopen("./input.txt", "r");
    char currCh; // welcome back Currch ^_^
    int fileLines = countFileLines(input); 
    // array of booleans that tells us which instructions have been visited.
    bool bootCode[fileLines]; 
    int accumulator = 0; // the global accumulator
    bool * bootCodePtr = bootCode;
    char instructions[fileLines][4];
    int instructionsInx = 0;
    int arguments[fileLines];
        
    initializeBootCode(bootCode, fileLines);

    populateInstructions(input, fileLines, instructions);
    //printInstructions(instructions, fileLines);

    populateArguments(input, fileLines, arguments);
    //printArguments(arguments, fileLines);
     
    while(!bootCode[instructionsInx])
    {
        bootCode[instructionsInx] = true;
        if(strcmp(instructions[instructionsInx], "nop") == 0)
        {
            instructionsInx += 1;
        }
        else if(strcmp(instructions[instructionsInx], "jmp") == 0)
        {
            instructionsInx += arguments[instructionsInx];
        }
        else if(strcmp(instructions[instructionsInx], "acc") == 0)
        {
            accumulator += arguments[instructionsInx];
            instructionsInx += 1;
        }
    }
    printf("Accumulator amount is: %d\n", accumulator);
    
    return 0;
}
