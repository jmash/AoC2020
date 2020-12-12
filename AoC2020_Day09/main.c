#include <stdio.h>
#include <stdlib.h>

/*
   [35   35   35
    20  [20   20
    15   15  [15
    25   25   25
    47]  47   47
    (40) 40]  40
    62   (62) 62]
    55   ...  (55)
    65        ...
    95
    102
    117
    150
    182
    127
    219
    299
    277
    309
    576 
*/

int readLines(FILE * input)
{
    int numLines = 0;
    char currCh; // hi Currch :)
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '\n') numLines++;
    }
    return numLines;
}

int main(int argc, const char *argv[])
{
    FILE * input = fopen("./testinput.txt", "r");
    int fileLines = readLines(input); 

    printf("%d\n", fileLines);
    return 0;
}
