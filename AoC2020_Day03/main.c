#include <stdio.h>

// Output should be: .#.##.####

int main(int argc, const char *argv[])
{
    FILE * input = fopen("./testinput.txt", "r");
    char currCh = fgetc(input);
    int charIter = 0;
    int colPos = 0;
    int numCols = 0;
    int treeCount = 0;
    int i = 0;

    while((currCh = fgetc(input)) != '\n')
    {
        numCols++;
    }
    numCols++;
    printf("columns %d\n", numCols);
    fseek(input, 0, SEEK_SET);

    fgetc(input);

    printf("O");
    while((currCh = fgetc(input)) != EOF)
    {
        ++charIter;
        if(colPos > numCols)
        {
            charIter = 0;
            colPos = 0;
        }
        if(currCh == '\n') 
        {
            colPos += 3;
            --charIter;
        }
        if(charIter % (numCols+3) == 0) 
        {
            if(currCh == '.') printf("O");
            if(currCh == '#') 
            {
                treeCount++;
                printf("X");
            }
            if(currCh == '\n') printf("\n");
        } else
        printf("%c", currCh);
    }
    printf("Tree count: %d\n", treeCount);
    return 0;
}
