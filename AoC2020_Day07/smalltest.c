#include <stdio.h>

#define MAX_LINES 9

int main()
{
    FILE * input = fopen("./testinput.txt", "r");

    for(int i = 0; i < MAX_LINES; i++)
    {
        char test1[50];
        char test2[50];
        char test3[50];
        char test4[50];

        if(fscanf(input, " %s %s bags contain ", test1, test2) == 2)
        {
            printf("test1: %s test2: %s\n", test1, test2);
        }
 
        while(fscanf(input, " %*[no0123456789] %s %s bag%*[,|s,|.]", test3, test4) == 2)
        {
            printf("test3: %s test4: %s\n", test3, test4);
        }
        printf("\n");
        
    }
    return 0;
}
