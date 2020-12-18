#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define clear() printf("\033[H\033[J")
#define clear2() printf("\x1b[H\x1b[J")

typedef struct {
    int rows;
    int cols;
    char **seats;
} layout_t;

void delay(int numberOfSeconds) 
{ 
    // Converting time into milli_seconds 
    int milliSeconds = 1000 * numberOfSeconds; 
  
    // Storing start time 
    clock_t startTime = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < startTime + milliSeconds); 
} 

void rewindFile(FILE * input)
{
    fseek(input, 0, SEEK_SET);
}

int getCols(FILE * input)
{
    char currCh; //welcome back buddy ^_^
    int numCols = 0;

    while((currCh = fgetc(input)) != '\n')
    {
        numCols++;
    }

    rewindFile(input);
    return numCols;
}

int getRows(FILE * input)
{
    char currCh;
    int numRows = 0;

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '\n') numRows++;
    }

    rewindFile(input);
    return numRows;
}

void readInSeats(layout_t * layoutPtr, FILE * input)
{
    for(int i = 1; i < (layoutPtr->rows)-1; i++)
    {
        fscanf(input, " %s ", layoutPtr->seats[i]+1);
        layoutPtr->seats[i][layoutPtr->cols-1]='&';
    }

    rewindFile(input);
}

layout_t * initLayout(int numRows, int numCols)
{
    layout_t * layoutPtr = (layout_t *)malloc(sizeof(layout_t));
    layoutPtr->rows=numRows;
    layoutPtr->cols=numCols;

    layoutPtr->seats = (char **)malloc(sizeof(char *)*numRows);
    layoutPtr->seats[0] = (char *)malloc(sizeof(char)*numCols*numRows);
    for(int i = 1; i < numRows; i++)
    {
        layoutPtr->seats[i] = layoutPtr->seats[0]+i*numCols;
    }
    
    memset(layoutPtr->seats[0], '&', numRows*numCols);

    return layoutPtr; 
}


void deinitLayout(layout_t * layoutPtr)
{ 
    free(layoutPtr->seats[0]);
    free(layoutPtr->seats);
    free(layoutPtr);
}

void printSeatLayout(const layout_t * seatLayout)
{
    for(int i = 0; i < seatLayout->rows; i++)
    {
        for(int j = 0; j < seatLayout->cols; j++)
        {
            printf("%c", seatLayout->seats[i][j]);
        }
        printf("\n");
    }
}


//bool iterateLayout(const layout_t * prev, layout_t * curr) put back when testing is over
bool iterateLayout(const layout_t * prev, layout_t * curr, FILE * input)
{
    static const int coordsToCheck[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int occupiedSeats = 0;
    bool changeOccurred = false;
    for(int i = 1; i < (prev->rows)-1; i++)
    {
        for(int j = 1; j < (prev->cols)-1; j++)
        {
            readInSeats(curr, input);
            curr->seats[i][j] = 'X';
            occupiedSeats = 0;
            if(prev->seats[i][j] == 'L' || prev->seats[i][j] == '#')
            {
                for(int k = 0; k < 8; k++)
                {
                    int r = i+coordsToCheck[k][0]; // 1 + -1 -> 0
                    int c = j+coordsToCheck[k][1]; // 1 + -1 -> 0
                   // printf("r:%d c:%d\n", r, c);
                    delay(500);
                    while(prev->seats[r][c] == '.')
                    {
                        curr->seats[r][c] = 'o';
                        r += coordsToCheck[k][0]; // 
                        c += coordsToCheck[k][1]; // 1 + -1
                        if(prev->seats[r][c] == '#') 
                        {
                            occupiedSeats++;
                        }                    
                    }
                    printSeatLayout(curr);
                    clear2();
                }
            }
            if((prev->seats[i][j] == 'L') && (occupiedSeats == 0)) 
            {
                changeOccurred = true;
                curr->seats[i][j] = '#';
            }
            else if((prev->seats[i][j] == '#') && (occupiedSeats >= 5)) 
            {
                changeOccurred = true;
                curr->seats[i][j] = 'L';
            }
            else curr->seats[i][j] = prev->seats[i][j];
        }
    }
    return changeOccurred;
}

void swapLayouts(layout_t ** a, layout_t ** b)
{
    layout_t * temp = *(b);
    *(b) = *(a);
    *(a) = temp;
}

int countOccupiedInLayout(layout_t * layout)
{ 
    // a e s t h e t i c
    int occupiedCount = 0;
    for(int i = 0; i < layout->rows; i++)
    {
        for(int j = 0; j < layout->cols; j++)
        {
            if(layout->seats[i][j] == '#')
            {
                occupiedCount++;
            }
        }
    }

    return occupiedCount;
}

int main(int argc, const char *argv[])
{
    if(argc < 2) 
    {
        printf("No file specified; aborting.\n");
        return 1;
    }
    FILE * input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Error opening file; aborting.\n");
        return 1;
    }
   
    int numCols = getCols(input);
    int numRows = getRows(input);
    // adding two to cols and rows in order to make room
    // for floor border (make algorithm easier to implement)
    numCols += 2;
    numRows += 2;

    layout_t * prevLayout = initLayout(numRows, numCols);
    layout_t * currLayout = initLayout(numRows, numCols);
    
    readInSeats(prevLayout, input);
    readInSeats(currLayout, input); // TEMPORARY: REMOVE BEFORE FINALIZING SOLUTION

    // input parameter is very temporary
    iterateLayout(prevLayout, currLayout, input);
    /*
    while(iterateLayout(prevLayout, currLayout, input))
    {
        swapLayouts(&currLayout, &prevLayout);
    }
    */

    int occupiedSeats = countOccupiedInLayout(currLayout);

    //printf("%d\n", occupiedSeats);

    deinitLayout(prevLayout);
    deinitLayout(currLayout);

    //printf("%dx%d\n", numRows, numCols);

    return 0;
}

