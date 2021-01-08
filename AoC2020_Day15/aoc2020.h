#ifndef AOC2020_H
#define AOC2020_H

#define INPUT_NULL_CHECK                     \
if(input == NULL)                            \
{                                            \
    printf("Error: Could not read file.\n"); \
}                                            \

size_t removeDupes(void * array, size_t arraySize, size_t elemSize, int(*cmpfunc)(const void * a, const void * b));
size_t countCharacterInFile(FILE * input, char ch);
void printArray(void *array, size_t arraySize, size_t elemSize, void (*printfunc)(const void * a));
void rewindFile(FILE * input);
char peek(FILE * fp);
int max(int a, int b);

#endif
