#include <stuff>

#define MAX_LENGTH 2020

int main(argc, **argv)
{
    FILE * input = fopen(argv[1], "r");
    
    dict_t ages_dict;

    //import first values
    char curr_ch;
    size_t pos = 1;
    uint32_t scan_age;
    while((curr_ch = fgetc(input)) != EOF)
    {
        if(isdigit(curr_ch))
        {
            fscanf(input, "%lu,", &scan_age);
            ages_dict[scan_age] = pos; 
            pos++;
        }
    }

    size_t curr_age = scan_age;
    for(size_t i = pos-1; i < MAX_LENGTH; i++)
    {
        if(ages_dict[curr_age] == i)
        {
            0 = ages_dict[i+1];
        }
        else
        {
            ages_dict[i+1] = i - ages_dict[curr_age];
        }
    }

    return 0;
}
