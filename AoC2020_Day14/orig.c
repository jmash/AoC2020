#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include "./aoc2020.h"

#define BIT_MAX 36

typedef uint64_t address_t;
typedef uint64_t value_t;
typedef struct
{
    int64_t value;
    size_t address;
    size_t addressLoc;
} line_info_t;

int cmpAddress_t (const void * a, const void * b) {
   address_t av = *(const address_t*)a;
   address_t bv = *(const address_t*)b;
   if(av == bv) return 0;
   else if(av < bv) return -1;
   else return 1;
}

void printAddressArray(address_t * array, size_t arraySize)
{
    for(size_t i = 0; i < arraySize; i++)
    {
        printf("[%ld]", array[i]);
    }
    printf("\n");
}

void populateAddresses(FILE * input, address_t * addresses)
{
    int currCh; // currCh now an int? it feels so wrong :(
    int inx = 0;
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '[')
        {
            fscanf(input, "%lu]", &addresses[inx]);
            inx++;
        }
    }
    rewindFile(input);
}

void printAddress(const void * address)
{
    printf("[%ld]", *(address_t *)address);
}

void printInt(const void * d)
{
    printf("%d", *(char *)d);
}

void printChar(const void * ch)
{
    printf("%c", *(char *)ch);
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
        printf("%ld\n", i);
        value -= base;
    }
}

// convert binary representation to decimal value
int64_t binaryToValue(char * binaryArray, size_t arrayLength)
{
    int64_t total = 0;
    for(size_t i = 0; i < arrayLength; i++)
    {
        if(binaryArray[arrayLength - i - 1])
        {
            total += pow64T(2, i);
        }
    }
    
    return total;
}

void applyBitmask(char * bitMask, char * binaryArray, size_t arrayLength)
{
    for(size_t i = 0; i < arrayLength; i++)
    {
        size_t revPos = arrayLength - i - 1;
        if(bitMask[revPos] == 48) binaryArray[revPos] = 0;
        if(bitMask[revPos] == 49) binaryArray[revPos] = 1;
    }
}

// returns the address' associated index in the locations array. if no address
// can be found, returns -1
int32_t locateAddress(size_t address, size_t * addressLocs, size_t addressesLength)
{
    for(size_t i = 0; i < addressesLength; i++)
    {
        if(addressLocs[i] == address) return i; 
    }

    return -1;
}

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Error: No input file specified.\n");
        return 1;
    }
    FILE * input = fopen(argv[1], "r");
    INPUT_NULL_CHECK; // make sure the input file actually works

    char currCh; // join the CURRCH
    char compWord[50]; // word to compare against the scanned-in word
    char currBitmask[BIT_MAX+1]; // bitmask is always 36 characters (+1 for null terminator)
    char bitValue[BIT_MAX];
    memset(currBitmask, 'X', BIT_MAX*sizeof(char)); // default mask for first pass
    memset(bitValue, 0, BIT_MAX*sizeof(char)); // default mask for first pass
    size_t numAddresses = countCharacterInFile(input, '[');
    printf("%lu\n", numAddresses);
    line_info_t lines[numAddresses];

//    valueToBinary(51, bitValue, BIT_MAX);
//    strcpy(currBitmask, "X1XXXXXXXX1XXXXXX1XXXXXXXXXXXXXX0000");
 //   applyBitmask(currBitmask, bitValue, BIT_MAX); 

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == 'm')
        {
            if(peek(input) == 'e')
            {
                fseek(input, 3, SEEK_CUR);
                //fscanf(input, "%lu", &addresses[numAddresses]);
                //printf("%lu\n", addresses[numAddresses]);
                fseek(input, 4, SEEK_CUR);
                
            }
        }
    }
    

    fclose(input); // STOP FORGETTING
    return 0;
}


//   [7][8]
//   [0][1]

// IN MEMORIAM REQUIESCAT IN PACE
//
/*size_t removeDuplicatesFromArray(int * array, size_t arraySize)
{ 
    qsort(array, arraySize, sizeof(int), cmpints);
    int * noDuplicates;
    noDuplicates = array;
    noDuplicates[0] = array[0];
    unsigned int uniqueCount = 0;
    for(int i = 1; i < arraySize; i++)
    {
       // check if prev element is a dupe
       if(array[i-1] != array[i])
       {
           uniqueCount++;
           noDuplicates[uniqueCount] = array[i];
       }
    }
    return ++uniqueCount;
}*/
