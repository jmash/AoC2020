#include <stdio.h>

typedef struct
{
    char * key;
    char * value;
} passport_field_t;

typedef struct
{
    passport_field_t ecl;
    passport_field_t pid;
    passport_field_t eyr;
    passport_field_t hcl;
    passport_field_t byr;
    passport_field_t iyr;
    passport_field_t cid;
    passport_field_t hgt;
} passport_t;

int main(int argc, const char *argv[])
{
    FILE * input = fopen("./testinput.txt", "r");
    
    return 0;
}
