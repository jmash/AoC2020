#include <stdio.h>
#include <stdlib.h>

/*
    Pseudo code thunkin':
    FBFBBFFRLR 
    min = 0 max = 127
F:  min = 0 max = 63
B:  min = 32 max = 63
F:  min = 32 max = 47
B:  min = 40 max = 47
B:  min = 44 max = 47
F:  min = 44 max = 45
F:  (min) or max -> row
    min = 0 max = 7
R:  min = 4 max = 7
L:  min = 4 max = 5
R:  min or (max) -> col
    
    1 F: max = (((max-min) + 1)/2)-1) + min -> max = (((127 - 0) + 1)/2-1) => 63 + 0
    2 B: min = ((max-min) + 1)/2) + min   -> min = (((63 - 0) + 1)/2) => 32 + 0
    3 F: max = (((max-min) + 1)/2)-1) + min -> max = (((63 - 32) + 1)/2 - 1) => 15 + 32 => 47
    4 B: min = (((max-min) + 1)/2)) + min   -> min = (((47 - 32) + 1)/2) => 8 + 32 => 40
    5 B: min = (((max-min) + 1)/2)) + min   -> min = (((47 - 40) + 1)/2) => 4 + 40 => 44
    6 F: max = (((max-min) + 1)/2)-1) + min -> max = (((47 - 44) + 1)/2 - 1) => 1 + 44 => 45
    7 F: (min) or max => 44 -> row
    8 R: min = (((max-min) + 1)/2)) + min   -> min = (((7 - 0) + 1)/2) => 4 + 0 => 4
    9 L: max = (((max-min) + 1)/2)-1) + min -> max = (((7 - 4) + 1)/2) => 1 + 4 => 5
    10 R: min or (max) => 5 -> col

    seat id: row*8+col
 
*/

int getMax(int a, int b)
{
    return a*(a >= b) + b*(a < b);
}

int cmpfunc (const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
}


int main(int argc, const char *argv[])
{
    FILE * input = fopen("./input.txt", "r");
    char currCh;
    int seatId = 0;
    int maxSeatId = 0;
    int seatIdsNum = 0;
    int seatInx = 0;

    while((currCh = fgetc(input)) != EOF)
        if(currCh == '\n') seatIdsNum++;

    int seatIds[seatIdsNum];

    fseek(input, 0, SEEK_SET);

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '\n') {
            seatIds[seatInx] = seatId;
            seatInx++; 
            continue;
        }
        int currCol = 0;
        int currRow = 0;
        int min = 0;
        int max = 127;
       
        //012345 01
        //FBFBBFFRLR 
        for(int i = 0; i <= 5; i++)
        {
            if(currCh == 'F') 
                max = ((((max-min) + 1)/2)-1) + min;   
            if(currCh == 'B')
                min = (((max-min) + 1)/2) + min;   
            currCh = fgetc(input);
        }
        if(currCh == 'F') currRow = min;
        if(currCh == 'B') currRow = max;
        currCh = fgetc(input);
        min = 0;
        max = 7;
        for(int i = 0; i <= 1; i++)
        {    
            if(currCh == 'L') 
                max = (((max-min) + 1)/2)-1 + min;   
            if(currCh == 'R')
                min = (((max-min) + 1)/2) + min;   
            currCh = fgetc(input);
        }
        if(currCh == 'L') currCol = min;
        if(currCh == 'R') currCol = max;
        seatId = currRow*8 + currCol;

        maxSeatId = getMax(seatId, maxSeatId);
    }

    qsort(seatIds, seatIdsNum, sizeof(int), cmpfunc);

    for(int i = 0; i < seatIdsNum; i++)
    {
        if(seatIds[i]+1 != seatIds[i+1])
        {
            printf("My seat id is: %d\n", seatIds[i]+1);
            break;
        }
    }
    
    return 0;
}
