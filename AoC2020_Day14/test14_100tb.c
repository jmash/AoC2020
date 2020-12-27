#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//static const ADDRESS_SPACE=0x1000000000ULL;
static const uint64_t ADDRESS_LEN=22;
static const uint64_t ADDRESS_SPACE=(1ULL) << ADDRESS_LEN;
//static const uint64_t ADDRESS_SPACE=0x8000000;
static const uint64_t ADDRESS_MASK=ADDRESS_SPACE-1;

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

mask_t parseMask(char maskString[37])
{
    //2 << Y;
    mask_t parsedMask;
    parsedMask.clearbits = 0;
    parsedMask.setbits = 0;

    for(int i = 0; i < 37; i++)
    {
        if(maskString[i] == '0')
        {
            parsedMask.clearbits += (2 << (36 - i));
        }
        if(maskString[i] == '1')
        {
            parsedMask.setbits += (2 << (36 - i));
        }
    }
    
    return parsedMask;
}

int main(int argc, char * argv[])
{
    FILE * input = fopen("./input.txt", "r");

    if(input == NULL)
    {
        printf("Error: cannot open file.\n");
        return 1;
    }
    uint64_t * memory = malloc(sizeof(uint64_t)*ADDRESS_SPACE);
    memset(memory, 0, sizeof(uint64_t)*ADDRESS_SPACE);
    
    char line[100];
    char mask[37];
    size_t inx = 0;

    while(fgets(line, 100, input) != NULL)
    {
        uint64_t addr, value;
        if(sscanf(line, "mem[%lu] = %lu", &addr, &value) == 2)
        {
            printf("%lu %lu\n", addr, value);
            memory[addr] = value;
        } else if(sscanf(line, "mask = %s", mask) == 1)
        {
            mask_t currMask = parseMask(mask);
            printf("%lu\n%lu\n", currMask.setbits, currMask.clearbits);
            printf("Updating mask\n");
        }
    }

    free(memory);
}

/*
setbits:   0b00001
clearbits: 0b11000 
value:     0b00101
-----------------
result:    0b10100
*/
