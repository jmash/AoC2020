#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "./aoc2020.h"
/*
mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
mem[8] = 11
mem[7] = 101
mem[8] = 0
*/
typedef struct
{
    int64_t value;
    size_t address;
    size_t addressLoc;
} line_info_t;

int compAddresses(const void * a, const void * b)
{
    return (*(size_t *)a - *(size_t *)b);
}

int main(int argc, char * argv[])
{
    line_info_t lines[3];
    lines[0].value = 11;
    lines[0].address = 8;
    lines[0].addressLoc = 0;
     
    lines[1].value = 101;
    lines[1].address = 7;
    lines[1].addressLoc = 1;

    lines[2].value = 0;
    lines[2].address = 8;
    lines[2].addressLoc = 2;

    qsort(lines, 3, sizeof(line_info_t), compAddresses);

}
