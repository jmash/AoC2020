#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

size_t removeDupes(void * array, size_t arraySize, size_t elemSize, int(*cmpfunc)(const void * a, const void * b));

int cmpints(const void * a, const void * b)
{
    return *(int *)a - *(int *)b; 
}

size_t max(size_t a, size_t b)
{
    return a*(a >= b) + b*(a < b);
}

size_t countCharacterInFile(FILE * input, char ch)
{
    int currCh; // CURRCH! :D :D :D
    size_t chCount = 0;
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == ch)
        {
            chCount++;
        }
    }

    fseek(input, 0, SEEK_SET);
    return chCount;
}

size_t removeDupes(void * array, size_t arraySize, size_t elemSize, int(*cmpfunc)(const void * a, const void * b))
{ 
    uint8_t * barr = (uint8_t *) array;
    qsort(barr, arraySize, elemSize, cmpfunc);
    size_t uniqueCount = 0;
    uint8_t * prev = barr;
    for(size_t i = 1; i < arraySize; i++)
    {
       // check if prev element is a dupe
       uint8_t * curr = prev+elemSize;
       if(cmpfunc(prev, curr) != 0)
       {
           uniqueCount++;
           uint8_t * output = barr+uniqueCount*elemSize;
           memcpy(output, curr, elemSize);
       }
       prev += elemSize;
    }
    return ++uniqueCount;
}


void printArray(void *array, size_t arraySize, size_t elemSize, void (*printfunc)(const void * a))
{
    uint8_t * barr = (uint8_t *) array;
    for(size_t i = 0; i < arraySize; i++)
    {
        printfunc(barr);
        barr += elemSize;
    }
}

char peek(FILE * fp)
{
    char ch;
    ch = fgetc(fp);
    ungetc(ch, fp);
    return ch;
}

void rewindFile(FILE * input)
{
    fseek(input, 0, SEEK_SET);
}

int is_file_valid(FILE * input)
{
    if(input == NULL)
    {
        printf("Error opening file; aborting.\n");
        return 0;
    }
    return 1;
}
