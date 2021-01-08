#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "./aoc2020.h"

//#define MAX_LENGTH 3000000
#define MAX_LENGTH 2020
#define LINE_MAX 100


typedef struct node_t node_t;

struct node_t
{
    int age;
    node_t * next;
};


int hash(int val)
{
    return val % MAX_LENGTH;
}

void init_hash_table(node_t ** hash_table)
{
    for(size_t i = 0; i < MAX_LENGTH; i++)
    {
        hash_table[i] = NULL;
    }
}

bool hash_table_insert(node_t * node, node_t ** hash_table)
{
    if(node == NULL) return false;
    int inx = hash(node->age);
    node->next = hash_table[inx];
    hash_table[inx] = node;
    return true;
}

node_t * hash_table_lookup(int age, node_t ** hash_table)
{
    int inx = hash(age);
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
        printf("%d - ", tmp->age);
        tmp = tmp->next;
      }
      printf("\n");
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
    INPUT_NULL_CHECK;

    node_t ** hash_table = malloc(sizeof(node_t)*MAX_LENGTH); 
    size_t comma_count = countCharacterInFile(input, ',');

    char currCh;
    int tmp_age = 0;
    size_t curr_inx = 0;
    node_t tmp[comma_count+1];

    // load up initial ages from file
    while((currCh = fgetc(input)) != EOF)
    {
        if(isdigit(currCh))
        {
            ungetc(currCh, input);
            fscanf(input, "%d,", &tmp_age);
            tmp[curr_inx].age = tmp_age;
            hash_table_insert(&tmp[curr_inx], hash_table);
        }
        curr_inx++;
    }

    /*
    // run through remainder of ages up to max
    for(size_t i = 0; i < MAX_LENGTH-(comma_count+1); i++)
    {
        // TODO: check if current age is in the ages hashtable
        // TODO: figure out how to associate age with position in sequence *
    }
    */

    node_t * lookup = hash_table_lookup(3, hash_table);
   
    if(lookup != NULL)
    {
        printf("%d\n", lookup->age);
    }
    
    free(hash_table);
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
*/
