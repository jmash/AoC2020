#ifndef AOC2020_H
#define AOC2020_H

size_t removeDupes(void * array, size_t arraySize, size_t elemSize, int(*cmpfunc)(const void * a, const void * b));
size_t countCharacterInFile(FILE * input, char ch);
void printArray(void *array, size_t arraySize, size_t elemSize, void (*printfunc)(const void * a));
void rewindFile(FILE * input);
char peek(FILE * fp);
int max(int a, int b);
int check_file(FILE * input);

#endif
