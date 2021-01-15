#include <stdio.h>
#include <stdlib.h>
#include "./aoc2020.h"

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
