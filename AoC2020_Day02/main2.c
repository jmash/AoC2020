#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    int firstPos;
    int secondPos;
    char checkChar;
    char * password;
} check_password_t;

void resetPasswordCheck(check_password_t * checkLine)
{
    checkLine->firstPos = 0;
    checkLine->secondPos = 0;
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
            bool isValid = false;
            int passwordChPos = 1; 

            isValid = ((*(passwordChPtr + checkLine.firstPos - 1) == checkLine.checkChar) ^ 
                    (*(passwordChPtr + checkLine.secondPos - 1) == checkLine.checkChar));
            
            if(isValid) validPasswordCount++;
            resetPasswordCheck(checkLinePtr);
        }


        if(currCh == ':')
        {
            checkLine.password = realloc(checkLine.password, passwordCharCount*sizeof(char)+1); 
        }
            
        fscanf(input, "%d-%d %c: %s", &checkLine.firstPos, &checkLine.secondPos, &checkLine.checkChar, checkLine.password);
        passwordCharCount++;
        currCh = fgetc(input);
    }
    printf("%d\n", validPasswordCount);

    free(checkLine.password);
    fclose(input);
    return 0;
}
