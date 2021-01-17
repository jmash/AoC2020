#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "aoc2020.h"

void print_int(const void * a)
{
    int a_i = *(int *)a;
    printf("[%d]", a_i);
}

int cmp_ints(const void * a, const void * b)
{
    int a_i = *(int *)a;
    int b_i = *(int *)b;
    if(a_i < b_i) return -1;
    else if(a_i == b_i) return 0;
    else return 1; 
}

size_t get_largest_value(FILE * input)
{
    char currCh;
    char check_your[12];
    size_t cur_inx = 0; 
    int low_range_1 = 0;
    int high_range_1 = 0;
    int low_range_2 = 0;
    int high_range_2 = 0;
    
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == 'y')
        {
            ungetc(currCh, input);
            fscanf(input, "%s:", check_your);
            if(strcmp(check_your, "your ticket"))
            {
                break;
            }
        }

        if(isdigit(currCh))
        {
            ungetc(currCh, input);
            fscanf(input, "%d-%d or %d-%d", &low_range_1, &high_range_1, &low_range_2, &high_range_2);
            for(int i = low_range_1; i <= high_range_1; i++)
            {
                cur_inx++;
            }
            for(int i = low_range_2; i <= high_range_2; i++)
            {
                cur_inx++;
            }
        } 
    }

    fseek(input, 0, SEEK_SET);
    
    return cur_inx;
}

void load_in_valid_values(FILE * input, int * valid_values)
{
    char currCh;
    char check_your[12];
    size_t cur_inx = 0;
    int low_range_1 = 0;
    int high_range_1 = 0;
    int low_range_2 = 0;
    int high_range_2 = 0;
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == 'y')
        {
            ungetc(currCh, input);
            fscanf(input, "%s:", check_your);
            if(strcmp(check_your, "your ticket"))
            {
                break;
            }
        }
        if(isdigit(currCh))
        {
            ungetc(currCh, input);
            fscanf(input, "%d-%d or %d-%d", &low_range_1, &high_range_1, &low_range_2, &high_range_2);
            for(int i = low_range_1; i <= high_range_1; i++)
            {
                valid_values[cur_inx] = i;
                cur_inx++;
            }
            for(int i = low_range_2; i <= high_range_2; i++)
            {
                valid_values[cur_inx] = i;
                cur_inx++;
            }
        } 
    }

    fseek(input, 0, SEEK_SET);
}

int get_error_rate(FILE * input, int * valid_values, size_t valid_size)
{
    char currCh;
    bool nearby_vals_flag = false;    
    char check_nearby[15];
    int cur_nearby_val = 0;
    int error_rate = 0;
    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == 'n')
        {
            ungetc(currCh, input);
            fscanf(input, "%s:", check_nearby);
            if(strcmp(check_nearby, "nearby tickets"))
            {
                nearby_vals_flag = true;
            }
        }
        if(nearby_vals_flag)
        {
            if(isdigit(currCh))
            {
                ungetc(currCh, input);
                fscanf(input, "%d", &cur_nearby_val);
                int * search_result = bsearch(&cur_nearby_val, valid_values, valid_size, sizeof(int), cmp_ints); 
                if(search_result != NULL)
                {
                    printf("%d\n", *(search_result));
                }
                else
                {
                    printf("not found\n");
                    error_rate += cur_nearby_val;
                }
            }
        }
    }

    fseek(input, 0, SEEK_SET);

    return error_rate;
}

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Too few arguments; aborting.\n");
    }

    FILE * input = fopen(argv[1], "r");
    if(!is_file_valid(input))
    {
        return 1;
    }

    int largest_val = get_largest_value(input); 
    int valid_values[largest_val];
    int error_rate = 0;
    memset(valid_values, 0, sizeof(int));

    load_in_valid_values(input, valid_values);
    size_t new_valid_size = remove_dupes(valid_values, largest_val, sizeof(int), cmp_ints);
    error_rate = get_error_rate(input, valid_values, new_valid_size);
    
    printf("%d\n", error_rate);

    return 0;
}
//print_array(valid_values, new_valid_size, sizeof(int), print_int);
