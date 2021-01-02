#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./aoc2020.h"

#define LINE_MAX 100
#define MAX_BITS 36

typedef struct
{
    uint64_t clearbits;
    uint64_t setbits;
} mask_t;

// (value | setbits) & ~clearbits
uint64_t applyMask(const mask_t * mask, uint64_t value)
{
   return (value | mask->setbits) & ~mask->clearbits; 
}

int64_t pow64T(size_t x, size_t y)
{
    int64_t total = x;
    if(y == 0) return 1;
    for(size_t i = 1; i < y; i++)
    {
        total *= x;
    }
    return total;
}

// convert decimal value to binary (assumes binary array in parameter is set to 0)
void valueToBinary(int64_t value, char * binaryArray, size_t arrayLength)
{
    while(value > 0)
    {
        size_t i = 0;
        int64_t base = 2;
        while(base <= value)
        {
            base = pow64T(2, i);
            if(pow64T(2, i+1) > value) break;
            i++;
        }
        binaryArray[arrayLength - i - 1] = 1;
        value -= base;
    }
}

size_t getGreatestMemoryAddress(FILE * input)
{
    char line[LINE_MAX];
    size_t currAddress = 0;
    size_t greatestAddress = 0;

    while(fgets(line, LINE_MAX, input) != NULL)
    {
        if(sscanf(line, "mem[%lu]", &currAddress) == 1)
        {
            greatestAddress = max(currAddress, greatestAddress); 
        }
    }

    fseek(input, 0, SEEK_SET);

    return greatestAddress;
}

mask_t parseMask(char maskString[MAX_BITS+1])
{
    //1 << Y;
    mask_t parsedMask;
    parsedMask.clearbits = 0;
    parsedMask.setbits = 0;

    for(size_t i = 0; i < MAX_BITS+1; i++)
    {
        if(maskString[i] == '0')
        {
            parsedMask.clearbits += ((1ULL) << (35 - i));
        }
        if(maskString[i] == '1')
        {
            parsedMask.setbits += ((1ULL) << (35 - i));
        }
    }
    
    return parsedMask;
}

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Error: No input file.\n");
        return 1;
    }
    FILE * input = fopen(argv[1], "r");

    if(input == NULL)
    {
        printf("Error: cannot open file.\n");
        return 1;
    }
    size_t greatestAddress = getGreatestMemoryAddress(input);
    uint64_t * memory = malloc(sizeof(uint64_t)*greatestAddress);
    memset(memory, 0, sizeof(uint64_t)*greatestAddress);
    
    char line[100];
    char mask[MAX_BITS+1];
    char binaryArray[MAX_BITS];

    uint64_t total = 0;
    mask_t currMask;

    while(fgets(line, 100, input) != NULL)
    {
        memset(binaryArray, 0, sizeof(char)*(MAX_BITS+1));
        uint64_t addr, value;
        if(sscanf(line, "mem[%lu] = %lu", &addr, &value) == 2)
        {
            valueToBinary(value, binaryArray, MAX_BITS);
            for(size_t i = 0; i < MAX_BITS; i++)
            {
                printf("%d", binaryArray[i]);
            }
            printf("\n");
            for(size_t i = 0; i < (MAX_BITS+1); i++)
            {
                printf("%c", mask[i]);
            }
            printf("\n");
            memset(binaryArray, 0, sizeof(char)*(MAX_BITS+1));
            valueToBinary(currMask.setbits, binaryArray, MAX_BITS);
            printf("setbits:\n");
            for(size_t i = 0; i < 36; i++)
            {
                printf("%d", binaryArray[i]);
            }
            printf("\n");
            memset(binaryArray, 0, sizeof(char)*(MAX_BITS+1));
            valueToBinary(currMask.clearbits, binaryArray, MAX_BITS);
            printf("clearbits:\n");
            for(size_t i = 0; i < 36; i++)
            {
                printf("%d", binaryArray[i]);
            }
            printf("\n");
            memory[addr] = applyMask(&currMask, value);
            memset(binaryArray, 0, sizeof(char)*(MAX_BITS+1));
            valueToBinary(applyMask(&currMask, value), binaryArray, MAX_BITS);
            for(size_t i = 0; i < 36; i++)
            {
                printf("%d", binaryArray[i]);
            }
            printf("\n");
            printf("%lu\n", applyMask(&currMask, value));
        } else if(sscanf(line, "mask = %s", mask) == 1)
        {
            currMask = parseMask(mask);
        }
    }
   
    for(uint64_t i = 0; i < greatestAddress+1; i++)
    {
        total += memory[i]; 
    }
    printf("%lu\n", total);
     

    free(memory);
}
