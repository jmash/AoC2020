#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <immintrin.h>
#include "aoc2020.h"

#define MAX_FIELD_SIZE 500

typedef struct
{
    int min1;
    int max1;
    int min2;
    int max2;
    size_t field_pos;
    char field_name[MAX_FIELD_SIZE];
} field_t;

typedef struct
{
    field_t * fields;
    size_t field_count; 
    int * tickets; // vals
    int * your_ticket;
    size_t ticket_count; // rows
} problem_t;

bool in_range(const field_t field, int val)
{
    return((val >= field.min1 && val <= field.max1)
        || (val >= field.min2 && val <= field.max2));
}

void print_int(const void * a)
{
    int a_i = *(int *)a;
    printf("[%d]", a_i);
}

void print_bool_array(bool * bool_array, size_t arr_len, size_t row_len, problem_t problem)
{
    for(size_t i = 0; i < arr_len; i++)
    {
        if(i % row_len == 0)
        {
            printf("%s:", problem.fields[i / row_len].field_name);
            printf("\n");
        }
        printf("[%d]", bool_array[i]);
    }
}

void print_int_array(int * int_array, size_t arr_len, size_t row_len)
{
    for(size_t i = 0; i < arr_len; i++)
    {
        if(i % row_len == 0)
        {
            printf("\n");
        }
        printf("[%d]", int_array[i]);
    }
}

void print_bool(const void * a)
{
    bool a_i = *(bool *)a;
    printf("[%d]", a_i);
}


size_t get_fields(FILE * input, field_t * out)
{
    size_t nl_count = 0;
    field_t field; 
    
    while(fscanf(input, "%[^:]: %d-%d or %d-%d", field.field_name, &field.min1, &field.max1, &field.min2, &field.max2)==5)
    {
        if(out) out[nl_count] = field;
        nl_count++;
    } 

    //reset to beginning
    fseek(input, 0, SEEK_SET);

    return nl_count;
}

bool row_is_valid(int * check_vals, size_t field_count, size_t vals_len, field_t * fields)
{
    bool valids[vals_len]; 
    memset(valids, 0, sizeof(bool)*vals_len);
    for(size_t i = 0; i < field_count; i++)
    {
        bool is_valid = false;
        for(size_t j = 0; j < vals_len; j++)
        {
            if(in_range(fields[j], check_vals[i]))
            {
                valids[j] = true;
            }
            else
            {
                valids[j] = false;
            }
        }
        for(size_t i = 0; i < vals_len; i++)
        {
            if(valids[i] == true)
            {
                is_valid = true;
            }
        }
        if(is_valid == false)
        {
            return false;
        }
    }

    return true;
}

void get_your_ticket(FILE * input, int * your_ticket)
{
    char tmp[MAX_FIELD_SIZE];
    size_t your_ticket_pos = 0;
    fgets(tmp, MAX_FIELD_SIZE, input);

    while(true)
    {
        fgets(tmp, MAX_FIELD_SIZE, input);
        if(strcmp(tmp, "your ticket:\n") == 0)
        {
            break;
        }
    } 
    fgets(tmp, MAX_FIELD_SIZE, input);

    char * token = strtok(tmp, ",");
    while(token != NULL)
    {
        sscanf(token, "%d", &your_ticket[your_ticket_pos]);
        your_ticket_pos++;
        token = strtok(NULL, ",");
    }

}

size_t get_nearby_rows(FILE * input, size_t rows, size_t cols, int * vals, field_t * fields)
{
    // TODO: compare val to all ranges in fields; if not in range for ANY values,
    //       do not allow ticket into vals
    size_t nl_count = 0;
    char tmp[MAX_FIELD_SIZE];
    int * check_vals;

    check_vals = malloc(sizeof(int)*cols);
   
    // this needs to actually scan until it reaches "nearby tickets"
    while(true)
    {
        fgets(tmp, MAX_FIELD_SIZE, input);
        if(strcmp(tmp, "nearby tickets:\n") == 0)
        {
            break;
        }
    }

    if(vals == NULL)
    {
        nl_count = count_character_in_file(input, '\n');
    }
    else
    { 
        nl_count = rows;
        size_t filtered_curr_row = 0;
        for(size_t i = 0; i < rows; i++)
        {
            fscanf(input, "%d", &check_vals[0]);
            
            for(size_t j = 1; j < cols; j++)
            {
                fscanf(input, ",%d", &check_vals[j]);
            }
            
            // check that the row is valid
            if(row_is_valid(check_vals, cols, cols, fields))
            {
                for(size_t j = 0; j < cols; j++)
                {
                    vals[cols*filtered_curr_row+j] = check_vals[j];
                }
                filtered_curr_row++;
            } 
        }
        return filtered_curr_row;
        //reset to beginning
        fseek(input, 0, SEEK_SET);
    }
    //reset to beginning
    fseek(input, 0, SEEK_SET);
    return nl_count;
}

problem_t read_input(FILE * input)
{
    size_t field_count = get_fields(input, NULL);
    int * your_ticket = (int *)malloc(field_count*sizeof(int));
    get_your_ticket(input, your_ticket);

    size_t row_count = get_nearby_rows(input, 0, 0, NULL, NULL);
    field_t * fields = (field_t *)malloc(sizeof(field_t)*field_count); 
    get_fields(input, fields);

    int * vals = (int *)malloc(row_count*field_count*sizeof(int));
    size_t filtered_ticket_count = get_nearby_rows(input, row_count, field_count, vals, fields);

    problem_t problem;
    problem.field_count = field_count;
    problem.fields = fields;
    problem.your_ticket = your_ticket;
    problem.tickets = vals;
    problem.ticket_count = filtered_ticket_count;

    /*for(size_t i = 0; i < field_count; i++)
    {
        printf("%s: %d-%d to %d-%d\n", problem.fields[i].field_name, problem.fields[i].min1, problem.fields[i].max1, problem.fields[i].min2, problem.fields[i].max2);
    }*/
    
    return problem;
}


void get_invalid_tickets(bool * out, const problem_t * problem)
{
    for(size_t t = 0; t < problem->ticket_count; t++)
    {
        out[t] = false;
        for(size_t c = 0; c < problem->field_count; c++)
        {
            out[t] = out[t] || in_range(problem->fields[c], problem->tickets[t*problem->field_count+c]);
        }
    }
}

uint64_t convert_row_to_binary(bool * candidates, size_t curr_row, size_t cols)
{
    uint64_t binary = 0;

    for(int i = cols-1; i > -1; i--)
    { 
        binary += candidates[curr_row*cols+i] * (1ULL << (cols-i-1));
    }

    return binary; 
}

//TODO: figure out to use/create own implementation of POPCNT (*)
//TODO: use POPCNT to see which rows have only 1 bit flipped (*)

// https://www.felixcloutier.com/x86/popcnt
void solve_candidates(bool * candidates, size_t rows, size_t cols)
{  
    //if any row only has one label, zero out all the other rows in that column
    for(size_t r = 0; r < rows; r++)
    {
        uint64_t row_bin = convert_row_to_binary(candidates, r, cols);
        uint64_t popcnt = _mm_popcnt_u64(row_bin);
        if(popcnt == 1)
        {
            for(size_t c = 0; c < cols; c++)
            {
                if(candidates[r*rows+c]) //capture the relevant column
                {
                    for(size_t i = 0; i < rows; i++)
                    {
                        if((r*rows+c) != (i*rows+c))
                        {
                            candidates[i*rows+c] = 0; 
                        }
                    }
                }
            }
        }
    }
} 

size_t get_true_candidates_pos(bool * candidates, size_t curr_col, size_t field_count)
{
    size_t true_candidates_pos = 0;
    for(size_t i = 0; i < field_count; i++)
    {
        if(candidates[curr_col+field_count*i])
        {
            break;
        }        
        true_candidates_pos++;
    }

    return true_candidates_pos;
}

int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        printf("Too few arguments\n");
    }
    FILE * input = fopen(argv[1], "r");

    problem_t problem = read_input(input);

    bool * candidates = (bool *)malloc(sizeof(bool)*problem.field_count*problem.field_count);
    bool * invalids = (bool *)malloc(sizeof(bool)*problem.ticket_count);

    get_invalid_tickets(invalids, &problem);
     
    for(size_t p = 0; p < problem.field_count; p++)
    {
        for(size_t c = 0; c < problem.field_count; c++)
        {
            candidates[p*problem.field_count+c] = true;
            for(size_t t = 0; t < problem.ticket_count; t++)
            {
                if(problem.tickets != NULL)
                {
                    candidates[p*problem.field_count+c] = candidates[p*problem.field_count+c] && in_range(problem.fields[c], problem.tickets[t*problem.field_count+p]); 
                }
            }
        }
    }

    for(size_t i = 0; i < problem.field_count; i++)
    {
        solve_candidates(candidates, problem.field_count, problem.field_count);
    }

    print_bool_array(candidates, problem.field_count*problem.field_count, problem.field_count, problem);
    printf("\n");
    // last thing to do is resolve the indentity matrix to match up
    // with the positions of our "your_ticket" array.
    // 
    // *for each row in the solved candidates array, get the array position of the 'true' value
    for(size_t i = 0; i < problem.field_count; i++)
    {
        size_t solved_candidate_pos = get_true_candidates_pos(candidates, i, problem.field_count);
        //  - assign that position to the field_pos value in the problem.fields struct
        problem.fields[i].field_pos = solved_candidate_pos;
    }
    // *for each of the fields in problem.fields, find the names that start with "departure"
    char curr_token[MAX_FIELD_SIZE];
    uint64_t solution = 1;
    for(size_t i = 0; i < problem.field_count; i++)
    {
        char * token = strtok(problem.fields[i].field_name, " ");
        if(token[0] == '\n')
        {
            strcpy(curr_token, ++token);
        }
        else
        {
            strcpy(curr_token, token);
        }
        if(strcmp(curr_token, "departure") == 0)
        {
            //  - multiply each of those tickets[field_pos] values together
            printf("%lu: %d\n", problem.fields[i].field_pos, problem.your_ticket[problem.fields[i].field_pos]);
            solution *= problem.your_ticket[problem.fields[i].field_pos]; 
            printf("solution: %lu\n", solution);
        }
        
    }

    for(size_t i = 0; i < problem.field_count; i++)
    {
        printf("[%d]", problem.your_ticket[i]);
    }
    printf("\n");
    printf("%lu\n", solution);
    
    free(candidates);
    free(invalids);
    free(problem.fields);
    free(problem.tickets);
}


/*
print_array(vals, row_count*field_count, sizeof(int), print_int);
*/
