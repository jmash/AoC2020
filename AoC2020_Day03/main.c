#include <stdio.h>

int main(int argc, const char *argv[])
{
    FILE * input = fopen("./testinput.txt", "r");
    char currCh;

    while((currCh = fgetc(input)) != EOF)
    {
        printf("%c");
    }
    return 0;
}
