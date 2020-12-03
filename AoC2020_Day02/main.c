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
    FILE * input = fopen("./input.txt", "r");
    char currCh = fgetc(input);
    check_password_t checkLine;
    check_password_t * checkLinePtr = &checkLine;
    int passwordCharCount = 0;
    int validPasswordCount = 0;

    checkLine.password = malloc(4*sizeof(char));
    strcpy(checkLine.password, "abc");

    resetPasswordCheck(checkLinePtr);

    ungetc(currCh, input);

    while(currCh != EOF)
    {
        if(currCh == '\n')
        {
            char * passwordChPtr = checkLine.password;
            int checkCharCount = 0; 
            while(*(passwordChPtr) != '\0')
            {
                if(*(passwordChPtr) == checkLine.checkChar)
                {
                    checkCharCount++;
                }
                passwordChPtr++;
            }
            if(checkCharCount >= checkLine.min && checkCharCount <= checkLine.max)
            {
                validPasswordCount++;
            }
            passwordCharCount = 0;
            resetPasswordCheck(checkLinePtr);
        }

        if(currCh == ':')
        {
            checkLine.password = realloc(checkLine.password, passwordCharCount*sizeof(char)+1); 
        }
            
        fscanf(input, "%d-%d %c: %s", &checkLine.min, &checkLine.max, &checkLine.checkChar, checkLine.password);
        passwordCharCount++;
        currCh = fgetc(input);
    }
    printf("%d\n", validPasswordCount);

    free(checkLine.password);
    return 0;
}
