#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./aoc2020.h"

#define MAX_BITS 36
#define LINE_MAX 100
#define OPERAND_SIZE 64

typedef size_t address_t;

typedef struct
{
    uint64_t clearbits;
    uint64_t setbits;
    size_t xbits;
} mask_t;

int cmpAddress_t (const void * a, const void * b) {
   address_t av = *(const address_t*)a;
   address_t bv = *(const address_t*)b;
   if(av == bv) return 0;
   else if(av < bv) return -1;
   else return 1;
}

int cmp64_t (const void * a, const void * b) {
   uint64_t av = *(const uint64_t*)a;
   uint64_t bv = *(const uint64_t*)b;
   if(av == bv) return 0;
   else if(av < bv) return -1;
   else return 1;
}

uint64_t jPDEP64(uint64_t src1, uint64_t src2)
{
    uint64_t temp = src1; 
    uint64_t mask = src2; 
    uint64_t dest = 0;
    size_t k = 0;

    for(size_t m = 0; m < OPERAND_SIZE; m++)
    {
        if((mask >> m) & 1)
        {
            dest += ((temp >> k) & 1)*((1ULL) << m);
            k++;
        }
    }

    return dest;
}

// (value | setbits) & ~clearbits
uint64_t applyMask(const mask_t * mask, uint64_t value)
{
   return (value | mask->setbits) & ~mask->clearbits; 
}

uint64_t getMappingSize(FILE * input)
{
    uint64_t total = 0;
    size_t currMaskXCount = 0;
    address_t addr = 0;
    char line[LINE_MAX];
    char mask[MAX_BITS+1];
    char * linePtr = line;

    while(fgets(line, LINE_MAX, input) != NULL)
    {
        if(sscanf(line, "mask = %s", mask) == 1)
        {
            currMaskXCount = 0;
            linePtr = line;
            while(*(linePtr) != '\0')
            {
                if(*(linePtr) == 'X') currMaskXCount++;
                linePtr++;
            }
        }
        if(sscanf(line, "mem[%lu]", &addr) == 1)
        {
            total += (1ULL) << currMaskXCount; 
        }
    }

    fseek(input, 0, SEEK_SET); // be kind rewind
    return total;
}

int64_t strToIntBinary(const char * str, size_t strLength, char onesCh)
{
    uint64_t total = 0;
    for(size_t i = 0; i < strLength; i++)
    {
        if(str[i] == onesCh)
        {
            total += (1ULL) << (strLength-i-1); 
        }
    }
     
    return total;
}

uint64_t getMaxedOutMask(char * mask, size_t maskLength)
{
    return strToIntBinary(mask, maskLength, '1') | strToIntBinary(mask, maskLength, 'X');
}

uint64_t getGreatestMaskAddress(FILE * input)
{
    char mask[MAX_BITS+1];
    char line[LINE_MAX];
    int64_t currMaxedOutVal = 0;
    int64_t maxMaxedOutVal = 0; 
    
    while(fgets(line, LINE_MAX, input) != NULL)
    {
        if(sscanf(line, "mask = %s", mask) == 1)
        {
            currMaxedOutVal = getMaxedOutMask(mask, MAX_BITS+1);
        }
        maxMaxedOutVal = max(currMaxedOutVal, maxMaxedOutVal);
    }

    fseek(input, 0, SEEK_SET);
    return maxMaxedOutVal;
}

uint64_t getGreatestAddress(FILE * input)
{
    char line[LINE_MAX];
    size_t currAddr = 0;
    size_t greatestAddr = 0;

    while(fgets(line, LINE_MAX, input) != NULL)
    {
        if(sscanf(line, "mem[%lu]", &currAddr) == 1)
        {
            greatestAddr = max(currAddr, greatestAddr);
        } 
    }

    fseek(input, 0, SEEK_SET);
    return greatestAddr;
}

int64_t binaryToValue(char * binaryArray, size_t arrayLength)
{
    int64_t total = 0;
    for(size_t i = 0; i < arrayLength; i++)
    {
        total += (binaryArray[arrayLength-i-1] << i); 
    }

    return total;
}

// convert decimal value to binary (assumes binary array in parameter is set to 0)
void valueToBinary(int64_t value, char * binaryArray, size_t arrayLength)
{
    int64_t x = value;
    for(size_t i = 0; i < arrayLength; i++)
    {
        binaryArray[arrayLength-i-1] = (x >> i) & 1;
    }
}

mask_t parseMask(const char * maskString, size_t maskLength)
{
    mask_t parsedMask;
    parsedMask.clearbits = strToIntBinary(maskString, maskLength, '0');
    parsedMask.setbits = strToIntBinary(maskString, maskLength, '1');
    parsedMask.xbits = strToIntBinary(maskString, maskLength, 'X');
    
    return parsedMask;
}

size_t countXsInMask(const char * maskString, size_t maskLength)
{
    size_t xCount = 0;
    for(size_t i = 0; i < maskLength; i++)
    {
        if(maskString[i] == 'X') xCount++;
    }

    return xCount;
}

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        printf("Error: No input file specified.\n");
        return 1;
    }
    FILE * input = fopen(argv[1], "r");

    if(input == NULL)
    {
        printf("Error: cannot open file.\n");
        return 1;
    }

    uint64_t mappingSize = getMappingSize(input);
    uint64_t * mapping = malloc(sizeof(uint64_t)*mappingSize);
    memset(mapping, 0, sizeof(uint64_t)*mappingSize);
    uint64_t greatestAddress = getGreatestAddress(input);
 
    char line[LINE_MAX];
    char mask[MAX_BITS+1];
    char binaryArray[MAX_BITS];
    mask_t currMask;
    size_t xCount = 0;
    size_t mappingInx = 0;

    memset(binaryArray, 0, sizeof(char)*MAX_BITS);

    while(fgets(line, LINE_MAX, input) != NULL)
    {
        memset(binaryArray, 0, sizeof(char)*MAX_BITS);
        uint64_t addr, value;
        if(sscanf(line, "mask = %s", mask) == 1)
        {
            currMask = parseMask(mask, MAX_BITS);
        }
        if(sscanf(line, "mem[%lu] = %lu", &addr, &value) == 2)
        {
            //run mask through PDEP 2^xCount # of times
            xCount = countXsInMask(mask, MAX_BITS);
            for(size_t i = 0; i < ((1ULL) << xCount); i++)
            {
                addr |= currMask.setbits; //set the one bits to one and leave the rest
                addr &= ~currMask.xbits; //clear the x bits to 0 and leave the rest.
                addr |= jPDEP64(i, currMask.xbits); //insert the deposited address offset into the xbit locations 
                mapping[mappingInx] = addr;
                mappingInx++;
            }
        } 
    } 

    // remove dupes from mapping
    size_t newSize = removeDupes(mapping, mappingSize, sizeof(uint64_t), cmpAddress_t);
    uint64_t * memory = malloc(sizeof(uint64_t)*newSize);
    
    // rewind file so we can start from beginning again
    fseek(input, 0, SEEK_SET);

    while(fgets(line, LINE_MAX, input) != NULL)
    {
        memset(binaryArray, 0, sizeof(char)*MAX_BITS);
        uint64_t addr, value;
        if(sscanf(line, "mask = %s", mask) == 1)
        {
            currMask = parseMask(mask, MAX_BITS);
        }
        if(sscanf(line, "mem[%lu] = %lu", &addr, &value) == 2)
        {
            //run mask through PDEP 2^xCount # of times
            xCount = countXsInMask(mask, MAX_BITS);
            for(size_t i = 0; i < ((1ULL) << xCount); i++)
            {
                addr |= currMask.setbits; //set the one bits to one and leave the rest
                addr &= ~currMask.xbits; //clear the x bits to 0 and leave the rest.
                addr |= jPDEP64(i, currMask.xbits); //insert the deposited address offset into the xbit locations 
                uint64_t memoryInx = ((uint64_t*) bsearch(&addr, mapping, newSize, sizeof(uint64_t), cmp64_t))-mapping;
                //printf("Address: %lu\n", memoryInx);
                memory[memoryInx] = value;
            }
        } 
    } 

    uint64_t total = 0;
    for(size_t i = 0; i < newSize; i++)
    {
        total += memory[i];
    }

    printf("%lu\n", total);

    free(mapping);
}

