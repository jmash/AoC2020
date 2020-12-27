#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "aoc2020.h"
/*
mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
mem[8] = 11
mem[7] = 101
mem[8] = 0
*/
/*
mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
mem[8] = 11
mem[7] = 101
mem[8] = 0
mask = XXXXXXXXXXXXXXXXXXXXXXXXX1XXX1X0XX0X
mem[6] = 2
mem[8] = 19
mem[5] = 4
mem[7] = 10
*/
typedef struct
{
    int64_t value;
    size_t address;
    size_t addressLoc;
} line_info_t;

int compAddresses(const void * a, const void * b)
{
    line_info_t *lineA = (line_info_t *) a;
    line_info_t *lineB = (line_info_t *) b;

    if(lineA->address > lineB->address) return 1;
    else if(lineA->address < lineB->address) return -1;
    else return 0;
}

int main(int argc, char * argv[])
{
    FILE * input = fopen("./testinput", "r");
    size_t charCount = countCharacterInFile(input, 'm');

    line_info_t lines[7];
    lines[0].value = 11;
    lines[0].address = 8;
    lines[0].addressLoc = 0;
     
    lines[1].value = 101;
    lines[1].address = 7;
    lines[1].addressLoc = 1;

    lines[2].value = 0;
    lines[2].address = 8;
    lines[2].addressLoc = 2;

    lines[3].value = 2;
    lines[3].address = 6;
    lines[3].addressLoc = 3;

    lines[4].value = 19;
    lines[4].address = 8;
    lines[4].addressLoc = 4;

    lines[5].value = 4;
    lines[5].address = 5;
    lines[5].addressLoc = 5;

    lines[6].value = 10;
    lines[6].address = 7;
    lines[6].addressLoc = 6;

    qsort(lines, 7, sizeof(line_info_t), compAddresses);

    for(size_t i = 0; i < 7; i++)
    {
        printf("[%ld ", lines[i].value);
        printf("%lu ", lines[i].address);
        printf("%lu]", lines[i].addressLoc);
        printf("\n");
    }
    removeDupes(lines, 7, sizeof(line_info_t), compAddresses);

    //size_t newLinesSize = removeDupes(lines, 7, sizeof(line_info_t), compAddresses);

    for(size_t i = 0; i < 7; i++)
    {
        printf("[%ld ", lines[i].value);
        printf("%lu ", lines[i].address);
        printf("%lu]", lines[i].addressLoc);
        printf("\n");
    }
}
