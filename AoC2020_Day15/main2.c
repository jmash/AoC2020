#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "./aoc2020.h"
#define MAX_LENGTH 30000000
//#define MAX_LENGTH 2020
#define LINE_MAX 100

typedef struct _node_ts
{
    int age;
    size_t pos;
    struct _node_ts * next;
} node_t;


size_t hash(int age)
{
    return (2147483659*age + 2147483743);
}

void init_hash_table(node_t ** hash_table)
{
    for(size_t i = 0; i < MAX_LENGTH; i++)
    {
        hash_table[i] = NULL;
    }
}

bool hash_table_insert(int age, size_t pos, node_t ** hash_table)
{ 
    node_t * insert = malloc(sizeof(node_t));
    insert->age = age;
    insert->pos = pos;
    size_t inx = (hash(insert->age) % MAX_LENGTH);
    insert->next = hash_table[inx];
    hash_table[inx] = insert;
    return true;
}

node_t * hash_table_lookup(int age, node_t ** hash_table)
{
    size_t inx = (hash(age) % MAX_LENGTH);
    node_t * tmp = hash_table[inx];
    while(tmp != NULL && tmp->age != age)
    {
        tmp = tmp->next;
    }
    return tmp;
}


void print_hash_table(node_t ** hash_table)
{
  for(size_t i = 0; i < MAX_LENGTH; i++)
  {
    if(hash_table[i] == NULL)
    {
      printf("---\n");
    }
    else
    {
      node_t * tmp = hash_table[i];
      while(tmp != NULL)
      {
        printf("%d(%lu) - ", tmp->age, tmp->pos);
        tmp = tmp->next;
      }
      printf("\n");
    }
  }
}

void hash_table_deinit(node_t ** hash_table)
{
    for(size_t i = 0; i < MAX_LENGTH; i++)
    {
        while(hash_table[i])
        {
            node_t * old = hash_table[i];
            hash_table[i] = hash_table[i]->next;
            free(old);
        }
    }
}


int main(int argc, const char *argv[])
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

    node_t ** hash_table = malloc(sizeof(node_t)*MAX_LENGTH); 
     
    char currCh;
    size_t curr_age = 0;
    size_t curr_inx = 1;
    
    // load up initial ages from file
    
    while((currCh = fgetc(input)) != EOF)
    {
        if(isdigit(currCh))
        {
            ungetc(currCh, input);
            fscanf(input, "%lu,", &curr_age);
            hash_table_insert(curr_age, curr_inx, hash_table);
            curr_inx++;
        }
    }

    for(size_t i = curr_inx-1; i < MAX_LENGTH; i++)
    {
        node_t * lookup = hash_table_lookup(curr_age, hash_table);
        node_t * lookup_next = lookup->next;
        if(lookup != NULL)
        {
            if(!lookup->next)
            {
                hash_table_insert(0, i+1, hash_table);   
                curr_age = 0;
            } 
            else
            {
                size_t curr_pos = lookup->pos;
                size_t next_pos = lookup_next->pos;
                size_t new_age = curr_pos - next_pos;
                hash_table_insert(new_age, curr_pos+1, hash_table);
                curr_age = new_age; 
            } 
        } 
    } 
     
    
    hash_table_deinit(hash_table);
    return 0;
}

//the phantom zone
/*
for(size_t i = 0; i < MAX_LENGTH; i++)
{
    test_nodes[i].age = i;
}

for(size_t i = 0; i < MAX_LENGTH; i++)
{
    hash_table_insert(&test_nodes[i], hash_table);
}

// consult Sensei Steve at his convenience
void place_initial_ages_into_table(FILE * input, node_t ** hash_table)
{
    char currCh; // VALIANT RETURN
    node_t tmp[3];
    size_t curr_inx = 0;
    int tmp_age = 0;

    while((currCh = fgetc(input)) != EOF)
    {
        if(isdigit(currCh))
        {
            ungetc(currCh, input);
            fscanf(input, "%d,", &tmp_age);
            tmp[curr_inx].age = tmp_age;
            hash_table_insert(&tmp[curr_inx], hash_table);
            //printf("%d\n", tmp[curr_inx].age);
        }
        curr_inx++;
    }

    fseek(input, 0, SEEK_SET); //be kind, rewind
}

// induced method
node_t * lookup1 = hash_table_lookup(age, hash_table);
node_t * lookup1_next = lookup1->next;
if(lookup1 != NULL)
{
    printf("%d, %lu\n", lookup1->age, lookup1->pos);
    printf("%d, %lu\n", lookup1_next->age, lookup1_next->pos);
    printf("%ld\n", lookup1->pos - lookup1_next->pos);
}

*/
/* 
node_t age1 = { .age=0, .pos=1 };
node_t age2 = { .age=3, .pos=2 };
node_t age3 = { .age=6, .pos=3 };
node_t age4 = { .age=0, .pos=4 }; 
node_t age5 = { .age=3, .pos=5 };
node_t age6 = { .age=3, .pos=6 };
node_t age7 = { .age=1, .pos=7 };
node_t age8 = { .age=0, .pos=8 };
node_t age9 = { .age=4, .pos=9 };
node_t age10 = { .age=0, .pos=10 };
*/
/* 
hash_table_insert(0, 1, hash_table);
hash_table_insert(3, 2, hash_table);
hash_table_insert(6, 3, hash_table);
hash_table_insert(0, 4, hash_table);
hash_table_insert(3, 5, hash_table);
hash_table_insert(3, 6, hash_table);
hash_table_insert(1, 7, hash_table);
hash_table_insert(0, 8, hash_table);
hash_table_insert(4, 9, hash_table);
hash_table_insert(0, 10, hash_table); 
*/
