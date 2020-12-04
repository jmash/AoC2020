#include <stdio.h>

int scanSlope(int dx, int dy)
{
    FILE * input = fopen("./input.txt", "r");
    char currCh;
    int charPos = 0;
    int tobPos = 0;
    int rowPos = 0;
    int colPos = 0;
    int numCols = 0;
    int numTrees = 0;

    while((currCh = fgetc(input)) != '\n')
    {
        numCols++;
    }
    fseek(input, 0, SEEK_SET);
         
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '\n') 
        {
            if(colPos % dy == 0) 
                tobPos = (tobPos + dx) % numCols;
            colPos++;
            continue;
        }

        rowPos = charPos % numCols;

        if(rowPos == tobPos) 
        {
            if((currCh == '#') && (colPos % dy == 0)) numTrees++;
        }
        charPos++;
    }
    printf("Trees: %d\n", numTrees);

    fclose(input);
    return numTrees;
}

int main(int argc, const char *argv[])
{
    int trees[5];
    long int answer = 1;

    trees[0] = scanSlope(1, 1); 
    trees[1] = scanSlope(3, 1);
    trees[2] = scanSlope(5, 1);
    trees[3] = scanSlope(7, 1);
    trees[4] = scanSlope(1, 2);

    for(int i = 0; i < 5; i++)
    {
        answer *= trees[i];
    }

    printf("Answer is : %ld\n", answer);
    printf("%d\n", sizeof(unsigned long int));
    
    return 0;
}
