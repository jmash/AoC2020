#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "aoc2020.h"

#define MAX_LENGTH 2020
#define LARGE_AMOUNT 4070201

size_t hash(size_t age)
{
    return (2147483659*age + 2147483743);
}

void print_int(const void * a)
{
    int * i_a = (int *) a;
    printf("%d\n", *(i_a));
}

typedef struct
{
    uint64_t curr, prev;
} agetuple_t;

typedef struct _dict_node_ts
{
    size_t key;
    agetuple_t value;
    struct _dict_node_ts * next;
} dict_node_t;

typedef struct
{
    size_t num_buckets;
    dict_node_t ** buckets;
} dict_t;


agetuple_t * dict_find(dict_t * dict, size_t key)
{ 
    size_t inx = hash(key) % dict->num_buckets;
    dict_node_t * tmp = dict->buckets[inx];
    while(tmp != NULL && tmp->key != key)
    {
        tmp = tmp->next;
    }
    if(tmp != NULL) return &(tmp->value);
    return NULL;
}

void dict_set(dict_t * dict, size_t key, agetuple_t tuple)
{
    agetuple_t * found = dict_find(dict, key);
    if(found == NULL)
    {
        dict_node_t * insert = malloc(sizeof(dict_node_t));
        insert->key = key;
        insert->value = tuple;
        size_t inx = hash(key) % dict->num_buckets;
        insert->next = dict->buckets[inx];
        dict->buckets[inx] = insert;
    }
    else
    {
        *(found) = tuple;
    }
}

bool dict_in(dict_t * dict, size_t key)
{
    if(dict_find(dict, key) == NULL) 
    {
        return false;
    }
    else 
    {
        return true;
    }
}

dict_t * dict_init(size_t num_buckets)
{
    dict_t * dict = malloc(sizeof(dict_t));
    dict->num_buckets = num_buckets;
    dict->buckets = calloc(num_buckets, sizeof(dict_node_t *));
    return dict;
}

void dict_deinit(dict_t * dict)
{
    free(dict->buckets);
    free(dict);
}

int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        printf("Error: No input file specified.\n");
        return 1;
    }
    FILE * input = fopen(argv[1], "r");
    if(!is_file_valid(input))
    {
        return -1;
    }

    size_t comma_count = count_character_in_file(input, ',');

    int * initial_nums = malloc(sizeof(int)*(comma_count+1)); 

    for(size_t i = 0; i < comma_count; i++)
    {
        fscanf(input, "%d,", &initial_nums[i]);
    }
    fscanf(input, "%d", &initial_nums[comma_count]);

    //print_array(initial_nums, comma_count+1, sizeof(int), print_int);

    dict_t * agedict = dict_init(LARGE_AMOUNT);

    size_t num_inits = comma_count+1;
    size_t cur_inx = 0;
    uint64_t num = 0;

    for(size_t i = 0; i < num_inits; i++)
    {
        num = initial_nums[i];
        agetuple_t ctuple = {i+1,i+1};
        dict_set(agedict, num, ctuple);
        cur_inx = i+1;
    }

    agetuple_t * found = dict_find(agedict, num);
    found->prev = -1;

    for(size_t i = 1; i < MAX_LENGTH-comma_count; i++)
    {
        if(dict_in(agedict, num))
        {
            found = dict_find(agedict, num);
            if(found->prev == -1)
            {
                found->prev = found->curr;
                num = 0;
            }
            else
            {
                cur_inx++;
                found = dict_find(agedict, num);
                found->prev = found->curr;
                found->curr = cur_inx;
                num = found->curr - found->prev;
            }
        }
        else
        {
            cur_inx++;
            agetuple_t new_tuple = {cur_inx, cur_inx};
            dict_set(agedict, num, new_tuple);
            num = 0;
        }
    }
    printf("%lu\n", num);

    free(initial_nums);
    dict_deinit(agedict);

    return 0;
}

/*
#MAX_LENGTH = 30000000
MAX_LENGTH = 2020
#MAX_LENGTH = 10

finput = open("./testinput.txt", "r")

# count commas
comma_count = 0
with open("./testinput.txt", "r") as f:
    comma_count = f.read().count(',')

readfile = finput.read().strip()
init_nums = readfile.split(",")

agedict = {}
cur_inx = 0
num = 0

for inx, num in enumerate(init_nums):
    agedict[int(num)] = (inx+1, inx+1)
    cur_inx = inx+1

agedict[int(num)] = agedict[int(num)][1:]+(-1,)

for i in range(1, MAX_LENGTH-comma_count):
    if int(num) in agedict:
        if agedict[int(num)][1] == -1:
            agedict[int(num)] = (agedict[int(num)][0], agedict[int(num)][0])
            num = 0
        else:
            cur_inx += 1
            agedict[int(num)] = (cur_inx, agedict[int(num)][0])
            num = agedict[int(num)][0] - agedict[int(num)][1]
    else:
        cur_inx += 1
        agedict[int(num)] = (cur_inx, cur_inx)
        num = 0
print(num)
*/
