#ifndef AOC2020_H
#define AOC2020_H

size_t remove_dupes(void * array, size_t arraySize, size_t elemSize, int(*cmpfunc)(const void * a, const void * b));
size_t count_character_in_file(FILE * input, char ch);
void print_array(void *array, size_t arraySize, size_t elemSize, void (*printfunc)(const void * a));
int get_largest_int_from_array(void *array, size_t array_size);
void rewindFile(FILE * input);
char peek(FILE * fp);
int max(int a, int b);
int is_file_valid(FILE * input);

#endif
