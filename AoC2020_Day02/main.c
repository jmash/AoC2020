#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int min;
    int max;
    char checkChar;
    char * password;
} password_check_t;

void resetPasswordCheck(password_check_t * checkLine)
{
    checkLine->min = 0;
    checkLine->max = 0;
    checkLine->checkChar = 'a';
    checkLine->password = "abc";
}

int main()
{
    FILE input = fopen("./testinput.txt", "r");
    char currCh;
    currCh = fgetc(input);
    check_password_t checkLine;
    check_password_t * checkLinePtr = checkLine;
    int passwordCharCount = 0;


    resetPasswordCheck(checkLinePtr);

    ungetc(currCh, input);

    while(currCh != EOF)
    {
        if(currCh == '\n')
        {
            passwordCharCount = 0;
        }
        printf("%c", currCh);
        currCh = fgetc(input);
    }

    return 0;
}
