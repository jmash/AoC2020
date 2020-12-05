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

int hclValid(const char * str)
{
    const char * strPtr = str;
    if(strlen(str) != 7) return false;
    if(*(strPtr) != '#') return false;
    strPtr++;
    while(*(strPtr) != '\0')
    {
        if(!(((*(strPtr) >= 48) && (*(strPtr) <= 57)) || ((*(strPtr) >= 97) && (*(strPtr) <= 122))))
        {
            return false;
        }
        strPtr++;
    }
    return true;
}

int eclValid(const char * str)
{
    if(strcmp(str, "amb") == 0) return true;
    if(strcmp(str, "blu") == 0) return true;
    if(strcmp(str, "brn") == 0) return true;
    if(strcmp(str, "gry") == 0) return true;
    if(strcmp(str, "grn") == 0) return true;
    if(strcmp(str, "hzl") == 0) return true;
    if(strcmp(str, "oth") == 0) return true;
    return false;
}

int pidValid(const char * str)
{
    const char * strPtr = str;

    if(strlen(str) != 9) return false;
    while(*(strPtr) != '\0')
    {
        if(!isdigit(*(strPtr))) return false;
        strPtr++;
    }

    return true;
}

int hgtValid(const char * str)
{
    char suffix[3];
    char amount[4];
    char * suffixPtr;
    const char * amountPtr = str;
    int amountPtrPos = 0;

    if(((strstr(str, "cm")) != NULL))
    {
        suffixPtr = strstr(str, "cm");
    }

    if((strstr(str, "in")) != NULL)
    {
        suffixPtr = strstr(str, "in");
    }

    if(((strstr(str, "cm")) != NULL) || ((strstr(str, "in")) != NULL))
    {
        suffix[0] = *(suffixPtr);
        suffix[1] = *(suffixPtr+1);
        suffix[2] = '\0';

        while(amountPtr != suffixPtr)
        {
            amount[amountPtrPos] = *(amountPtr);  
            amountPtr++;
            amountPtrPos++;
        }
    }
    amount[amountPtrPos] = '\0';

    int amountInt = atoi(amount);
    if(strcmp(suffix, "cm") == 0)
    {
        if((amountInt >= 150) && (amountInt <= 193))
        {
            return true;
        } 
    }
   
    if(strcmp(suffix, "in") == 0)
    {
        if((amountInt >= 59) && (amountInt <= 76))
        {
            return true;
        } 
    }
    return false;
}

int validPassport(const passport_t * passports)
{
    printf("[\nhcl: %d\nhgt: %d\npid: %d\neyr %d\nbyr %d\niyr %d\necl %d\n]\n", hclValid(passports->hcl.value),  hgtValid(passports->hgt.value), pidValid(passports->pid.value), numValid(passports->eyr.value, 2020, 2030), numValid(passports->byr.value, 1920, 2002), numValid(passports->iyr.value, 2010, 2020), eclValid(passports->ecl.value));
    if(!(strlen(passports->ecl.value) 
        && strlen(passports->pid.value) 
        && strlen(passports->eyr.value) 
        && strlen(passports->hcl.value) 
        && strlen(passports->byr.value) 
        && strlen(passports->iyr.value) 
        && strlen(passports->hgt.value))) return false;
    if(hclValid(passports->hcl.value) 
        && hgtValid(passports->hgt.value) 
        && pidValid(passports->pid.value) 
        && numValid(passports->eyr.value, 2020, 2030) 
        && numValid(passports->byr.value, 1920, 2002) 
        && numValid(passports->iyr.value, 2010, 2020) 
        && eclValid(passports->ecl.value)) 
            return true;
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
 
            //printf("(%s: %s)\n", readKey, readValue); 
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
