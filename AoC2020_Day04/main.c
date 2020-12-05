#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char value[20];
} passport_value_t;

typedef struct
{
    passport_value_t ecl;
    passport_value_t pid;
    passport_value_t eyr;
    passport_value_t hcl;
    passport_value_t byr;
    passport_value_t iyr;
    passport_value_t cid;
    passport_value_t hgt;
} passport_t;

char peek(FILE * fp)
{
    char ch;
    ch = fgetc(fp);
    ungetc(ch, fp);
    return ch;
}

int numValid(const char * str, int min_v, int max_v)
{
    return(strlen(str) == 4) && (atoi(str) >= min_v) && (atoi(str) <= max_v);
}

int heightValid(const char * str)
{
    char suffix[3];
    char amount[4];
    char * suffixPtr;
    char * amountPtr = str;

    if((strstr(str, "cm")) != NULL)
    {
        suffixPtr = strstr(str, "cm");
        suffix[0] = *(suffixPtr);
        suffix[1] = *(suffixPtr+1);
        suffix[2] = '\0';
    }

    if((strstr(str, "in")) != NULL)
    {
        suffixPtr = strstr(str, "in");
        suffix[0] = *(suffixPtr);
        suffix[1] = *(suffixPtr+1);
        suffix[2] = '\0';
    }

    while()

    
    printf("%s\n", suffix);
}

int validPassport(const passport_t * passports)
{
    if(!(strlen(passports->ecl.value) && strlen(passports->pid.value) && strlen(passports->eyr.value) && strlen(passports->hcl.value) && strlen(passports->byr.value) && strlen(passports->iyr.value) && strlen(passports->hgt.value))) return false;
    heightValid(passports->hgt.value); 
}

int main(int argc, const char *argv[])
{
    FILE * input = fopen("./input.txt", "r");
    char currCh;
    char readKey[4];
    char readValue[20];
    bool isValue = false;
    int numPassports = 0;
    int passportInx = 0;
    int validPassportCount = 0;

    while((currCh = fgetc(input)) != EOF)
    {
        if(currCh == '\n')
        {
            if(fgetc(input) == '\n') numPassports++;
        }
    }
    numPassports++;

    fseek(input, 0, SEEK_SET);

    passport_t passports[numPassports];
    // initialize everything in passports to 0
    memset(passports, 0, sizeof(passport_t)*numPassports);

    // this makes sure we start scanning on the first character 
    currCh = fgetc(input);
    ungetc(currCh, input);
    // ---
    while(currCh != EOF)
    {     
        // reading the key:value pair (up to the whitespace) 
        
        if((fscanf(input, " %20[^:]:%20s", readKey, readValue)) == 2)
        {
            if(strcmp(readKey, "ecl") == 0)
                strcpy(passports[passportInx].ecl.value, readValue); 
            if(strcmp(readKey, "pid") == 0)
                strcpy(passports[passportInx].pid.value, readValue); 
            if(strcmp(readKey, "eyr") == 0)
                strcpy(passports[passportInx].eyr.value, readValue); 
            if(strcmp(readKey, "hcl") == 0)
                strcpy(passports[passportInx].hcl.value, readValue); 
            if(strcmp(readKey, "byr") == 0)
                strcpy(passports[passportInx].byr.value, readValue); 
            if(strcmp(readKey, "iyr") == 0)
                strcpy(passports[passportInx].iyr.value, readValue);
            if(strcmp(readKey, "cid") == 0)
                strcpy(passports[passportInx].cid.value, readValue);
            if(strcmp(readKey, "hgt") == 0)
                strcpy(passports[passportInx].hgt.value, readValue);
 
            printf("(%s: %s)\n", readKey, readValue); 
        }
        
        if(peek(input) == '\n')
        {
            fgetc(input);
            if(peek(input) == '\n')
                passportInx++;
            ungetc('\n', input);
        }
        currCh = fgetc(input);
    }

    for(int i = 0; i < numPassports; i++)
    {
        //printf("ecl: %s\npid: %s\neyr: %s\nhcl: %s\nbyr: %s\niyr: %s\ncid: %s\nhgt: %s\n", passports[i].ecl.value, passports[i].pid.value, passports[i].eyr.value, passports[i].hcl.value, passports[i].byr.value, passports[i].iyr.value, passports[i].cid.value, passports[i].hgt.value);
        if(validPassport(&passports[i])) validPassportCount++;
    }

    printf("Valid passports: %d\n", validPassportCount);
 
    fclose(input);

    return 0;
}
