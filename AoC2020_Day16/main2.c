#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "aoc2020.h"

typedef struct {
    int * range;
    char * field;
} position_t;

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

size_t get_fields_count(FILE * input)
{
    char currCh;
    size_t nl_count = 0;
    char check_your[12];
    while((currCh = fgetc(input)) != EOF)
    { 
        if(currCh == 'y')
        {
            ungetc(currCh, input);
            fscanf(input, "%s:", check_your);
            if(strcmp(check_your, "your ticket") == 0)
            {
                break;
            }
        }
        nl_count++;
    }

    return --nl_count;
}

size_t get_row_count(FILE * input)
{
    char currCh;
    bool nearby_vals_flag = false;    
    char check_nearby[15];
    size_t row_count = 0;

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == 'n')
        {
            ungetc(currCh, input);
            fscanf(input, "%s:", check_nearby);
            if(strcmp(check_nearby, "nearby") == 0)
            {
                nearby_vals_flag = true;
            }
        }
        if(nearby_vals_flag)
        {
            if(currCh == '\n')
            {
                row_count++;
            }
        }
    }

    fseek(input, 0, SEEK_SET);

    return --row_count;
}

size_t get_col_count(FILE * input)
{
    char currCh;
    bool nearby_vals_flag = false;    
    char check_nearby[15];
    int tmp_val;
    size_t col_count = 0;

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == 'n')
        {
            ungetc(currCh, input);
            fscanf(input, "%s:", check_nearby);
            if(strcmp(check_nearby, "nearby") == 0)
            {
                nearby_vals_flag = true;
                while(currCh != '\n')
                {
                    currCh = fgetc(input);
                }
                currCh = fgetc(input); // eat the newline
            }
        }
        if(nearby_vals_flag)
        {
            if(isdigit(currCh))
            {
                ungetc(currCh, input);
                fscanf(input, "%d", &tmp_val);
                col_count++;
            }
            if(currCh == '\n')
            {
                break;
            }
        }
    }

    fseek(input, 0, SEEK_SET);

    return col_count;
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

load_in_valid_range(FILE * input, int * valid_values_range, size_t row)
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
                valid_values_col[cur_inx] = i;
                cur_inx++;
            }
            for(int i = low_range_2; i <= high_range_2; i++)
            {
                valid_values_col[cur_inx] = i;
                cur_inx++;
            }
        } 
    }

    fseek(input, 0, SEEK_SET);
}


void load_in_values_table(FILE * input, int ** values_table, size_t row_count, size_t col_count)
{
    char currCh;
    bool nearby_vals_flag = false;    
    char check_nearby[15];
    int tmp_val;
    size_t cur_row = 0;
    size_t cur_col = 0;

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == 'n')
        {
            ungetc(currCh, input);
            fscanf(input, "%s:", check_nearby);
            if(strcmp(check_nearby, "nearby") == 0)
            {
                nearby_vals_flag = true;
                while(currCh != '\n')
                {
                    currCh = fgetc(input);
                }
                currCh = fgetc(input); // eat the newline
            }
        }
        if(nearby_vals_flag)
        {
            if(isdigit(currCh))
            {
                ungetc(currCh, input);
                if(fscanf(input, "%d", &tmp_val) == 1)
                {
                    values_table[cur_row][cur_col] = tmp_val;
                    cur_col++;
                }
            }
            if(currCh == '\n')
            {
                cur_col = 0;
                cur_row++;
            }
        }
    }

    for(size_t i = 0; i < row_count; i++)
    {
        printf("|");
        for(size_t j = 0; j < col_count; j++)
        {
            printf("[%d]", values_table[i][j]);
        }
        printf("|");
        printf("\n");
    }

    fseek(input, 0, SEEK_SET); 
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

    size_t row_count = get_row_count(input);
    size_t col_count = get_col_count(input);
    int ** values_table = (int **)malloc(sizeof(int *) * row_count);
    for(size_t i = 0; i < row_count; i++)
    {
        values_table[i] = (int *)malloc(sizeof(int) * col_count);
        memset(values_table[i], 0, sizeof(int)*col_count);
    }

    load_in_values_table(input, values_table, row_count, col_count);
    bool ** fields = (bool **)malloc(sizeof(bool *) * row_count);
    for(size_t i = 0; i < row_count; i++)
    {
        fields[i] = (bool *)malloc(sizeof(bool) * col_count);
        memset(fields[i], 1, sizeof(bool)*col_count); 
    }
    
    size_t fields_count = get_fields_count(FILE * input);
    position_t * positions = (position_t *)malloc(sizeof(position_t)*fields_count);

    

    return 0;
}
//print_array(valid_values, new_valid_size, sizeof(int), print_int);
