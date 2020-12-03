#include <stdio.h>
#include <stdlib.h>

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
    checkLine->password = "abc";
}

int main()
{
    FILE * input = fopen("./testinput.txt", "r");
    char currCh = fgetc(input);
    check_password_t checkLine;
    check_password_t * checkLinePtr = &checkLine;
    int passwordCharCount = 0;

    resetPasswordCheck(checkLinePtr);

    ungetc(currCh, input);

    while(currCh != EOF)
    {
        if(currCh == '\n')
        {
            passwordCharCount = 0;
            resetPasswordCheck(checkLinePtr);
        }


        printf("%c", currCh);
        currCh = fgetc(input);
    }

    return 0;
}
