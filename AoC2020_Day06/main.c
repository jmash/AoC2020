#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ALPHA 26

void printArray(bool arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}

int main(int argc, const char *argv[])
{
    bool groupAnswers[MAX_ALPHA];
    memset(groupAnswers, 0, MAX_ALPHA*sizeof(bool));

    printArray(groupAnswers, MAX_ALPHA);

    return 0;
}
