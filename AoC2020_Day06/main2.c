#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_ALPHA 26

/*
    Part One Pseudocode
    index of array will always be character ascii value - 97
    group_sum = 0
    total_sum = 0

    abc -> [0][1][2] -> 1 => 3 values | group_sum = 3
    \n --> \n o
    total_sum = group_sum + total_sum | total_sum = 3 + 0
    group_sum = 0
    reset bool array
    a -> [0] -> 1 => 1 value | group_sum = 1
    \n --> \n x
    b -> [1] => 1 => 1 value | group_sum = 2
    \n --> \n x
    c -> [2] => 1 => 1 value | group_sum = 3
    \n --> \n o
    total_sum = group_sum + total_sum | total_sum = 3 + 3
    group_sum = 0
    reset bool array
    ab -> [0][1] -> 1 => 2 values | group_sum = 2
    \n --> \n x
    ac -> [(0)][2] -> 1 => 1 values | group_sum = 3
    \n --> \n o
    total_sum = group_sum + total_sum | total_sum = 6 + 3
    group_sum = 0
    reset bool array
    a -> [0] -> 1 => 1 value | group_sum = 1
    \n --> \n x
    a -> [(0)] -> 1 => 0 values | group_sum = 1
    \n --> \n x
    a -> [(0)] -> 1 => 0 values | group_sum = 1
    \n --> \n x
    a -> [(0)] -> 1 => 0 values | group_sum = 1 
    \n --> \n o
    total_sum = group_sum + total_sum | total_sum = 9 + 1
    group_sum = 0
    reset bool array
    b -> [1] -> 1 => 1 value | group_sum = 1
    EOF
    total_sum = group_sum + total_sum | total_sum = 10 + 1
    group_sum = 0
    reset bool array
*/

/*
    start
    1 1 1
    0 0 0
    a
    1 1 1
    1 0 0
    b
    1 1 1
    1 1 0
    c
    1 1 1
    1 1 1
    -->
        1 1 1 comparator
        1 1 1 AND
        -----
        1 1 1 -> 3
    a
    1 1 1
    1 0 0
    -->
        1 1 1 comparator
        1 0 0 AND
        _____
        1 0 0
    b
    1 0 0
    0 1 0
    -->
        1 0 0 comparator
        0 1 0 AND
        _____
        0 0 0 -> new comparator
    c
    0 0 0
    0 0 1
    -->
        0 0 0 comparator
        0 0 1 AND
        -----
        0 0 0 
    a
    1 1 1
    1 0 0
    b
    1 1 1
    1 1 0
    -->
        1 1 1 comparator
        1 1 0 AND
        _____
        1 1 0 new comparator
    a
    1 1 0
    1 0 0
    c
    1 1 0
    1 0 1
    -->
        1 1 0 comparator
        1 0 1 AND
        -----
        1 0 0 
    
*/

void printArray(bool arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

char peek(FILE * fp)
{
    char ch;
    ch = fgetc(fp);
    ungetc(ch, fp);
    return ch;
}

// anticipated testinput output 11
int main(int argc, const char *argv[])
{
    FILE * input = fopen("./input.txt", "r");
    char currCh; // friend! <3
    bool groupAnswers[MAX_ALPHA];
    bool comparatorArray[MAX_ALPHA];
    int totalSum = 0;
    int groupSum = 0;
    memset(groupAnswers, 0, MAX_ALPHA*sizeof(bool));
    memset(comparatorArray, 1, MAX_ALPHA*sizeof(bool));

    while((currCh = fgetc(input)) != EOF)
    {
        /*
        if(currCh == '\n') printf("N\n"); else printf("%c\n", currCh);
        printf("-------------------\n");
        printArray(comparatorArray, 3);
        printf("\n");
        printArray(groupAnswers, 3);
        printf("\n------------------\n");
        */
        if(currCh == '\n')
        {
            for(int i = 0; i < MAX_ALPHA; i++)
            {
                comparatorArray[i] = comparatorArray[i] && groupAnswers[i]; 
            }
            if((peek(input) == '\n') || (peek(input) == EOF)) // sum and reset
            {
                for(int i = 0; i < MAX_ALPHA; i++)
                {
                    if(comparatorArray[i] == true) 
                    {
                        //printf("firing\n");
                        groupSum++;
                    }
                }
                totalSum += groupSum;
                groupSum = 0;
                memset(groupAnswers, 0, MAX_ALPHA*sizeof(bool));
                memset(comparatorArray, 1, MAX_ALPHA*sizeof(bool));
                fgetc(input);
            }
            memset(groupAnswers, 0, MAX_ALPHA*sizeof(bool));
        }
        if(groupAnswers[currCh - 97] == false)
        {
            groupAnswers[currCh - 97] = true;
        }
      
    }

    printf("total sum is %d\n", totalSum);


    return 0;
}
