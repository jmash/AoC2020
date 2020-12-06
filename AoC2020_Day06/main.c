#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ALPHA 26

/*
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

void printArray(bool arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

// anticipated testinput output 11
int main(int argc, const char *argv[])
{
    FILE * input = fopen("./testinput.txt", "r");
    bool groupAnswers[MAX_ALPHA];
    memset(groupAnswers, 0, MAX_ALPHA*sizeof(bool));

    printArray(groupAnswers, MAX_ALPHA);



    return 0;
}
