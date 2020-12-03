#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int min;
    int max;
    char checkChar;
    char * password;
} check_password_t;

void resetPasswordCheck(check_password_t * checkLine)
{
    checkLine->min = 0;
    checkLine->max = 0;
    checkLine->checkChar = 'a';
}

int main()
{
    FILE * input = fopen("./testinput.txt", "r");
    char currCh = fgetc(input);
    check_password_t checkLine;
    check_password_t * checkLinePtr = &checkLine;
    int passwordCharCount = 0;

    checkLine.password = malloc(4*sizeof(char));
    strcpy(checkLine.password, "abc");
    printf("%s\n", checkLine.password);

    resetPasswordCheck(checkLinePtr);

    ungetc(currCh, input);

    while(currCh != EOF)
    {
        if(currCh == '\n')
        {
            passwordCharCount = 0;
            resetPasswordCheck(checkLinePtr);
        }


        fscanf(input, "%d-%d %c: ", &checkLine.min, &checkLine.max, &checkLine.checkChar);
        currCh = fgetc(input);
    }

    return 0;
}
